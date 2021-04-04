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
#include "project.h"
#include "stdio.h"
#include "RGB_driver.h"
#include "InterruptRoutines.h"

volatile uint8_t byte_C, byte_T, seconds, timeout;
volatile uint8_t header_C, header_T,status,connection;
volatile color input_color;

extern volatile uint8_t b;
static char message [20] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

      /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    RGBLed_Start();
    UART_Start();
    
    set_idle();//init
    timeout = 5; 
    
    isr_Timer_StartEx(Custom_TIMER_ISR);
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
       
    for(;;)
    {
        /* Place your application code here. */
        
        
        switch(byte_C){
 
            case 5: RGBLed_setColor(input_color);// turn on the LED
                    set_idle(); // Get ready for next color
                    break;
                
            default: break;
        }
        
        switch(byte_T){
            
            case 3: set_idle();
                    break;
            
            default: break;
            }
        
        if (connection == RECEIVED && b == 0){
            sprintf(message, "RGB LED Program $$$\r\n");
            //send through UART
            UART_PutString(message);
            b++;
        }
        
       
    }

}

/* [] END OF FILE */
