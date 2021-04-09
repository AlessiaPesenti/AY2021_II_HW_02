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
*
* Source file for interrupt routines
*
*/


#include "InterruptRoutines.h"
#include "stdio.h"


CY_ISR(Custom_Timer_ISR){
    
    Timer_ReadStatusRegister();
    seconds++;
    
    if (seconds == timeout)                 // If time exceeds the threshold, reset to IDLE
        {  
            set_idle();
        }
}


CY_ISR(Custom_UART_RX_ISR)
{

     if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) {
            received = UART_ReadRxData();
            flag = RECEIVED;    
    }
        
    }

   

