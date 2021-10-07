/* 
 * File name  : morphy.h
 * Author     : KU Leuven
 * Description: This file defines the morphy client library apis for the interaction with the morphy module
 * The APIs in this module are called either within FreeRTOS for task control or from the application to interact with morphy module
 * The APIs are adapted for nRF board and the accompanying FreeRTOS implementation
 * This file is an extension to the FreeRTOS kernel and adapts the same license as FreeRTOS\
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