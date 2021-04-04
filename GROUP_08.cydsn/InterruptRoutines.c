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
#include "InterruptRoutines.h"
#include "stdio.h"
#include "RGB_driver.h"
#include "UART.h"

extern volatile uint8_t header_C, header_T, status ;
extern volatile uint8_t byte_C, byte_T;
extern volatile color input_color;
extern volatile uint8_t timeout,received, seconds;
extern volatile uint8_t connection;


CY_ISR(Custom_TIMER_ISR){
    Timer_ReadStatusRegister();
    seconds++;
    
    if (seconds == timeout)
        {   
            set_idle();
        }
}


CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY && status == FREE)
        {
                    received = UART_ReadRxData();
                
                if (received == HEADER_COLOR) {
                    
                    //SET FLAGS
                    status = RECEIVING_COLOR;
                    header_C = HEADER_RECEIVED;
                    byte_C = RECEIVED;
                    timer_count();
                    }
                
                else if (received == HEADER_TIMER) {
                    
                    //SET FLAGS
                    status = RECEIVING_TIMEOUT;
                    header_T = HEADER_RECEIVED;
                    byte_T = RECEIVED;
                  }
                
                else if (received == CONNECTION_CMD) {
                    
                    //SET FLAG
                    connection = RECEIVED;
                    
                }
                
                else if (received != HEADER_COLOR && received != HEADER_TIMER && received != CONNECTION_CMD){
                    
                    set_idle();
                    }
                }
    
    
        

         //color
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY && header_C == HEADER_RECEIVED && status == RECEIVING_COLOR ) 
        {   
            received = UART_ReadRxData(); //Si resetta alla lettura, VERIFICATO!           
                        
                       
            switch(byte_C){
            case 1: 
                    input_color.red = received;
                    timer_count();
                    byte_C ++;
                    break;
                    
            case 2: 
                    input_color.green = received;
                    timer_count();
                    byte_C ++;
                    break;
                    
            case 3: 
                    input_color.blue = received;
                    timer_count();
                    byte_C ++;
                    break;
                    
            case 4: if(received == TAIL_VALUE){ 
                    byte_C ++;
                    break;}
            
                   else break;
            
            default: break;
            }
        }
        
        
          if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY && header_T == HEADER_RECEIVED && status == RECEIVING_TIMEOUT ) 
        {   received = UART_ReadRxData(); 
        
            switch(byte_T){
                
            case 1: 
                
                    timeout = received;
                    byte_T ++;
                    break;

            case 2: if(received == TAIL_VALUE){ 
                    byte_T ++;
                    
                    break;}
            
                    else break;
            
            default: break;
            }
        }
        
    }
/* [] END OF FILE */
