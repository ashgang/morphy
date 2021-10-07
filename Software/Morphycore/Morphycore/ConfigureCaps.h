/* 
 * File:   ConfigureCaps.h
 * Author: Terry
 *
 * Created on October 7, 2021, 11:10 AM
 */

#ifndef CONFIGURECAPS_H
#define	CONFIGURECAPS_H
#include"stdbool.h"

#ifdef	__cplusplus
extern "C" {
#endif


   
    
void C_N_SWALLconnectGND(void);
void Caps8seriesConnection(void);
float sampleEHvoc(void);
float sampleChargingCapArray(void);
void decoupleCapArray(bool state);
void addCapToParallel( void);
void fastChargingcaps(void);
void isolatedOneTaskCap(void);
void delayedBrownOut();


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGURECAPS_H */

