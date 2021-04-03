/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "RGB_driver.h"
#include "InterruptRoutines.h"
#include "project.h"


volatile uint8_t byte_C,byte_T, header_C, header_T, status, received, seconds;
//volatile uint16_t period;
volatile char b;
static void RGBLed_WriteRed (uint8_t red);
static void RGBLed_Writegreen (uint8_t green);
static void RGBLed_Writeblue (uint8_t blue);

void set_idle(){
    
        //reset all FLAGS and timer
        header_C = HEADER_NOT_RECEIVED;
        byte_C = NOT_RECEIVED;
    
        header_T = HEADER_NOT_RECEIVED;
        byte_T = NOT_RECEIVED;    
    
        seconds = 0;
        Timer_Stop();
        
        status = FREE;
        received = NOT_RECEIVED;
     
        b=0;
    }


//function which will start PWM
void RGBLed_Start()
    {
        PWM_RG_Start();
        PWM_B_Start();
        }
    
    
//function which starts the timeout  
void timer_count(){
            Timer_Stop();
            seconds = 0;
            Timer_WriteCounter(999);
            Timer_Start();
}
    
    
//functions which will set the color
void RGBLed_setColor(color c)    
    {   
           RGBLed_WriteRed(c.red);
           RGBLed_Writegreen(c.green);
           RGBLed_Writeblue(c.blue);
    }
     
static void RGBLed_WriteRed (uint8_t red)
{
    PWM_RG_WriteCompare1(red);
}
static void RGBLed_Writegreen (uint8_t green)
{
    PWM_RG_WriteCompare2(green);
}
static void RGBLed_Writeblue (uint8_t blue)
{
    PWM_B_WriteCompare(blue);
}


/* [] END OF FILE */
