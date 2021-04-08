/* ========================================
 *
 * ASSIGNMENT 02 - GROUP 08
 *
 * @authors Giovanni Parrella & Alessia Pesenti
 * @date 08/04/2021
 *
 * ========================================
*/
/*
 * RGB LED Color selection project - CY8CKIT-059 KIT - See TopDesign for more info on the hardware connections/settings.
 *
 * This project can be used to turn on a RGB LED, selecting the color through a custom GUI and UART communication.
 * Baude rate was set to 9600.
 * In order to communicate the color, the following packet must be sent: [0XA0(160), Red (0-255), Green(0-255), Blue(0-255), 0XC0(192)]
 * The timeout configuration can be useful when testing this code on a serial port terminal app (as CoolTerm). 
 * In order to communicate the timeout value, the following packet must be sent: [0XA1(161), timeout value(1-20), 0XC0(192)].

*/

#include "project.h"
#include "stdio.h"
#include "RGB_driver.h"
#include "InterruptRoutines.h"


static char message [20] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    
    // Start PWM and UART
    RGBLed_Start();
    UART_Start();
    
    // Initialize FLAGS and counters to IDLE (everything to 0, timer stopped)
    set_idle();
    
    // Initialize timeout to 5 seconds
    timeout = DEFAULT_5S; 
    
    // Start ISRs with custom functions
    isr_Timer_StartEx(Custom_Timer_ISR);
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
       
    for(;;)
    {
        if (flag == RECEIVED && byte_C == IDLE && byte_T == IDLE){
                    
                           
            switch(received) {
            case HEADER_COLOR:  byte_C = HEADER_RECEIVED; //note that = RECEIVING RED
                                //Start timeout
                                timer_count();
                                break;
                                        
            case HEADER_TIMER:  byte_T = HEADER_RECEIVED;
                                break;
                                        
            case CONNECTION_CMD:sprintf(message, "RGB LED Program $$$");   //If the command 'v' is received, print the string "RGB LED Program $$$"
                                //send through UART
                                UART_PutString(message);
                                set_idle();
                                break;
                    
            default:            break;
                    }
            flag = NOT_RECEIVED;  
                }
        
      //COLOR
    if(flag == RECEIVED && byte_C != IDLE ) 
        {   
              
            switch(byte_C){
                
            case RECEIVING_RED: input_color.red = received;           //Assigning RED to input_color
                    byte_C ++;
                    timer_count();
                    break;
                    
            case RECEIVING_GREEN: input_color.green = received;         //Assigning GREEN to input_color
                    byte_C ++;
                    timer_count();
                    break;
                    
            case RECEIVING_BLUE: input_color.blue = received;          //Assigning BLUE to input_color 
                    byte_C ++;
                    timer_count();
                    break;
                    
            case RECEIVING_TAIL: if(received == TAIL_VALUE){           //Check if TAIL is the correct one, otherwise wait for it (until time runs out)
                    RGBLed_setColor(input_color);         // Turn on the LED only if the correct TAIL is received
                    set_idle();
                    break;}
            
                    else break;
            
            default: break;
            }
            
            flag = NOT_RECEIVED;                          // Reset FLAG
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
