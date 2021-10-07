# 1 "RunTask.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-K_DFP/1.4.87/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "RunTask.c" 2
# 1 "./Fastcharge.h" 1
# 11 "./Fastcharge.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.32\\pic\\include\\c99\\stdbool.h" 1 3
# 11 "./Fastcharge.h" 2






void C_N_SWALLconnectGND(void);
void Caps8seriesConnection(void);
float sampleEHvoc(void);
float sampleChargingCapArray(void);
void decoupleCapArray(_Bool state);
void addCapToParallel( void);
void fastChargingcaps(void);
void isolatedOneTaskCap(void);
# 1 "RunTask.c" 2

# 1 "./RunTask.h" 1
# 15 "./RunTask.h"
float sampleTaskCapArray(void);
void isolateCapsToSeries(void);
void delayedBrownOut();
# 2 "RunTask.c" 2




float sampleTaskCapArray(void)
{
 float vcap = 0;


 return vcap;
}
void isolateCapsToSeries(void)
{

}
# 25 "RunTask.c"
void delayedBrownOut()
{
 float vcap = 0.0;

 vcap = sampleTaskCapArray();

 if (vcap <= (2.7 * 1.1)) {

  isolateCapsToSeries();
 }
 else {

 }
}
