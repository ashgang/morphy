/*
** Morphy extension
*/

#include <stdlib.h>
#include "FreeRTOS.h"
#include "morphy.h"
#include <string.h>
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
****************************************/

typedef void (*bugHandler)(uint8_t buggyTaskID);
typedef void (*brownoutHandler)();
bugHandler bugH;
brownoutHandler boH; 
volatile uint8_t currentTaskBug = 0;
static uint8_t freeTask = MAX_MORPHY_TASK;
static uint8_t allocTaskID[MAX_MORPHY_TASK] = {1,2,3,4,5,6,7,8,9,10};
static uint8_t taskIndex = 0;
static uint16_t taskStartVoltage = 0;
static uint16_t taskEndVoltage = 0;
static uint8_t currTaskID = 0;

typedef struct {
    uint8_t taskID;
    uint16_t tCharge;
    bool semValue;
}tskPwrMap_t;
tskPwrMap_t taskPwrMap[MAX_MORPHY_TASK];

bool initMorphy()
{
    for (int i = 0; i < MAX_MORPHY_TASK; i++) {
        taskPwrMap[i].semValue = 0;
        taskPwrMap[i].tCharge = 0;
        taskPwrMap[i].taskID = 0;
    }
    charge_monitor_timer();
}

bool setMaxVoltage(uint16_t max_v)
{
    uint8_t maxV[3] = "3.5\n";
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
    uint8_t maxV[3] = "3.5\n";
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
    float coreV = 1;//getCoreVoltage();
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
    bool retVal = false;

    //retVal = uart_tx_data(alarm_v);
    return retVal;
}

bool schedulePowerOn(uint16_t timeout)
{
    bool retVal = false;

    //retVal = uart_tx_data(alarm_v);
    return retVal;
}

void powerDown()
{
    //put the device to shutdown
    //nrf_pwr_mgmt_shutdown(NRF_PWR_MGMT_SHUTDOWN_STAY_IN_SYSOFF);
}


uint8_t getSemaphoreNextTask(uint8_t TaskID)
{
    bool retVal = false;
    uint8_t semTask = 0;
    currentTaskBug = 0;

    //retVal = uart_tx_data(TaskID);
    //while(uart_rx_data(&semTask, len) != true);
    return semTask;
}

uint8_t* getSemaphores()
{
    uint8_t semArray[MAX_MORPHY_TASK] = {0};
    currentTaskBug = 0;
    //Comm with Morphy module
    
    return semArray;
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

//This is a callbacks from other MCU
void morphySetBugHandler()
{
    uint8_t taskID;

    currentTaskBug = 1;
    //while(uart_rx_data(&taskID, len) != true);
    bugH(taskID);
}

uint8_t morphyGetBugLevel()
{
    return currentTaskBug;
}

//This is a callbacks from other MCU
void morphySetBrownoutHandler()
{
    boH();
    vTaskEndScheduler();
}
