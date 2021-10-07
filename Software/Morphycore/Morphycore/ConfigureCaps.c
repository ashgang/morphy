/*
 * File name  : ConfigureCaps.c
 * Author     : KU Leuven
 *
 * Description: This file implements morphy's core functionalities: fast charging,
 * delayed brown-out, charge isolation. 
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



#include "ConfigureCaps.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"
#include"mcc_generated_files/adcc.h"

static  float voc_prev = 0.0, voc_current = 0.0;
static  float vcap_prev = 0.0, vcap_current = 0.0;
static  uint8_t  cap_count = 0;
static  uint8_t capParalle_count =0;
static  uint8_t capSeries_count =0;
static  uint8_t capTaskParalle_count =0;
static  uint8_t capTaskSeries_count =0;

extern float getADCValue(void);
#define BO_VOLTAGE  2.7
    
volatile uint8_t isolatedflag = 0;

void C_N_SWALLconnectGND(void)
{
    C1_N_SW_SetLow();
    C2_N_SW_SetLow();
    C3_N_SW_SetLow();
    C4_N_SW_SetLow();
    C5_N_SW_SetLow();
    C6_N_SW_SetLow();
    C7_N_SW_SetLow();
    C8_N_SW_SetLow();
    C9_N_SW_SetLow();
    C10_N_SW_SetLow();
    C11_N_SW_SetLow();
    C12_N_SW_SetLow();
    C13_N_SW_SetLow();
    C14_N_SW_SetLow();
    C15_N_SW_SetLow();
    C16_N_SW_SetLow();
}


void Caps8seriesConnection(void)
{
    VEH_SW_SetHigh();
    VSYS_SW_SetLow();
    
    // Connect the first Cap and not connect to the second. 
    C1_P_SW_SetHigh();
    C2_P_SW_SetLow();
    C3_P_SW_SetLow();
    C4_P_SW_SetLow();
    C5_P_SW_SetLow();
    C6_P_SW_SetLow();
    C7_P_SW_SetLow();
    C8_P_SW_SetLow();
    C9_P_SW_SetLow();
    
    C_N_SWALLconnectGND();
    C1_N_SW_SetHigh();
    C2_N_SW_SetHigh();
    C3_N_SW_SetHigh();
    C4_N_SW_SetHigh();
    C5_N_SW_SetHigh();
    C6_N_SW_SetHigh();
    C7_N_SW_SetHigh();
    capSeries_count=8;
    capParalle_count =0; 
}



float sampleEHvoc(void)
{
    float voc =0;
    // 
    VEH_SW_SetHigh();
    VSYS_SW_SetLow();
    C1_P_SW_SetLow();
    
    voc=getADCValue();
    
    voc_prev = voc_current;
    voc_current = voc;
    return voc;
}

float sampleChargingCapArray(void)
{
    float vcap = 0;
    //Sample adc for the current voltage of the charging cap array
    VEH_SW_SetLow();
    VSYS_SW_SetLow();
    C1_P_SW_SetHigh();
    
    vcap=getADCValue();
    
    vcap_prev = vcap_current;
    vcap_current = vcap;
    
    return vcap;
}

void decoupleCapArray(bool state)
{
    //open the switch here to decouple cap from the EH source (solar panel)
    if (state == 1) { //decouple
         C1_P_SW_SetLow();
    }
    else { //couple
         VEH_SW_SetHigh();
         C1_P_SW_SetHigh();
    }
}


void addCapToParallel( void)
{
	//Add one more cap to parallel charging config
    switch(capParalle_count)
    {
        case 0 :               
                C8_P_SW_SetHigh();
                C9_P_SW_SetLow();    
                
                C7_N_SW_SetLow();
                //printf("\r\n CAP78 in parallel \r\n"); 
               // 6 CAPS IN SERIES AND 2 CAP IN PARALLEL
                capParalle_count =2;
                capSeries_count=6;
                break;
           
        case 2:
                C9_P_SW_SetLow();  
                C8_P_SW_SetHigh();
                C7_P_SW_SetHigh();
                
                C7_N_SW_SetLow();  
                C6_N_SW_SetLow();  
                //printf("\r\n CAP678 in parallel \r\n");
                // 5 CAPS IN SERIES AND 3 CAP IN PARALLEL
                capParalle_count =3;
                capSeries_count=5;
                break;
        
        case 3:
                C9_P_SW_SetLow();  
                C8_P_SW_SetHigh();
                C7_P_SW_SetHigh();
                C6_P_SW_SetHigh();
                
                C7_N_SW_SetLow();  
                C6_N_SW_SetLow(); 
                C5_N_SW_SetLow();
                //printf("\r\n CAP5678 in parallel \r\n");
                // 4 CAPS IN SERIES AND 4 CAP IN PARALLEL
                capParalle_count =4;
                capSeries_count=4;
                 break;
        
        case 4:
                C9_P_SW_SetLow();  
                C8_P_SW_SetHigh();
                C7_P_SW_SetHigh();
                C6_P_SW_SetHigh();
                C5_P_SW_SetHigh();
                
                C7_N_SW_SetLow();  
                C6_N_SW_SetLow(); 
                C5_N_SW_SetLow();
                C4_N_SW_SetLow();
                
                //printf("\r\n CAP45678 in parallel \r\n");
                // 4 CAPS IN SERIES AND 4 CAP IN PARALLEL
                capParalle_count =5;
                capSeries_count=3;
                 break;
                 
         case 5:
                C9_P_SW_SetLow();  
                C8_P_SW_SetHigh();
                C7_P_SW_SetHigh();
                C6_P_SW_SetHigh();
                C5_P_SW_SetHigh();
                C4_P_SW_SetHigh();
                
                C7_N_SW_SetLow();  
                C6_N_SW_SetLow(); 
                C5_N_SW_SetLow();
                C4_N_SW_SetLow();
                C3_N_SW_SetLow();
                //printf("\r\n CAP345678 in parallel \r\n");
                // 2 CAPS IN SERIES AND 6 CAP IN PARALLEL
                capParalle_count =6;
                capSeries_count=2;
                 break;
            case 6:
                C9_P_SW_SetLow();  
                C8_P_SW_SetHigh();
                C7_P_SW_SetHigh();
                C6_P_SW_SetHigh();
                C5_P_SW_SetHigh();
                C4_P_SW_SetHigh();
                C3_P_SW_SetHigh();

                C7_N_SW_SetLow();  
                C6_N_SW_SetLow(); 
                C5_N_SW_SetLow();
                C4_N_SW_SetLow();
                C3_N_SW_SetLow();
                C2_N_SW_SetLow();
                //printf("\r\n CAP2345678 in parallel \r\n");
           // 1 CAPS IN SERIES AND 7 CAP IN PARALLEL
                capParalle_count =7;
                capSeries_count=1;
            break;
            
            case 7:
                C9_P_SW_SetLow();  
                C8_P_SW_SetHigh();
                C7_P_SW_SetHigh();
                C6_P_SW_SetHigh();
                C5_P_SW_SetHigh();
                C4_P_SW_SetHigh();
                C3_P_SW_SetHigh();
                C2_P_SW_SetHigh();

                C7_N_SW_SetLow();  
                C6_N_SW_SetLow(); 
                C5_N_SW_SetLow();
                C4_N_SW_SetLow();
                C3_N_SW_SetLow();
                C2_N_SW_SetLow();
                C1_N_SW_SetLow();
                //printf("\r\n CAP12345678 in parallel \r\n");
           // 1 CAPS IN SERIES AND 7 CAP IN PARALLEL
                capParalle_count =8;
                capSeries_count=0;
            break;
                 
            default:
                  //printf("\r\n%d \r\n", capParalle_count);
                break;
    }
}


float sampleTaskCapArray()
{
            float vcap = 0;
            //Sample adc for the current voltage of the cap array isolated for task
            VSYS_SW_SetLow();
            VEH_SW_SetLow();
            vcap= getADCValue();    

            return vcap;
}

void isolateCapsToSeries(void)
{
    
    //Here add more cap to series to up the voltage
    VSYS_SW_SetLow();
    VEH_SW_SetLow();
    
    switch(capTaskSeries_count)
    {
        case 1:
            C1_N_SW_SetHigh();
            C2_P_SW_SetLow(); 
           
            VEH_SW_SetHigh();
            capTaskSeries_count=2;
            capTaskParalle_count=6;
            //printf("\r\n CAP12 in SERIES \r\n"); 
            break;
             
        case 2:
            C1_N_SW_SetHigh();
            C2_N_SW_SetHigh();
            
            C2_P_SW_SetLow(); 
            C3_P_SW_SetLow(); 
            
            VEH_SW_SetHigh();
            
            capTaskSeries_count=3;
            capTaskParalle_count=5;
            //printf("\r\n CAP123 in SERIES \r\n"); 
            break;
             
        case 3:
            C1_N_SW_SetHigh();
            C2_N_SW_SetHigh();
            C3_N_SW_SetHigh();
            
            C2_P_SW_SetLow(); 
            C3_P_SW_SetLow(); 
            C4_P_SW_SetLow(); 
            
            VEH_SW_SetHigh();
        
            capTaskSeries_count=4;
            capTaskParalle_count=4;      
            //printf("\r\n CAP1234 in SERIES \r\n"); 
            break;
        case 4:
            C1_N_SW_SetHigh();
            C2_N_SW_SetHigh();
            C3_N_SW_SetHigh();
            C4_N_SW_SetHigh();
            
            C2_P_SW_SetLow(); 
            C3_P_SW_SetLow(); 
            C4_P_SW_SetLow(); 
            C5_P_SW_SetLow(); 
            
            VEH_SW_SetHigh();
        
            capTaskSeries_count=5;
            capTaskParalle_count=3;  
            //printf("\r\n CAP12345 in SERIES \r\n"); 
            break;
         case 5:
            C1_N_SW_SetHigh();
            C2_N_SW_SetHigh();
            C3_N_SW_SetHigh();
            C4_N_SW_SetHigh();
            C5_N_SW_SetHigh();
            
            C2_P_SW_SetLow(); 
            C3_P_SW_SetLow(); 
            C4_P_SW_SetLow(); 
            C5_P_SW_SetLow(); 
            C6_P_SW_SetLow(); 
            
            VEH_SW_SetHigh();
        
            capTaskSeries_count=6;
            capTaskParalle_count=2;     
            //printf("\r\n CAP123456 in SERIES \r\n"); 
            break;
        
        case 6:
            C1_N_SW_SetHigh();
            C2_N_SW_SetHigh();
            C3_N_SW_SetHigh();
            C4_N_SW_SetHigh();
            C5_N_SW_SetHigh();
            C6_N_SW_SetHigh();
            
            C2_P_SW_SetLow(); 
            C3_P_SW_SetLow(); 
            C4_P_SW_SetLow(); 
            C5_P_SW_SetLow(); 
            C6_P_SW_SetLow(); 
            C7_P_SW_SetLow(); 
            
            VEH_SW_SetHigh();
        
            capTaskSeries_count=7;
            capTaskParalle_count=1;     
            //printf("\r\n CAP1234567 in SERIES \r\n"); 
            break;
        
        case 7:
            C1_N_SW_SetHigh();
            C2_N_SW_SetHigh();
            C3_N_SW_SetHigh();
            C4_N_SW_SetHigh();
            C5_N_SW_SetHigh();
            C6_N_SW_SetHigh();
            C7_N_SW_SetHigh();
            
            C2_P_SW_SetLow(); 
            C3_P_SW_SetLow(); 
            C4_P_SW_SetLow(); 
            C5_P_SW_SetLow(); 
            C6_P_SW_SetLow(); 
            C7_P_SW_SetLow(); 
            C8_P_SW_SetLow(); 
            C9_P_SW_SetLow(); 
            
            VEH_SW_SetHigh();
        
            capTaskSeries_count=8;
            capTaskParalle_count=0;  
             //printf("\r\n CAP12345678 in SERIES \r\n"); 
            break;
            default:
                //printf("\r\n add all SERIES \r\n");
                break; 
    }
    
}


void delayedBrownOut()
{
	float vcap = 0.0;
	
	vcap = sampleTaskCapArray();
	
	if (vcap <= (BO_VOLTAGE * 1.1) &&  capTaskSeries_count != 8 ) {
		//add caps to series
                   // printf("\r\n %.2f \r\n",vcap);
		isolateCapsToSeries(); 
	}        
	else if(vcap <= BO_VOLTAGE ) 
        {
		//do nothing
            isolatedflag=0;
         }
}


void isolatedOneTaskCap(void)
{
    VEH_SW_SetLow();
    C1_P_SW_SetLow(); 
    VSYS_SW_SetHigh(); 
    
    capTaskParalle_count =7;
    capTaskSeries_count =1;
}


void fastChargingcaps(void) 
{
    float voc = 0;
    float vcap = 0;
    
   decoupleCapArray(1);
   
   voc=sampleEHvoc();
//   printf("\r\n voc =%.2f\r\n", voc);
//   printf("\r\n voc_prev =%.2f\r\n", voc_prev);
    
   vcap = sampleChargingCapArray();
//   printf("\r\n vcap =%.2f\r\n", vcap);
//   printf("\r\n vcap_prev =%.2f\r\n", vcap_prev);

   if (vcap >(0.9 * voc_current))
    {
        addCapToParallel();
     }
    else if (voc_current >= voc_prev || vcap_current > vcap_prev) 
            {
                 //do nothing
             }
   
//   if(vcap_current < vcap_prev)
//   {
//    //wait for three samples, if it still drops, remove cap from parallel if possible
//        cap_count++;
//        if (cap_count >= 3) 
//        {
//            //add cap to series, if possible, else maintain status quo
//            //addCapToSeries();
//            cap_count = 0;
//        }
//   }
   
   if(capParalle_count ==8 )
        {
             if(vcap > 3.29)
             {
                    //printf("\r\n Now the volatge of the paraller caps is up to 3.3v \r\n");
                    isolatedflag=1;
             }

        }
   
     decoupleCapArray(0);     
}



