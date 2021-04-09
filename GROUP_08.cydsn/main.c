/* ========================================
 *
 * ASSIGNMENT 02 - GROUP 08
 *
 * @authors Giovanni Parrella & Alessia Pesenti
 * @date 09/04/2021
 *
 * ========================================
*/

/*
 * Source file for main.
 * 
 * RGB LED Color selection project - CY8CKIT-059 KIT - See TopDesign for more info on the hardware connections/settings.
 *
 * This project can be used to turn on a RGB LED, selecting the color through a custom GUI and UART communication.
 * Baude rate was set to 9600 bps.
 * In order to communicate the color, the following packet must be sent: [0XA0(160), Red (0-255), Green(0-255), Blue(0-255), 0XC0(192)].
 * The timeout configuration can be useful when testing this code on a serial port terminal app (as CoolTerm). 
 * In order to communicate the timeout value, the following packet must be sent: [0XA1(161), timeout value(1-20), 0XC0(192)].

*/


#include "project.h"
#include "stdio.h"
#include "RGB_driver.h"
#include "InterruptRoutines.h"


static char message [20] = {'\0'};
static color Black = {0,0,0};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    
    // Start PWM and UART
    RGBLed_Start();
    UART_Start();
    
    // Initialize FLAGS and counters to IDLE (everything to 0, timer stopped)
    set_idle();
    
    // Set black color
    RGBLed_setColor(Black);
    
    // Initialize timeout to 5 seconds
    timeout = DEFAULT_5S; 
    
    // Start ISRs with custom functions
    isr_Timer_StartEx(Custom_Timer_ISR);
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
       
    for(;;)
    {
        if (flag == RECEIVED && byte_C == IDLE && byte_T == IDLE){
                    
                           
            switch(received) {
            
                case HEADER_COLOR:                                 //Switch to receiving color 
                        byte_C = HEADER_RECEIVED;                  //Set FLAG (note that HEADER RECEIVED = RECEIVING RED)                    
                        timer_count();                             //Start timeout
                        break;
                                        
                case HEADER_TIMER:                                 //Switch to receiving timeout configuration
                        byte_T = HEADER_RECEIVED;                  //Set FLAG
                        break;
                                        
                case CONNECTION_CMD:                               //Switch to connection with GUI
                        sprintf(message, "RGB LED Program $$$");   //Print the string "RGB LED Program $$$" through UART                                                    
                        UART_PutString(message);
                        set_idle();
                        break;
                    
                default:break;
                    }
            
            flag = NOT_RECEIVED;                                   //Reset FLAG
        }
        
      //COLOR
    if(flag == RECEIVED && byte_C != IDLE ){   
           
        
            switch(byte_C){
                
                case RECEIVING_RED: 
                        input_color.red = received;           //Assigning RED to input_color
                        byte_C ++;
                        timer_count();
                        break;
                    
                case RECEIVING_GREEN: 
                        input_color.green = received;         //Assigning GREEN to input_color
                        byte_C ++;
                        timer_count();
                        break;
                    
                case RECEIVING_BLUE: 
                        input_color.blue = received;          //Assigning BLUE to input_color 
                        byte_C ++;
                        timer_count();
                        break;
                    
                case RECEIVING_TAIL: 
                        if(received == TAIL_VALUE){           //Check if TAIL is the correct one, otherwise wait for it (until time runs out)
                        RGBLed_setColor(input_color);         //Turn on the LED only if the correct TAIL is received
                        set_idle();
                        break;}
                        else break;
            
                default: break;
            }
            
            flag = NOT_RECEIVED;                              //Reset FLAG
        }
        
        
    //TIMEOUT CONFIGURATION
    if( flag == RECEIVED && byte_T != IDLE ){      
     
        
            switch(byte_T){           
                
                case RECEIVING_TIMEOUT:
                        if(received >= 1 && received <= 20 ){ //Check if the value is in the range 1-20 seconds
                        timeout = received;                   //Assign the new value
                        byte_T ++;
                        break;}
                        
                        else {
                        set_idle();                           //If the value is out of range, reset to IDLE
                        break;}

                case RECEIVING_TAIL_TIME: 
                        if(received == TAIL_VALUE){           //Chek if TAIL is the correct one
                        set_idle();                           //After setting the new timeout, go back to IDLE
                        break;}
                        
                        else {
                        timeout = DEFAULT_5S;
                        set_idle();
                        break;}                               //If TAIL is wrong, set the default (5s) value and reset to IDLE
            
            default: break;
            }
            
            flag = NOT_RECEIVED;                              //Reset FLAG
        }
        
   
    }

}

/* [] END OF FILE */
