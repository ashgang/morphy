/* 
 * File name  : morphy.c
 * Author     : KU Leuven
 * Description: This file implements the morphy client library apis for the interaction with the morphy module
 * The APIs in this module are called either within FreeRTOS for task control or from the application to interact with morphy module
 * The APIs are adapted for nRF board and the accompanying FreeRTOS implementation
 * This file is an extension to the FreeRTOS kernel and adapts the same license as FreeRTOS
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include "FreeRTOS.h"
#include "morphy.h"
#include <string.h>
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


/****************** CMDS ****************
nRF - PIC ++++++++++++++++
11 -> SetMaxVoltage
OK <- 00
12 -> SetMinVoltage
OK <- 00
13 -> getCoreVoltage
<> <- <Current Voltage>
14 -> setLowVoltageAlarm
OK <- 00
15 -> reconfigCapArray
OK <- 00
16 -> scheduleInterrupt
OK <- 00
17 -> schedulePowerOn
OK <- 00
18 <- handleBrownOut
OK -> 00
19 <- handlePowerBug
20 -> runTask
OK <- 00
****************************************/
bugHandler bugH;
brownoutHandler boH; 
volatile uint8_t currentTaskBug = 0;
static uint8_t freeTask = MAX_MORPHY_TASK;
static uint8_t allocTaskID[MAX_MORPHY_TASK] = {1,2,3,4,5,6,7,8,9,10};
static uint8_t taskIndex = 0;
static uint16_t taskStartVoltage = 0;
static uint16_t taskEndVoltage = 0;
static uint8_t currTaskID = 0;

tskPwrMap_t taskPwrMap[MAX_MORPHY_TASK];

bool initMorphy()
{
    for (int i = 0; i < MAX_MORPHY_TASK; i++) {
        taskPwrMap[i].semValue = 0;
        taskPwrMap[i].tCharge = 0;
        taskPwrMap[i].taskID = 0;
        taskPwrMap[i].taskBug = false;
    }
    charge_monitor_timer();
}

bool setMaxVoltage(uint16_t max_v)
{
    uint8_t maxV[3] = "3.6\n";
    int retVal = -1;

    uint8_t cmd[10] = "11,";
    uint8_t resp[10] = {0}, dataSize = 0;

    strcat(cmd, maxV);

    if (uart_tx_data(cmd, 7)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    if (retVal == 0)
        return true;
    else
        return false;
}

bool setMinVoltage(uint16_t min_v)
{
    uint8_t maxV[3] = "3.0\n";
    int retVal = -1;

    uint8_t cmd[10] = "12,";
    uint8_t resp[10] = {0}, dataSize = 0;

    strcat(cmd, maxV);

    if (uart_tx_data(cmd, 7)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    if (retVal == 0)
        return true;
    else
        return false;
}

float getCoreVoltage()
{
    float coreV = 0;
    uint8_t cmd[5] = "13\n";
    uint8_t resp[10] = {0}, dataSize = 0; 

    if (uart_tx_data(cmd, 3)) {
        if (uart_rx_data(resp, &dataSize)) {
            coreV = atof(resp);
        }
    }

    return coreV;
}

bool setLowVoltageAlarm(float alarm_v)
{
    uint8_t alrmV[3] = {0};
    int retVal = -1;
    uint8_t cmd[10] = "14,";
    uint8_t resp[10] = {0}, dataSize = 0;

    uint8_t bufLen = sprintf(alrmV, "%0.1f", alarm_v);
    strcat(cmd, alrmV);
    //memcpy(&cmd[3], alrmV, 3);
    //bufLen = bufLen+3;
    cmd[6] = 0x0A;
    cmd[7] = 0;

    //strcat(cmd, alrmV);
    //strcat(cmd, "\n");
    //uint16_t test = alarm_v*1000;

    NRF_LOG_INFO("%s\r\n", cmd);
    NRF_LOG_FLUSH();

    if (uart_tx_data(cmd, 7)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    if (retVal == 0)
        return true;
    else
        return false;
}

uint8_t addTask(uint16_t charge)
{
    uint8_t taskid = 0;
    
    if(taskIndex >= MAX_MORPHY_TASK) {
        //Max task limit reached
        return 0;
    }
    
    taskPwrMap[taskIndex].tCharge = charge;
    taskPwrMap[taskIndex].taskID = allocTaskID[taskIndex];
    taskid = taskPwrMap[taskIndex].taskID;
    freeTask--;
    taskIndex++;

    //uart_tx_data(charge);
    //while(uart_rx_data(&taskid, len) != true);

    //The current implementation does not go to UART

    return taskid;
}

void charge_level_meas_timeout_handler(TimerHandle_t xTimer)
{
    UNUSED_PARAMETER(xTimer);
    float coreV = getCoreVoltage();
    uint16_t charge = 100 * coreV; //100mF cap, charge assigned to task is in mC, so we do this

    taskEndVoltage = charge;
    
    if ((taskStartVoltage - taskEndVoltage) > taskPwrMap[currTaskID-1].tCharge) {
        //Set bug here
    }

}

uint8_t runTask(uint8_t taskID)
{
    uint8_t cmd[10] = "20\n", resp[5] = {0}, dataSize = 0, retVal = 0;

    if (uart_tx_data(cmd, 3)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    //if (retVal == 0)
    //    return 1;
    //else
    //    return 0;
    float coreV = getCoreVoltage(); //1;
    uint16_t charge = 100 * coreV; //100mF cap, charge assigned to task is in mC, so we do this

    taskStartVoltage = charge;

    if (charge > taskPwrMap[taskID-1].tCharge) {
        //start_charge_monitoring();
        currTaskID = taskID;
        return 1;
    }
    return 0;
}

bool reconfigCapArray(uint8_t noOfCaps, bool paraConf)
{
    uint8_t tbuf[3] = {0};
    int retVal = -1;
    uint8_t cmd[11] = "15,";
    uint8_t resp[10] = {0}, dataSize = 0;

    uint8_t bufLen = sprintf(tbuf, "%02d", noOfCaps);
    strcat(cmd, tbuf);
    strcat(cmd, ",");
    memset(tbuf, 0, 3);
    sprintf(tbuf, "%02d", paraConf);
    //memcpy(&cmd[7], tbuf, 2);
    strcat(cmd, tbuf);
    cmd[9] = 0x0A;
    cmd[10] = 0;

    //strcat(cmd, alrmV);
    //strcat(cmd, "\n");
    //uint16_t test = alarm_v*1000;
    //cmd[6] = 0x2C;

    NRF_LOG_INFO("%s\r\n", cmd);
    NRF_LOG_FLUSH();

    if (uart_tx_data(cmd, 10)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    if (retVal == 0)
        return true;
    else
        return false;
}

bool scheduleInterrupt(uint16_t timeout)
{
    uint8_t alrmV[5] = {0};
    int retVal = -1;
    uint8_t cmd[15] = "16,";
    uint8_t resp[10] = {0}, dataSize = 0;

    uint8_t bufLen = sprintf(alrmV, "%d", timeout);
    strcat(cmd, alrmV);
    bufLen = bufLen+3;
    cmd[bufLen] = 0x0A;

    NRF_LOG_INFO("%s\r\n", cmd);
    NRF_LOG_FLUSH();

    if (uart_tx_data(cmd, bufLen)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    if (retVal == 0)
        return true;
    else
        return false;
}

bool schedulePowerOn(uint16_t timeout)
{
    uint8_t alrmV[5] = {0};
    int retVal = -1;
    uint8_t cmd[15] = "17,";
    uint8_t resp[10] = {0}, dataSize = 0;

    uint8_t bufLen = sprintf(alrmV, "%d", timeout);
    strcat(cmd, alrmV);
    bufLen = bufLen+3;
    cmd[bufLen] = 0x0A;

    NRF_LOG_INFO("%s\r\n", cmd);
    NRF_LOG_FLUSH();

    if (uart_tx_data(cmd, bufLen)) {
        if (uart_rx_data(resp, &dataSize)) {
            retVal = atoi(resp);
        }
    }

    if (retVal == 0)
        return true;
    else
        return false;
}

void powerDown()
{
    //put the device to shutdown
    nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_STAY_IN_SYSOFF);
}

tskPwrMap_t* getSemaphores()
{
    //Comm with Morphy module, if required
    
    return taskPwrMap;
}

void setBugHandler(bugHandler f1)
{
    bugH = f1;
}

void setBrownoutHandler(brownoutHandler f2)
{
    boH = f2;
}

bool blacklist(uint8_t TaskID)
{
    bool retVal = false;

    //retVal = uart_tx_data(TaskID);
    return retVal;
}

bool releaseBlacklist(uint8_t TaskID)
{
    bool retVal = false;

    //retVal = uart_tx_data(TaskID);
    return retVal;
}

uint8_t* getBlacklist()
{
    uint8_t blArray[MAX_MORPHY_TASK] = {0};

    //Comm with Morphy module
    //retVal = uart_tx_data(cmd);
    //while(uart_rx_data(&blArray, len) != true);

    return blArray;
}

uint8_t morphyGetBugLevel()
{
    if (taskPwrMap[currTaskID].taskBug == true)
        return 1;
    else
        return 0;
}

//This is a callbacks from other MCU
void morphyCallBugHandler(uint8_t *buf, uint8_t datasize)
{
    uint8_t taskID;

    currentTaskBug = 1;
    taskPwrMap[currTaskID].taskBug = true;
    
    if (bugH != NULL)
        bugH(taskID);
}

//This is a callbacks from other MCU
void morphyCallBrownoutHandler()
{
    if (boH != NULL)
        boH();
    //vTaskEndScheduler();
    nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_STAY_IN_SYSOFF);
}
