/**
 * Copyright (c) 2017 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* 
 * File name  : main.c
 * Author     : KU Leuven
 * Description: This file provides a sample implementation for the morphy module
 * and shows how the application can communicate with the morphy module
 */

#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"

#include "app_timer.h"
#include "peer_manager.h"
#include "peer_manager_handler.h"
#include "bsp_btn_ble.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "fds.h"
#include "ble_conn_state.h"
#include "nrf_drv_clock.h"
#include "app_uart.h"
#include "app_error.h"
#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
#include "nrf_drv_gpiote.h"
#include "morphy.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


#if NRF_LOG_ENABLED
static TaskHandle_t m_logger_thread;                                /**< Definition of Logger thread. */
#endif
static TaskHandle_t m_morphy_thread;
static TaskHandle_t m_app_thread;

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}


#if NRF_LOG_ENABLED
/**@brief Thread for handling the logger.
 *
 * @details This thread is responsible for processing log entries if logs are deferred.
 *          Thread flushes all log entries and suspends. It is resumed by idle task hook.
 *
 * @param[in]   arg   Pointer used for passing some arbitrary information (context) from the
 *                    osThreadCreate() call to the thread.
 */
static void logger_thread(void * arg)
{
    UNUSED_PARAMETER(arg);

    while (1)
    {
        NRF_LOG_FLUSH();

        vTaskSuspend(NULL); // Suspend myself
    }
}
#endif //NRF_LOG_ENABLED

/**@brief A function which is hooked to idle task.
 * @note Idle hook must be enabled in FreeRTOS configuration (configUSE_IDLE_HOOK).
 */
void vApplicationIdleHook( void )
{
#if NRF_LOG_ENABLED
     vTaskResume(m_logger_thread);
#endif
}

#ifdef FPU_INTERRUPT_MODE
void FPU_IRQHandler(void)
{
    // Prepare pointer to stack address with pushed FPSCR register.
    uint32_t * fpscr = (uint32_t * )(FPU->FPCAR + FPU_FPSCR_REG_STACK_OFF);
    // Execute FPU instruction to activate lazy stacking.
    (void)__get_FPSCR();
    // Clear flags in stacked FPSCR register.
    *fpscr = *fpscr & ~(FPU_EXCEPTION_MASK);
}
#endif

/**@brief Function for initializing the clock.
 */
static void clock_init(void)
{
    ret_code_t err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
}


#define RX_PIN_NUMBER  8
#define TX_PIN_NUMBER  6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define UART_RX_PIN              NRF_GPIO_PIN_MAP(1,1)    // UART RX pin number.
#define UART_TX_PIN              NRF_GPIO_PIN_MAP(1,2)    // UART TX pin number.
#define UART_CTS_PIN             NRF_GPIO_PIN_MAP(0,7)     // UART Clear To Send pin number.
#define UART_RTS_PIN             NRF_GPIO_PIN_MAP(0,9)    // UART Request To Send pin number.
#define UART_TX_BUF_SIZE 256                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 256                         /**< UART RX buffer size. */
volatile bool data_available = false;
static uint8_t data_array[200];
static uint8_t data_length = 0;
static bool ledToggle = false;
volatile bool lowVoltageAlarm = false;
volatile bool startTasks = false;

#define LV_ALARM_PIN            NRF_GPIO_PIN_MAP(0,27)
#define TASK_GPIO               NRF_GPIO_PIN_MAP(1,10)

void uart_error_handle(app_uart_evt_t * p_event)
{
    static uint8_t index;
    
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
    else if (p_event->evt_type == APP_UART_DATA_READY)
    {  
       UNUSED_VARIABLE(app_uart_get(&data_array[index]));
       index++;
       
       //NRF_LOG_INFO("received: %s", );
       //NRF_LOG_RAW_INFO("%s\r\n", data_array);
       /* TODO: Substitute '\n' in the statement below with the Modbus escape character, if 
           applicable */
       uint8_t qbuf[3] = {0}, recv = 0;
       if ((data_array[index - 1] == '\n'))
       {
            qbuf[0] = data_array[0]; qbuf[1] = data_array[1]; recv = atoi(qbuf);
            if (recv == 18) {
                morphyCallBrownoutHandler();
            }
            else if (recv == 19) {
                morphyCallBugHandler(data_array, index);
            }
            //else if (recv == 20) {
            //    //vTaskStartScheduler();
            //    startTasks = true;
            //}
            else {
                data_available = true;
                data_length = index;
                NRF_LOG_INFO("Received command copying");

                index = 0;
            }
        }

    }
}

void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    lowVoltageAlarm = true;
    morphyCallBrownoutHandler();
}

static void gpio_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);

    //nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(false);

    //err_code = nrf_drv_gpiote_out_init(TASK_GPIO, &out_config);
    //APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    //nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(true);
    in_config.sense = NRF_GPIOTE_POLARITY_LOTOHI;//NRF_GPIOTE_POLARITY_TOGGLE; //NRF_GPIOTE_POLARITY_LOTOHI
    in_config.pull = NRF_GPIO_PIN_PULLDOWN;
    in_config.hi_accuracy = false;
    in_config.is_watcher = false;

    err_code = nrf_drv_gpiote_in_init(LV_ALARM_PIN, &in_config, in_pin_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_in_event_enable(LV_ALARM_PIN, true);

    nrf_gpio_cfg_output(TASK_GPIO);
    nrf_gpio_pin_clear(TASK_GPIO);
}

#define UART_TEST 1
void uart_init()
{
    uint32_t err_code;

    const app_uart_comm_params_t comm_params =
      {
#ifdef UART_TEST
            RX_PIN_NUMBER,
            TX_PIN_NUMBER,
#else
            UART_RX_PIN,
            UART_TX_PIN,
#endif
            RTS_PIN_NUMBER,
            CTS_PIN_NUMBER,
            APP_UART_FLOW_CONTROL_DISABLED,
            false,
#ifdef UART_TEST
            NRF_UARTE_BAUDRATE_115200
#else
            NRF_UART_BAUDRATE_9600
#endif
      };

    APP_UART_FIFO_INIT(&comm_params,
                         UART_RX_BUF_SIZE,
                         UART_TX_BUF_SIZE,
                         uart_error_handle,
                         APP_IRQ_PRIORITY_HIGHEST,//APP_IRQ_PRIORITY_MID,//APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);
}

static uint8_t reconf = 1;
static bool paraConf = true;
static void morphy_app_thread(void * arg)
{
    UNUSED_PARAMETER(arg);
    uint8_t cr;
    float tcorev = 0.0;
    uint16_t corev = 0;

    NRF_LOG_INFO("Starting Morphy App");
    NRF_LOG_INFO("Configuring Morphy");
    
    vTaskDelay(pdMS_TO_TICKS(1000));
    tcorev = getCoreVoltage();
    corev = tcorev * 1000;
    NRF_LOG_INFO("%d\r\n", corev);
    vTaskDelay(pdMS_TO_TICKS(1000));
    tcorev = 2.0;
    setLowVoltageAlarm(tcorev);
    vTaskDelay(pdMS_TO_TICKS(1000));
    NRF_LOG_INFO("Low Voltage Alarm Set\r\n");

    //nrf_drv_gpiote_out_toggle(TASK_GPIO);

    while (1)
    {
        NRF_LOG_INFO("Running App");
        reconfigCapArray(reconf, paraConf);
        reconf++;
        if (reconf > 4) {
            reconf = 1;
        }
        nrf_gpio_pin_toggle(TASK_GPIO);
        //vTaskDelay(pdMS_TO_TICKS(10));
        if (lowVoltageAlarm == true) {
            lowVoltageAlarm = false;
            NRF_LOG_INFO("Low Voltage Detected\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

static void app_thread(void * arg)
{
    UNUSED_PARAMETER(arg);

    while (1)
    {
        NRF_LOG_INFO("Running App");
        nrf_gpio_pin_toggle(TASK_GPIO);
        vTaskDelay(pdMS_TO_TICKS(1000));
        nrf_gpio_pin_toggle(TASK_GPIO);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}


bool uart_tx_data(uint8_t *buf, uint8_t dataSize)
{
    for (uint8_t i = 0; i < dataSize; i++) {
        while (app_uart_put(buf[i]) != NRF_SUCCESS);
    }
    return true;
}

bool uart_rx_data(uint8_t *buf, uint8_t *dataSize)
{
    if (buf == NULL) {
        return false;
    }

    while (!data_available);
    data_available = false;
    memcpy(buf, data_array, data_length);
    *dataSize = data_length;

    return true;
}

#define CHARGE_LEVEL_MEAS_INTERVAL         2000
static TimerHandle_t m_charge_timer;


void charge_monitor_timer(void)
{
    // Initialize timer module.
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    // Create timers.
    m_charge_timer = xTimerCreate("CHARGE",
                                   CHARGE_LEVEL_MEAS_INTERVAL,
                                   pdTRUE,
                                   NULL,
                                   charge_level_meas_timeout_handler);

    /* Error checking */
    if(NULL == m_charge_timer)
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }
}

/**@brief Function for application main entry.
 */
int main(void)
{
    bool erase_bonds;
    uint32_t err_code;

    bsp_board_init(BSP_INIT_LEDS);

    // Initialize modules.
    log_init();
    clock_init();
    gpio_init();
    uart_init();
    //initMorphy();

#ifdef FPU_INTERRUPT_MODE
    // Enable FPU interrupt
    NVIC_SetPriority(FPU_IRQn, APP_IRQ_PRIORITY_LOWEST);
    NVIC_ClearPendingIRQ(FPU_IRQn);
    NVIC_EnableIRQ(FPU_IRQn);
#endif

    // Do not start any interrupt that uses system functions before system initialisation.
    // The best solution is to start the OS before any other initalisation.

#if NRF_LOG_ENABLED
    // Start execution.
    if (pdPASS != xTaskCreate(logger_thread, "LOGGER", 256, NULL, 1, 0, &m_logger_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }
#endif


    if (pdPASS != xTaskCreate(morphy_app_thread, "Morphy", 256, NULL, 1, 10, &m_morphy_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }

    if (pdPASS != xTaskCreate(app_thread, "app1", 256, NULL, 1, 10, &m_app_thread))
    {
        APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
    }

    NRF_LOG_INFO("Morphy FreeRTOS example started.");
    // Start FreeRTOS scheduler.
    vTaskStartScheduler();

    for (;;)
    {
        APP_ERROR_HANDLER(NRF_ERROR_FORBIDDEN);
    }
}

