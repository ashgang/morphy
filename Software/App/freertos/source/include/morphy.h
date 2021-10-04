/*
** Morphy extension
*/
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#define MAX_MORPHY_TASK 10

uint8_t addTask(uint16_t charge);
uint8_t runTask(uint8_t taskID);
bool setMaxVoltage(uint16_t max_v);
bool setMinVoltage(uint16_t min_v);
float getCoreVoltage();
bool setLowVoltageAlarm(float alarm_v);
bool reconfigCapArray(uint8_t noOfCaps, bool paraConf);
uint16_t morphyGetCharge();
uint8_t *morphyGetSemaphores();
void morphySetBugHandler();
void morphySetBrownoutHandler();
uint8_t morphyGetBugLevel();
void morphyNotifyTaskChange(uint8_t morphyTaskID);
void charge_level_meas_timeout_handler(TimerHandle_t xTimer);


bool uart_tx_data(uint8_t *buf, uint8_t dataSize);
bool uart_rx_data(uint8_t *buf, uint8_t *dataSize);
