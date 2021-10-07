/*
 * File name  : main.c
 * Author     : KU Leuven
 *
 * Description: This file implements morphy's core functionalities: fast charging,
 * delayed brown-out, charge isolation and communication with the application via uart
 * for application task management
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

#include "mcc_generated_files/mcc.h"
#include<string.h>
#include "ConfigureCaps.h"


#define MAX_COMMAND_LEN 20

char msgOK[] = "0\n";
char command11[] ={0x00,0x31,0x31,0x0A};
char command12[] ={0x31,0x32,0x0A};
char command13[] ={0x31,0x33,0x0A};
char command14[] ={0x31,0x34,0x2C,0x32,0x2E,0x30,0x0A};
char command16[] ={0x31,0x36,0x0A};
char command17[] ={0x31,0x37,0x0A};
char command18[] ={0x31,0x38,0x0A};
char command19[] ={0x31,0x39,0x0A};
char command20[] ={0x00,0x31,0x31,0x0A};

extern volatile uint8_t Flag5sfastcharing; 
extern volatile uint8_t isolatedflag ;
 volatile uint8_t DectecLowVFlag =0;
 float getADCValue(void);
extern void Caps8seriesConnection(void);
extern void fastChargingcaps(void);
extern void isolatedOneTaskCap(void);

/*
                Main application
 */


/* Get sample value from channel_AND3 (GPIO RD3) */
/* ADC 10bit; VCC 3.3V */
float getADCValue(void)   
{
    float ADC_float = 0;
    adc_result_t getADCValue =0 ;
   
    getADCValue= ADCC_GetSingleConversion(channel_AND3);
    
    ADC_float =  getADCValue *(3.3 / 1023);
    return ADC_float;

}

uint8_t* ConvertADCtoSend(float convertedValue01)
{
    char msgValue[8] ;
    sprintf(msgValue,"%.2f" ,convertedValue01);
    return msgValue;
}

void DectecLowVolatge(void)
{
        LowVoltagePin_SetLow();  
        __delay_ms(1);
        LowVoltagePin_SetHigh();    
}


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
//15 -> reconfigCapArray
//OK <- 00
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



void executeCommand(char *command)
{  
    float ADCValue_float;
    adc_result_t getADCValue1;
    uint8_t* msgValue;
    
    if(strcmp(command, command11) == 0)
    {
        for(uint8_t i = 0; i < strlen(msgOK); i++)
        {
            EUSART5_Write(msgOK[i]);
        } 
    }
    
    if (strcmp(command, command12) == 0)
    {
        for(uint8_t i = 0; i < strlen(msgOK); i++)
        {
            EUSART5_Write(msgOK[i]);
        } 
    } 
    
    if (strcmp(command, command13) == 0)
    {
        ADCValue_float=getADCValue();
        msgValue= ConvertADCtoSend(ADCValue_float);
       
        msgValue[strlen(msgValue)-1] = 0x0A;
        for(uint8_t i = 0; i < strlen(msgValue); i++)
        {
          EUSART5_Write(msgValue[i]);
        }
    }
    
    if (memcmp(command, command14,4)== 0)
    {
        for(uint8_t i = 0; i < strlen(msgOK); i++)
        {
            EUSART5_Write(msgOK[i]);
        } 
        DectecLowVFlag =1;
    }
    
    if (strcmp(command, command16) == 0)
    {
        for(uint8_t i = 0; i < strlen(msgOK); i++)
        {
            EUSART5_Write(msgOK[i]);
        } 
    }
    
    if (strcmp(command, command17) == 0)
    {
        for(uint8_t i = 0; i < strlen(msgOK); i++)
        {
            EUSART5_Write(msgOK[i]);
        } 
    }
    
    if (memcmp(command, command20,3) == 0)
    {
        for(uint8_t i = 0; i < strlen(msgOK); i++)
        {
            EUSART5_Write(msgOK[i]);
        } 
    }
}


void main(void)
{   
    char c;
    char command[MAX_COMMAND_LEN];
    uint8_t index = 0;
 
    // Initialize the device
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    isolatedflag=0;
    Flag5sfastcharing=0;
    Caps8seriesConnection();
    
   while (1)
    {
       if((Flag5sfastcharing==1) &&(isolatedflag ==0) )
       {
           fastChargingcaps();
            Flag5sfastcharing =0;
       }
       else if (isolatedflag ==1)
       {
            isolatedOneTaskCap();
             LowVoltagePin_SetLow();   
             while(1)
             {
                   c= EUSART5_Read();
                    if(c != 0x0A)
                    {
                        command[index++] =c;
                    }
                    else if(c == 0x0A)
                    {
                        //EUSART2_Write(c);
                        command[index] = c;
                        command[index+1] = '\0';          
                        index =0;
                        executeCommand(command); 
                    }
                   if(DectecLowVFlag ==1)
                   {
                       delayedBrownOut();
                       if(isolatedflag ==0)
                       {
                           DectecLowVolatge();
                           __delay_ms(100);
                           VSYS_SW_SetLow();                       
                           break;
                       }                      
                   }
           }
       }
       
       
            
//         if(isolatedflag ==1)  // isolated a cap as output
//        {
//            isolatedOneTaskCap();
//            delayedBrownOut();
////            while(1)
////            {
////                  c= EUSART5_Read();
////            // Add your application code
////                if(c != 0x0A)
////                {
////                    command[index++] =c;
////                }
////                else if(c == 0x0A)
////                {
////                    //EUSART2_Write(c);
////                    command[index] = c;
////                    command[index+1] = '\0';          
////                    index =0;
////    //                executeCommand(command); 
////               }       
////            }        
//        }
    }
}

/**
 End of File
*/