/*
** Morphy extension
*/
#ifndef MORPHY_H
#define MORPHY_H

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#define MAX_MORPHY_TASK 10

typedef void (*bugHandler)(uint8_t buggyTaskID);
typedef void (*brownoutHandler)();

typedef struct {
    uint8_t taskID;
    uint16_t tCharge;
    bool semValue;
    bool taskBug;
}tskPwrMap_t;

uint8_t addTask(uint16_t charge);
uint8_t runTask(uint8_t taskID);
bool setMaxVoltage(uint16_t max_v);
bool setMinVoltage(uint16_t min_v);
float getCoreVoltage();
bool setLowVoltageAlarm(float alarm_v);
bool reconfigCapArray(uint8_t noOfCaps, bool paraConf);
bool scheduleInterrupt(uint16_t timeout);
bool schedulePowerOn(uint16_t timeout);
void powerDown();
tskPwrMap_t* getSemaphores();
void setBugHandler(bugHandler f1);
void setBrownoutHandler(brownoutHandler f2);
void morphyCallBugHandler(uint8_t *buf, uint8_t datasize);
void morphyCallBrownoutHandler();
uint8_t morphyGetBugLevel();
void charge_level_meas_timeout_handler(TimerHandle_t xTimer);

bool uart_tx_data(uint8_t *buf, uint8_t dataSize);
bool uart_rx_data(uint8_t *buf, uint8_t *dataSize);

#endif