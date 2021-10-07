/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18LF67K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set C13_N_SW aliases
#define C13_N_SW_TRIS                 TRISAbits.TRISA1
#define C13_N_SW_LAT                  LATAbits.LATA1
#define C13_N_SW_PORT                 PORTAbits.RA1
#define C13_N_SW_WPU                  WPUAbits.WPUA1
#define C13_N_SW_OD                   ODCONAbits.ODCA1
#define C13_N_SW_ANS                  ANSELAbits.ANSELA1
#define C13_N_SW_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define C13_N_SW_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define C13_N_SW_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define C13_N_SW_GetValue()           PORTAbits.RA1
#define C13_N_SW_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define C13_N_SW_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define C13_N_SW_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define C13_N_SW_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define C13_N_SW_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define C13_N_SW_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define C13_N_SW_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define C13_N_SW_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set C12_N_SW aliases
#define C12_N_SW_TRIS                 TRISAbits.TRISA3
#define C12_N_SW_LAT                  LATAbits.LATA3
#define C12_N_SW_PORT                 PORTAbits.RA3
#define C12_N_SW_WPU                  WPUAbits.WPUA3
#define C12_N_SW_OD                   ODCONAbits.ODCA3
#define C12_N_SW_ANS                  ANSELAbits.ANSELA3
#define C12_N_SW_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define C12_N_SW_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define C12_N_SW_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define C12_N_SW_GetValue()           PORTAbits.RA3
#define C12_N_SW_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define C12_N_SW_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define C12_N_SW_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define C12_N_SW_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define C12_N_SW_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define C12_N_SW_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define C12_N_SW_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define C12_N_SW_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set C15_N_SW aliases
#define C15_N_SW_TRIS                 TRISBbits.TRISB0
#define C15_N_SW_LAT                  LATBbits.LATB0
#define C15_N_SW_PORT                 PORTBbits.RB0
#define C15_N_SW_WPU                  WPUBbits.WPUB0
#define C15_N_SW_OD                   ODCONBbits.ODCB0
#define C15_N_SW_ANS                  ANSELBbits.ANSELB0
#define C15_N_SW_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define C15_N_SW_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define C15_N_SW_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define C15_N_SW_GetValue()           PORTBbits.RB0
#define C15_N_SW_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define C15_N_SW_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define C15_N_SW_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define C15_N_SW_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define C15_N_SW_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define C15_N_SW_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define C15_N_SW_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define C15_N_SW_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set LowVoltagePin aliases
#define LowVoltagePin_TRIS                 TRISBbits.TRISB7
#define LowVoltagePin_LAT                  LATBbits.LATB7
#define LowVoltagePin_PORT                 PORTBbits.RB7
#define LowVoltagePin_WPU                  WPUBbits.WPUB7
#define LowVoltagePin_OD                   ODCONBbits.ODCB7
#define LowVoltagePin_ANS                  ANSELBbits.ANSELB7
#define LowVoltagePin_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define LowVoltagePin_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define LowVoltagePin_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define LowVoltagePin_GetValue()           PORTBbits.RB7
#define LowVoltagePin_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define LowVoltagePin_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define LowVoltagePin_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define LowVoltagePin_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define LowVoltagePin_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define LowVoltagePin_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define LowVoltagePin_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define LowVoltagePin_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set VSYS_SW aliases
#define VSYS_SW_TRIS                 TRISDbits.TRISD1
#define VSYS_SW_LAT                  LATDbits.LATD1
#define VSYS_SW_PORT                 PORTDbits.RD1
#define VSYS_SW_WPU                  WPUDbits.WPUD1
#define VSYS_SW_OD                   ODCONDbits.ODCD1
#define VSYS_SW_ANS                  ANSELDbits.ANSELD1
#define VSYS_SW_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define VSYS_SW_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define VSYS_SW_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define VSYS_SW_GetValue()           PORTDbits.RD1
#define VSYS_SW_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define VSYS_SW_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define VSYS_SW_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define VSYS_SW_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define VSYS_SW_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define VSYS_SW_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define VSYS_SW_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define VSYS_SW_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set VEH_SW aliases
#define VEH_SW_TRIS                 TRISDbits.TRISD2
#define VEH_SW_LAT                  LATDbits.LATD2
#define VEH_SW_PORT                 PORTDbits.RD2
#define VEH_SW_WPU                  WPUDbits.WPUD2
#define VEH_SW_OD                   ODCONDbits.ODCD2
#define VEH_SW_ANS                  ANSELDbits.ANSELD2
#define VEH_SW_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define VEH_SW_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define VEH_SW_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define VEH_SW_GetValue()           PORTDbits.RD2
#define VEH_SW_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define VEH_SW_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define VEH_SW_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define VEH_SW_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define VEH_SW_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define VEH_SW_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define VEH_SW_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define VEH_SW_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set channel_AND3 aliases
#define channel_AND3_TRIS                 TRISDbits.TRISD3
#define channel_AND3_LAT                  LATDbits.LATD3
#define channel_AND3_PORT                 PORTDbits.RD3
#define channel_AND3_WPU                  WPUDbits.WPUD3
#define channel_AND3_OD                   ODCONDbits.ODCD3
#define channel_AND3_ANS                  ANSELDbits.ANSELD3
#define channel_AND3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define channel_AND3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define channel_AND3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define channel_AND3_GetValue()           PORTDbits.RD3
#define channel_AND3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define channel_AND3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define channel_AND3_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define channel_AND3_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define channel_AND3_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define channel_AND3_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define channel_AND3_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define channel_AND3_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set C16_N_SW aliases
#define C16_N_SW_TRIS                 TRISDbits.TRISD6
#define C16_N_SW_LAT                  LATDbits.LATD6
#define C16_N_SW_PORT                 PORTDbits.RD6
#define C16_N_SW_WPU                  WPUDbits.WPUD6
#define C16_N_SW_OD                   ODCONDbits.ODCD6
#define C16_N_SW_ANS                  ANSELDbits.ANSELD6
#define C16_N_SW_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define C16_N_SW_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define C16_N_SW_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define C16_N_SW_GetValue()           PORTDbits.RD6
#define C16_N_SW_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define C16_N_SW_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define C16_N_SW_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define C16_N_SW_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define C16_N_SW_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define C16_N_SW_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define C16_N_SW_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define C16_N_SW_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set C4_P_SW aliases
#define C4_P_SW_TRIS                 TRISEbits.TRISE0
#define C4_P_SW_LAT                  LATEbits.LATE0
#define C4_P_SW_PORT                 PORTEbits.RE0
#define C4_P_SW_WPU                  WPUEbits.WPUE0
#define C4_P_SW_OD                   ODCONEbits.ODCE0
#define C4_P_SW_ANS                  ANSELEbits.ANSELE0
#define C4_P_SW_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define C4_P_SW_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define C4_P_SW_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define C4_P_SW_GetValue()           PORTEbits.RE0
#define C4_P_SW_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define C4_P_SW_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define C4_P_SW_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define C4_P_SW_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define C4_P_SW_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define C4_P_SW_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define C4_P_SW_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define C4_P_SW_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set C4_N_SW aliases
#define C4_N_SW_TRIS                 TRISEbits.TRISE1
#define C4_N_SW_LAT                  LATEbits.LATE1
#define C4_N_SW_PORT                 PORTEbits.RE1
#define C4_N_SW_WPU                  WPUEbits.WPUE1
#define C4_N_SW_OD                   ODCONEbits.ODCE1
#define C4_N_SW_ANS                  ANSELEbits.ANSELE1
#define C4_N_SW_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define C4_N_SW_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define C4_N_SW_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define C4_N_SW_GetValue()           PORTEbits.RE1
#define C4_N_SW_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define C4_N_SW_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define C4_N_SW_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define C4_N_SW_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define C4_N_SW_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define C4_N_SW_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define C4_N_SW_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define C4_N_SW_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set RE2 procedures
#define RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define RE2_GetValue()              PORTEbits.RE2
#define RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define RE2_SetPullup()             do { WPUEbits.WPUE2 = 1; } while(0)
#define RE2_ResetPullup()           do { WPUEbits.WPUE2 = 0; } while(0)
#define RE2_SetAnalogMode()         do { ANSELEbits.ANSELE2 = 1; } while(0)
#define RE2_SetDigitalMode()        do { ANSELEbits.ANSELE2 = 0; } while(0)

// get/set RE3 procedures
#define RE3_SetHigh()            do { LATEbits.LATE3 = 1; } while(0)
#define RE3_SetLow()             do { LATEbits.LATE3 = 0; } while(0)
#define RE3_Toggle()             do { LATEbits.LATE3 = ~LATEbits.LATE3; } while(0)
#define RE3_GetValue()              PORTEbits.RE3
#define RE3_SetDigitalInput()    do { TRISEbits.TRISE3 = 1; } while(0)
#define RE3_SetDigitalOutput()   do { TRISEbits.TRISE3 = 0; } while(0)
#define RE3_SetPullup()             do { WPUEbits.WPUE3 = 1; } while(0)
#define RE3_ResetPullup()           do { WPUEbits.WPUE3 = 0; } while(0)
#define RE3_SetAnalogMode()         do { ANSELEbits.ANSELE3 = 1; } while(0)
#define RE3_SetDigitalMode()        do { ANSELEbits.ANSELE3 = 0; } while(0)

// get/set C3_P_SW aliases
#define C3_P_SW_TRIS                 TRISEbits.TRISE4
#define C3_P_SW_LAT                  LATEbits.LATE4
#define C3_P_SW_PORT                 PORTEbits.RE4
#define C3_P_SW_WPU                  WPUEbits.WPUE4
#define C3_P_SW_OD                   ODCONEbits.ODCE4
#define C3_P_SW_ANS                  ANSELEbits.ANSELE4
#define C3_P_SW_SetHigh()            do { LATEbits.LATE4 = 1; } while(0)
#define C3_P_SW_SetLow()             do { LATEbits.LATE4 = 0; } while(0)
#define C3_P_SW_Toggle()             do { LATEbits.LATE4 = ~LATEbits.LATE4; } while(0)
#define C3_P_SW_GetValue()           PORTEbits.RE4
#define C3_P_SW_SetDigitalInput()    do { TRISEbits.TRISE4 = 1; } while(0)
#define C3_P_SW_SetDigitalOutput()   do { TRISEbits.TRISE4 = 0; } while(0)
#define C3_P_SW_SetPullup()          do { WPUEbits.WPUE4 = 1; } while(0)
#define C3_P_SW_ResetPullup()        do { WPUEbits.WPUE4 = 0; } while(0)
#define C3_P_SW_SetPushPull()        do { ODCONEbits.ODCE4 = 0; } while(0)
#define C3_P_SW_SetOpenDrain()       do { ODCONEbits.ODCE4 = 1; } while(0)
#define C3_P_SW_SetAnalogMode()      do { ANSELEbits.ANSELE4 = 1; } while(0)
#define C3_P_SW_SetDigitalMode()     do { ANSELEbits.ANSELE4 = 0; } while(0)

// get/set C3_N_SW aliases
#define C3_N_SW_TRIS                 TRISEbits.TRISE5
#define C3_N_SW_LAT                  LATEbits.LATE5
#define C3_N_SW_PORT                 PORTEbits.RE5
#define C3_N_SW_WPU                  WPUEbits.WPUE5
#define C3_N_SW_OD                   ODCONEbits.ODCE5
#define C3_N_SW_ANS                  ANSELEbits.ANSELE5
#define C3_N_SW_SetHigh()            do { LATEbits.LATE5 = 1; } while(0)
#define C3_N_SW_SetLow()             do { LATEbits.LATE5 = 0; } while(0)
#define C3_N_SW_Toggle()             do { LATEbits.LATE5 = ~LATEbits.LATE5; } while(0)
#define C3_N_SW_GetValue()           PORTEbits.RE5
#define C3_N_SW_SetDigitalInput()    do { TRISEbits.TRISE5 = 1; } while(0)
#define C3_N_SW_SetDigitalOutput()   do { TRISEbits.TRISE5 = 0; } while(0)
#define C3_N_SW_SetPullup()          do { WPUEbits.WPUE5 = 1; } while(0)
#define C3_N_SW_ResetPullup()        do { WPUEbits.WPUE5 = 0; } while(0)
#define C3_N_SW_SetPushPull()        do { ODCONEbits.ODCE5 = 0; } while(0)
#define C3_N_SW_SetOpenDrain()       do { ODCONEbits.ODCE5 = 1; } while(0)
#define C3_N_SW_SetAnalogMode()      do { ANSELEbits.ANSELE5 = 1; } while(0)
#define C3_N_SW_SetDigitalMode()     do { ANSELEbits.ANSELE5 = 0; } while(0)

// get/set C2_P_SW aliases
#define C2_P_SW_TRIS                 TRISEbits.TRISE6
#define C2_P_SW_LAT                  LATEbits.LATE6
#define C2_P_SW_PORT                 PORTEbits.RE6
#define C2_P_SW_WPU                  WPUEbits.WPUE6
#define C2_P_SW_OD                   ODCONEbits.ODCE6
#define C2_P_SW_ANS                  ANSELEbits.ANSELE6
#define C2_P_SW_SetHigh()            do { LATEbits.LATE6 = 1; } while(0)
#define C2_P_SW_SetLow()             do { LATEbits.LATE6 = 0; } while(0)
#define C2_P_SW_Toggle()             do { LATEbits.LATE6 = ~LATEbits.LATE6; } while(0)
#define C2_P_SW_GetValue()           PORTEbits.RE6
#define C2_P_SW_SetDigitalInput()    do { TRISEbits.TRISE6 = 1; } while(0)
#define C2_P_SW_SetDigitalOutput()   do { TRISEbits.TRISE6 = 0; } while(0)
#define C2_P_SW_SetPullup()          do { WPUEbits.WPUE6 = 1; } while(0)
#define C2_P_SW_ResetPullup()        do { WPUEbits.WPUE6 = 0; } while(0)
#define C2_P_SW_SetPushPull()        do { ODCONEbits.ODCE6 = 0; } while(0)
#define C2_P_SW_SetOpenDrain()       do { ODCONEbits.ODCE6 = 1; } while(0)
#define C2_P_SW_SetAnalogMode()      do { ANSELEbits.ANSELE6 = 1; } while(0)
#define C2_P_SW_SetDigitalMode()     do { ANSELEbits.ANSELE6 = 0; } while(0)

// get/set C2_N_SW aliases
#define C2_N_SW_TRIS                 TRISEbits.TRISE7
#define C2_N_SW_LAT                  LATEbits.LATE7
#define C2_N_SW_PORT                 PORTEbits.RE7
#define C2_N_SW_WPU                  WPUEbits.WPUE7
#define C2_N_SW_OD                   ODCONEbits.ODCE7
#define C2_N_SW_ANS                  ANSELEbits.ANSELE7
#define C2_N_SW_SetHigh()            do { LATEbits.LATE7 = 1; } while(0)
#define C2_N_SW_SetLow()             do { LATEbits.LATE7 = 0; } while(0)
#define C2_N_SW_Toggle()             do { LATEbits.LATE7 = ~LATEbits.LATE7; } while(0)
#define C2_N_SW_GetValue()           PORTEbits.RE7
#define C2_N_SW_SetDigitalInput()    do { TRISEbits.TRISE7 = 1; } while(0)
#define C2_N_SW_SetDigitalOutput()   do { TRISEbits.TRISE7 = 0; } while(0)
#define C2_N_SW_SetPullup()          do { WPUEbits.WPUE7 = 1; } while(0)
#define C2_N_SW_ResetPullup()        do { WPUEbits.WPUE7 = 0; } while(0)
#define C2_N_SW_SetPushPull()        do { ODCONEbits.ODCE7 = 0; } while(0)
#define C2_N_SW_SetOpenDrain()       do { ODCONEbits.ODCE7 = 1; } while(0)
#define C2_N_SW_SetAnalogMode()      do { ANSELEbits.ANSELE7 = 1; } while(0)
#define C2_N_SW_SetDigitalMode()     do { ANSELEbits.ANSELE7 = 0; } while(0)

// get/set C10_N_SW aliases
#define C10_N_SW_TRIS                 TRISFbits.TRISF1
#define C10_N_SW_LAT                  LATFbits.LATF1
#define C10_N_SW_PORT                 PORTFbits.RF1
#define C10_N_SW_WPU                  WPUFbits.WPUF1
#define C10_N_SW_OD                   ODCONFbits.ODCF1
#define C10_N_SW_ANS                  ANSELFbits.ANSELF1
#define C10_N_SW_SetHigh()            do { LATFbits.LATF1 = 1; } while(0)
#define C10_N_SW_SetLow()             do { LATFbits.LATF1 = 0; } while(0)
#define C10_N_SW_Toggle()             do { LATFbits.LATF1 = ~LATFbits.LATF1; } while(0)
#define C10_N_SW_GetValue()           PORTFbits.RF1
#define C10_N_SW_SetDigitalInput()    do { TRISFbits.TRISF1 = 1; } while(0)
#define C10_N_SW_SetDigitalOutput()   do { TRISFbits.TRISF1 = 0; } while(0)
#define C10_N_SW_SetPullup()          do { WPUFbits.WPUF1 = 1; } while(0)
#define C10_N_SW_ResetPullup()        do { WPUFbits.WPUF1 = 0; } while(0)
#define C10_N_SW_SetPushPull()        do { ODCONFbits.ODCF1 = 0; } while(0)
#define C10_N_SW_SetOpenDrain()       do { ODCONFbits.ODCF1 = 1; } while(0)
#define C10_N_SW_SetAnalogMode()      do { ANSELFbits.ANSELF1 = 1; } while(0)
#define C10_N_SW_SetDigitalMode()     do { ANSELFbits.ANSELF1 = 0; } while(0)

// get/set C9_P_SW aliases
#define C9_P_SW_TRIS                 TRISFbits.TRISF2
#define C9_P_SW_LAT                  LATFbits.LATF2
#define C9_P_SW_PORT                 PORTFbits.RF2
#define C9_P_SW_WPU                  WPUFbits.WPUF2
#define C9_P_SW_OD                   ODCONFbits.ODCF2
#define C9_P_SW_ANS                  ANSELFbits.ANSELF2
#define C9_P_SW_SetHigh()            do { LATFbits.LATF2 = 1; } while(0)
#define C9_P_SW_SetLow()             do { LATFbits.LATF2 = 0; } while(0)
#define C9_P_SW_Toggle()             do { LATFbits.LATF2 = ~LATFbits.LATF2; } while(0)
#define C9_P_SW_GetValue()           PORTFbits.RF2
#define C9_P_SW_SetDigitalInput()    do { TRISFbits.TRISF2 = 1; } while(0)
#define C9_P_SW_SetDigitalOutput()   do { TRISFbits.TRISF2 = 0; } while(0)
#define C9_P_SW_SetPullup()          do { WPUFbits.WPUF2 = 1; } while(0)
#define C9_P_SW_ResetPullup()        do { WPUFbits.WPUF2 = 0; } while(0)
#define C9_P_SW_SetPushPull()        do { ODCONFbits.ODCF2 = 0; } while(0)
#define C9_P_SW_SetOpenDrain()       do { ODCONFbits.ODCF2 = 1; } while(0)
#define C9_P_SW_SetAnalogMode()      do { ANSELFbits.ANSELF2 = 1; } while(0)
#define C9_P_SW_SetDigitalMode()     do { ANSELFbits.ANSELF2 = 0; } while(0)

// get/set C9_N_SW aliases
#define C9_N_SW_TRIS                 TRISFbits.TRISF3
#define C9_N_SW_LAT                  LATFbits.LATF3
#define C9_N_SW_PORT                 PORTFbits.RF3
#define C9_N_SW_WPU                  WPUFbits.WPUF3
#define C9_N_SW_OD                   ODCONFbits.ODCF3
#define C9_N_SW_ANS                  ANSELFbits.ANSELF3
#define C9_N_SW_SetHigh()            do { LATFbits.LATF3 = 1; } while(0)
#define C9_N_SW_SetLow()             do { LATFbits.LATF3 = 0; } while(0)
#define C9_N_SW_Toggle()             do { LATFbits.LATF3 = ~LATFbits.LATF3; } while(0)
#define C9_N_SW_GetValue()           PORTFbits.RF3
#define C9_N_SW_SetDigitalInput()    do { TRISFbits.TRISF3 = 1; } while(0)
#define C9_N_SW_SetDigitalOutput()   do { TRISFbits.TRISF3 = 0; } while(0)
#define C9_N_SW_SetPullup()          do { WPUFbits.WPUF3 = 1; } while(0)
#define C9_N_SW_ResetPullup()        do { WPUFbits.WPUF3 = 0; } while(0)
#define C9_N_SW_SetPushPull()        do { ODCONFbits.ODCF3 = 0; } while(0)
#define C9_N_SW_SetOpenDrain()       do { ODCONFbits.ODCF3 = 1; } while(0)
#define C9_N_SW_SetAnalogMode()      do { ANSELFbits.ANSELF3 = 1; } while(0)
#define C9_N_SW_SetDigitalMode()     do { ANSELFbits.ANSELF3 = 0; } while(0)

// get/set C8_P_SW aliases
#define C8_P_SW_TRIS                 TRISFbits.TRISF4
#define C8_P_SW_LAT                  LATFbits.LATF4
#define C8_P_SW_PORT                 PORTFbits.RF4
#define C8_P_SW_WPU                  WPUFbits.WPUF4
#define C8_P_SW_OD                   ODCONFbits.ODCF4
#define C8_P_SW_ANS                  ANSELFbits.ANSELF4
#define C8_P_SW_SetHigh()            do { LATFbits.LATF4 = 1; } while(0)
#define C8_P_SW_SetLow()             do { LATFbits.LATF4 = 0; } while(0)
#define C8_P_SW_Toggle()             do { LATFbits.LATF4 = ~LATFbits.LATF4; } while(0)
#define C8_P_SW_GetValue()           PORTFbits.RF4
#define C8_P_SW_SetDigitalInput()    do { TRISFbits.TRISF4 = 1; } while(0)
#define C8_P_SW_SetDigitalOutput()   do { TRISFbits.TRISF4 = 0; } while(0)
#define C8_P_SW_SetPullup()          do { WPUFbits.WPUF4 = 1; } while(0)
#define C8_P_SW_ResetPullup()        do { WPUFbits.WPUF4 = 0; } while(0)
#define C8_P_SW_SetPushPull()        do { ODCONFbits.ODCF4 = 0; } while(0)
#define C8_P_SW_SetOpenDrain()       do { ODCONFbits.ODCF4 = 1; } while(0)
#define C8_P_SW_SetAnalogMode()      do { ANSELFbits.ANSELF4 = 1; } while(0)
#define C8_P_SW_SetDigitalMode()     do { ANSELFbits.ANSELF4 = 0; } while(0)

// get/set C8_N_SW aliases
#define C8_N_SW_TRIS                 TRISFbits.TRISF5
#define C8_N_SW_LAT                  LATFbits.LATF5
#define C8_N_SW_PORT                 PORTFbits.RF5
#define C8_N_SW_WPU                  WPUFbits.WPUF5
#define C8_N_SW_OD                   ODCONFbits.ODCF5
#define C8_N_SW_ANS                  ANSELFbits.ANSELF5
#define C8_N_SW_SetHigh()            do { LATFbits.LATF5 = 1; } while(0)
#define C8_N_SW_SetLow()             do { LATFbits.LATF5 = 0; } while(0)
#define C8_N_SW_Toggle()             do { LATFbits.LATF5 = ~LATFbits.LATF5; } while(0)
#define C8_N_SW_GetValue()           PORTFbits.RF5
#define C8_N_SW_SetDigitalInput()    do { TRISFbits.TRISF5 = 1; } while(0)
#define C8_N_SW_SetDigitalOutput()   do { TRISFbits.TRISF5 = 0; } while(0)
#define C8_N_SW_SetPullup()          do { WPUFbits.WPUF5 = 1; } while(0)
#define C8_N_SW_ResetPullup()        do { WPUFbits.WPUF5 = 0; } while(0)
#define C8_N_SW_SetPushPull()        do { ODCONFbits.ODCF5 = 0; } while(0)
#define C8_N_SW_SetOpenDrain()       do { ODCONFbits.ODCF5 = 1; } while(0)
#define C8_N_SW_SetAnalogMode()      do { ANSELFbits.ANSELF5 = 1; } while(0)
#define C8_N_SW_SetDigitalMode()     do { ANSELFbits.ANSELF5 = 0; } while(0)

// get/set C7_P_SW aliases
#define C7_P_SW_TRIS                 TRISFbits.TRISF6
#define C7_P_SW_LAT                  LATFbits.LATF6
#define C7_P_SW_PORT                 PORTFbits.RF6
#define C7_P_SW_WPU                  WPUFbits.WPUF6
#define C7_P_SW_OD                   ODCONFbits.ODCF6
#define C7_P_SW_ANS                  ANSELFbits.ANSELF6
#define C7_P_SW_SetHigh()            do { LATFbits.LATF6 = 1; } while(0)
#define C7_P_SW_SetLow()             do { LATFbits.LATF6 = 0; } while(0)
#define C7_P_SW_Toggle()             do { LATFbits.LATF6 = ~LATFbits.LATF6; } while(0)
#define C7_P_SW_GetValue()           PORTFbits.RF6
#define C7_P_SW_SetDigitalInput()    do { TRISFbits.TRISF6 = 1; } while(0)
#define C7_P_SW_SetDigitalOutput()   do { TRISFbits.TRISF6 = 0; } while(0)
#define C7_P_SW_SetPullup()          do { WPUFbits.WPUF6 = 1; } while(0)
#define C7_P_SW_ResetPullup()        do { WPUFbits.WPUF6 = 0; } while(0)
#define C7_P_SW_SetPushPull()        do { ODCONFbits.ODCF6 = 0; } while(0)
#define C7_P_SW_SetOpenDrain()       do { ODCONFbits.ODCF6 = 1; } while(0)
#define C7_P_SW_SetAnalogMode()      do { ANSELFbits.ANSELF6 = 1; } while(0)
#define C7_P_SW_SetDigitalMode()     do { ANSELFbits.ANSELF6 = 0; } while(0)

// get/set C7_N_SW aliases
#define C7_N_SW_TRIS                 TRISFbits.TRISF7
#define C7_N_SW_LAT                  LATFbits.LATF7
#define C7_N_SW_PORT                 PORTFbits.RF7
#define C7_N_SW_WPU                  WPUFbits.WPUF7
#define C7_N_SW_OD                   ODCONFbits.ODCF7
#define C7_N_SW_ANS                  ANSELFbits.ANSELF7
#define C7_N_SW_SetHigh()            do { LATFbits.LATF7 = 1; } while(0)
#define C7_N_SW_SetLow()             do { LATFbits.LATF7 = 0; } while(0)
#define C7_N_SW_Toggle()             do { LATFbits.LATF7 = ~LATFbits.LATF7; } while(0)
#define C7_N_SW_GetValue()           PORTFbits.RF7
#define C7_N_SW_SetDigitalInput()    do { TRISFbits.TRISF7 = 1; } while(0)
#define C7_N_SW_SetDigitalOutput()   do { TRISFbits.TRISF7 = 0; } while(0)
#define C7_N_SW_SetPullup()          do { WPUFbits.WPUF7 = 1; } while(0)
#define C7_N_SW_ResetPullup()        do { WPUFbits.WPUF7 = 0; } while(0)
#define C7_N_SW_SetPushPull()        do { ODCONFbits.ODCF7 = 0; } while(0)
#define C7_N_SW_SetOpenDrain()       do { ODCONFbits.ODCF7 = 1; } while(0)
#define C7_N_SW_SetAnalogMode()      do { ANSELFbits.ANSELF7 = 1; } while(0)
#define C7_N_SW_SetDigitalMode()     do { ANSELFbits.ANSELF7 = 0; } while(0)

// get/set C5_N_SW aliases
#define C5_N_SW_TRIS                 TRISGbits.TRISG0
#define C5_N_SW_LAT                  LATGbits.LATG0
#define C5_N_SW_PORT                 PORTGbits.RG0
#define C5_N_SW_WPU                  WPUGbits.WPUG0
#define C5_N_SW_OD                   ODCONGbits.ODCG0
#define C5_N_SW_ANS                  ANSELGbits.ANSELG0
#define C5_N_SW_SetHigh()            do { LATGbits.LATG0 = 1; } while(0)
#define C5_N_SW_SetLow()             do { LATGbits.LATG0 = 0; } while(0)
#define C5_N_SW_Toggle()             do { LATGbits.LATG0 = ~LATGbits.LATG0; } while(0)
#define C5_N_SW_GetValue()           PORTGbits.RG0
#define C5_N_SW_SetDigitalInput()    do { TRISGbits.TRISG0 = 1; } while(0)
#define C5_N_SW_SetDigitalOutput()   do { TRISGbits.TRISG0 = 0; } while(0)
#define C5_N_SW_SetPullup()          do { WPUGbits.WPUG0 = 1; } while(0)
#define C5_N_SW_ResetPullup()        do { WPUGbits.WPUG0 = 0; } while(0)
#define C5_N_SW_SetPushPull()        do { ODCONGbits.ODCG0 = 0; } while(0)
#define C5_N_SW_SetOpenDrain()       do { ODCONGbits.ODCG0 = 1; } while(0)
#define C5_N_SW_SetAnalogMode()      do { ANSELGbits.ANSELG0 = 1; } while(0)
#define C5_N_SW_SetDigitalMode()     do { ANSELGbits.ANSELG0 = 0; } while(0)

// get/set C5_P_SW aliases
#define C5_P_SW_TRIS                 TRISGbits.TRISG1
#define C5_P_SW_LAT                  LATGbits.LATG1
#define C5_P_SW_PORT                 PORTGbits.RG1
#define C5_P_SW_WPU                  WPUGbits.WPUG1
#define C5_P_SW_OD                   ODCONGbits.ODCG1
#define C5_P_SW_ANS                  ANSELGbits.ANSELG1
#define C5_P_SW_SetHigh()            do { LATGbits.LATG1 = 1; } while(0)
#define C5_P_SW_SetLow()             do { LATGbits.LATG1 = 0; } while(0)
#define C5_P_SW_Toggle()             do { LATGbits.LATG1 = ~LATGbits.LATG1; } while(0)
#define C5_P_SW_GetValue()           PORTGbits.RG1
#define C5_P_SW_SetDigitalInput()    do { TRISGbits.TRISG1 = 1; } while(0)
#define C5_P_SW_SetDigitalOutput()   do { TRISGbits.TRISG1 = 0; } while(0)
#define C5_P_SW_SetPullup()          do { WPUGbits.WPUG1 = 1; } while(0)
#define C5_P_SW_ResetPullup()        do { WPUGbits.WPUG1 = 0; } while(0)
#define C5_P_SW_SetPushPull()        do { ODCONGbits.ODCG1 = 0; } while(0)
#define C5_P_SW_SetOpenDrain()       do { ODCONGbits.ODCG1 = 1; } while(0)
#define C5_P_SW_SetAnalogMode()      do { ANSELGbits.ANSELG1 = 1; } while(0)
#define C5_P_SW_SetDigitalMode()     do { ANSELGbits.ANSELG1 = 0; } while(0)

// get/set C6_N_SW aliases
#define C6_N_SW_TRIS                 TRISGbits.TRISG2
#define C6_N_SW_LAT                  LATGbits.LATG2
#define C6_N_SW_PORT                 PORTGbits.RG2
#define C6_N_SW_WPU                  WPUGbits.WPUG2
#define C6_N_SW_OD                   ODCONGbits.ODCG2
#define C6_N_SW_ANS                  ANSELGbits.ANSELG2
#define C6_N_SW_SetHigh()            do { LATGbits.LATG2 = 1; } while(0)
#define C6_N_SW_SetLow()             do { LATGbits.LATG2 = 0; } while(0)
#define C6_N_SW_Toggle()             do { LATGbits.LATG2 = ~LATGbits.LATG2; } while(0)
#define C6_N_SW_GetValue()           PORTGbits.RG2
#define C6_N_SW_SetDigitalInput()    do { TRISGbits.TRISG2 = 1; } while(0)
#define C6_N_SW_SetDigitalOutput()   do { TRISGbits.TRISG2 = 0; } while(0)
#define C6_N_SW_SetPullup()          do { WPUGbits.WPUG2 = 1; } while(0)
#define C6_N_SW_ResetPullup()        do { WPUGbits.WPUG2 = 0; } while(0)
#define C6_N_SW_SetPushPull()        do { ODCONGbits.ODCG2 = 0; } while(0)
#define C6_N_SW_SetOpenDrain()       do { ODCONGbits.ODCG2 = 1; } while(0)
#define C6_N_SW_SetAnalogMode()      do { ANSELGbits.ANSELG2 = 1; } while(0)
#define C6_N_SW_SetDigitalMode()     do { ANSELGbits.ANSELG2 = 0; } while(0)

// get/set C6_P_SW aliases
#define C6_P_SW_TRIS                 TRISGbits.TRISG3
#define C6_P_SW_LAT                  LATGbits.LATG3
#define C6_P_SW_PORT                 PORTGbits.RG3
#define C6_P_SW_WPU                  WPUGbits.WPUG3
#define C6_P_SW_OD                   ODCONGbits.ODCG3
#define C6_P_SW_ANS                  ANSELGbits.ANSELG3
#define C6_P_SW_SetHigh()            do { LATGbits.LATG3 = 1; } while(0)
#define C6_P_SW_SetLow()             do { LATGbits.LATG3 = 0; } while(0)
#define C6_P_SW_Toggle()             do { LATGbits.LATG3 = ~LATGbits.LATG3; } while(0)
#define C6_P_SW_GetValue()           PORTGbits.RG3
#define C6_P_SW_SetDigitalInput()    do { TRISGbits.TRISG3 = 1; } while(0)
#define C6_P_SW_SetDigitalOutput()   do { TRISGbits.TRISG3 = 0; } while(0)
#define C6_P_SW_SetPullup()          do { WPUGbits.WPUG3 = 1; } while(0)
#define C6_P_SW_ResetPullup()        do { WPUGbits.WPUG3 = 0; } while(0)
#define C6_P_SW_SetPushPull()        do { ODCONGbits.ODCG3 = 0; } while(0)
#define C6_P_SW_SetOpenDrain()       do { ODCONGbits.ODCG3 = 1; } while(0)
#define C6_P_SW_SetAnalogMode()      do { ANSELGbits.ANSELG3 = 1; } while(0)
#define C6_P_SW_SetDigitalMode()     do { ANSELGbits.ANSELG3 = 0; } while(0)

// get/set C11_N_SW aliases
#define C11_N_SW_TRIS                 TRISGbits.TRISG7
#define C11_N_SW_LAT                  LATGbits.LATG7
#define C11_N_SW_PORT                 PORTGbits.RG7
#define C11_N_SW_WPU                  WPUGbits.WPUG7
#define C11_N_SW_OD                   ODCONGbits.ODCG7
#define C11_N_SW_ANS                  ANSELGbits.ANSELG7
#define C11_N_SW_SetHigh()            do { LATGbits.LATG7 = 1; } while(0)
#define C11_N_SW_SetLow()             do { LATGbits.LATG7 = 0; } while(0)
#define C11_N_SW_Toggle()             do { LATGbits.LATG7 = ~LATGbits.LATG7; } while(0)
#define C11_N_SW_GetValue()           PORTGbits.RG7
#define C11_N_SW_SetDigitalInput()    do { TRISGbits.TRISG7 = 1; } while(0)
#define C11_N_SW_SetDigitalOutput()   do { TRISGbits.TRISG7 = 0; } while(0)
#define C11_N_SW_SetPullup()          do { WPUGbits.WPUG7 = 1; } while(0)
#define C11_N_SW_ResetPullup()        do { WPUGbits.WPUG7 = 0; } while(0)
#define C11_N_SW_SetPushPull()        do { ODCONGbits.ODCG7 = 0; } while(0)
#define C11_N_SW_SetOpenDrain()       do { ODCONGbits.ODCG7 = 1; } while(0)
#define C11_N_SW_SetAnalogMode()      do { ANSELGbits.ANSELG7 = 1; } while(0)
#define C11_N_SW_SetDigitalMode()     do { ANSELGbits.ANSELG7 = 0; } while(0)

// get/set C14_N_SW aliases
#define C14_N_SW_TRIS                 TRISHbits.TRISH1
#define C14_N_SW_LAT                  LATHbits.LATH1
#define C14_N_SW_PORT                 PORTHbits.RH1
#define C14_N_SW_WPU                  WPUHbits.WPUH1
#define C14_N_SW_OD                   ODCONHbits.ODCH1
#define C14_N_SW_SetHigh()            do { LATHbits.LATH1 = 1; } while(0)
#define C14_N_SW_SetLow()             do { LATHbits.LATH1 = 0; } while(0)
#define C14_N_SW_Toggle()             do { LATHbits.LATH1 = ~LATHbits.LATH1; } while(0)
#define C14_N_SW_GetValue()           PORTHbits.RH1
#define C14_N_SW_SetDigitalInput()    do { TRISHbits.TRISH1 = 1; } while(0)
#define C14_N_SW_SetDigitalOutput()   do { TRISHbits.TRISH1 = 0; } while(0)
#define C14_N_SW_SetPullup()          do { WPUHbits.WPUH1 = 1; } while(0)
#define C14_N_SW_ResetPullup()        do { WPUHbits.WPUH1 = 0; } while(0)
#define C14_N_SW_SetPushPull()        do { ODCONHbits.ODCH1 = 0; } while(0)
#define C14_N_SW_SetOpenDrain()       do { ODCONHbits.ODCH1 = 1; } while(0)

// get/set C1_P_SW aliases
#define C1_P_SW_TRIS                 TRISHbits.TRISH2
#define C1_P_SW_LAT                  LATHbits.LATH2
#define C1_P_SW_PORT                 PORTHbits.RH2
#define C1_P_SW_WPU                  WPUHbits.WPUH2
#define C1_P_SW_OD                   ODCONHbits.ODCH2
#define C1_P_SW_SetHigh()            do { LATHbits.LATH2 = 1; } while(0)
#define C1_P_SW_SetLow()             do { LATHbits.LATH2 = 0; } while(0)
#define C1_P_SW_Toggle()             do { LATHbits.LATH2 = ~LATHbits.LATH2; } while(0)
#define C1_P_SW_GetValue()           PORTHbits.RH2
#define C1_P_SW_SetDigitalInput()    do { TRISHbits.TRISH2 = 1; } while(0)
#define C1_P_SW_SetDigitalOutput()   do { TRISHbits.TRISH2 = 0; } while(0)
#define C1_P_SW_SetPullup()          do { WPUHbits.WPUH2 = 1; } while(0)
#define C1_P_SW_ResetPullup()        do { WPUHbits.WPUH2 = 0; } while(0)
#define C1_P_SW_SetPushPull()        do { ODCONHbits.ODCH2 = 0; } while(0)
#define C1_P_SW_SetOpenDrain()       do { ODCONHbits.ODCH2 = 1; } while(0)

// get/set C1_N_SW aliases
#define C1_N_SW_TRIS                 TRISHbits.TRISH3
#define C1_N_SW_LAT                  LATHbits.LATH3
#define C1_N_SW_PORT                 PORTHbits.RH3
#define C1_N_SW_WPU                  WPUHbits.WPUH3
#define C1_N_SW_OD                   ODCONHbits.ODCH3
#define C1_N_SW_SetHigh()            do { LATHbits.LATH3 = 1; } while(0)
#define C1_N_SW_SetLow()             do { LATHbits.LATH3 = 0; } while(0)
#define C1_N_SW_Toggle()             do { LATHbits.LATH3 = ~LATHbits.LATH3; } while(0)
#define C1_N_SW_GetValue()           PORTHbits.RH3
#define C1_N_SW_SetDigitalInput()    do { TRISHbits.TRISH3 = 1; } while(0)
#define C1_N_SW_SetDigitalOutput()   do { TRISHbits.TRISH3 = 0; } while(0)
#define C1_N_SW_SetPullup()          do { WPUHbits.WPUH3 = 1; } while(0)
#define C1_N_SW_ResetPullup()        do { WPUHbits.WPUH3 = 0; } while(0)
#define C1_N_SW_SetPushPull()        do { ODCONHbits.ODCH3 = 0; } while(0)
#define C1_N_SW_SetOpenDrain()       do { ODCONHbits.ODCH3 = 1; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/