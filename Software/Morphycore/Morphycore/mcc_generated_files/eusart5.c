/**
  EUSART5 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart5.c

  @Summary
    This is the generated driver implementation file for the EUSART5 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for EUSART5.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18LF67K40
        Driver Version    :  2.1.1
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

/**
  Section: Included Files
*/
#include "eusart5.h"

volatile eusart5_status_t eusart5RxLastError;

/**
  Section: EUSART5 APIs
*/

void (*EUSART5_FramingErrorHandler)(void);
void (*EUSART5_OverrunErrorHandler)(void);
void (*EUSART5_ErrorHandler)(void);

void EUSART5_DefaultFramingErrorHandler(void);
void EUSART5_DefaultOverrunErrorHandler(void);
void EUSART5_DefaultErrorHandler(void);

void EUSART5_Initialize(void)
{
    // Set the EUSART5 module to the options selected in the user interface.

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD5CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC5STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX5STA = 0x24;

    // SP5BRGL 25; 
    SP5BRGL = 0x19;

    // SP5BRGH 0; 
    SP5BRGH = 0x00;


    EUSART5_SetFramingErrorHandler(EUSART5_DefaultFramingErrorHandler);
    EUSART5_SetOverrunErrorHandler(EUSART5_DefaultOverrunErrorHandler);
    EUSART5_SetErrorHandler(EUSART5_DefaultErrorHandler);

    eusart5RxLastError.status = 0;

}

bool EUSART5_is_tx_ready(void)
{
    return (bool)(PIR4bits.TX5IF && TX5STAbits.TXEN);
}

bool EUSART5_is_rx_ready(void)
{
    return (bool)(PIR4bits.RC5IF);
}

bool EUSART5_is_tx_done(void)
{
    return TX5STAbits.TRMT;
}

eusart5_status_t EUSART5_get_last_status(void){
    return eusart5RxLastError;
}

uint8_t EUSART5_Read(void)
{
    while(!PIR4bits.RC5IF)
    {
    }

    eusart5RxLastError.status = 0;
    
    if(1 == RC5STAbits.OERR)
    {
        // EUSART5 error - restart

        RC5STAbits.CREN = 0; 
        RC5STAbits.CREN = 1; 
    }

    return RC5REG;
}

void EUSART5_Write(uint8_t txData)
{
    while(0 == PIR4bits.TX5IF)
    {
    }

    TX5REG = txData;    // Write the data byte to the USART.
}

char getch(void)
{
    return EUSART5_Read();
}

void putch(char txData)
{
    EUSART5_Write(txData);
}



void EUSART5_DefaultFramingErrorHandler(void){}

void EUSART5_DefaultOverrunErrorHandler(void){
    // EUSART5 error - restart

    RC5STAbits.CREN = 0;
    RC5STAbits.CREN = 1;

}

void EUSART5_DefaultErrorHandler(void){
}

void EUSART5_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART5_FramingErrorHandler = interruptHandler;
}

void EUSART5_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART5_OverrunErrorHandler = interruptHandler;
}

void EUSART5_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART5_ErrorHandler = interruptHandler;
}


/**
  End of File
*/
