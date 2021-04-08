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
#define HEADER_COLOR 160
#define TAIL_VALUE 192
#define HEADER_TIMER 161
#define CONNECTION_CMD 118
#define DEFAULT_5S 5


#define NOT_RECEIVED 0
#define RECEIVED 1

#define HEADER_RECEIVED 1

#define RECEIVING_RED 1
#define RECEIVING_GREEN 2
#define RECEIVING_BLUE 3
#define RECEIVING_TAIL 4

#define IDLE 0
#define RECEIVING_COLOR 1
#define RECEIVING_TIMEOUT 2

#ifndef __INTERRUPT_ROUTINES_H__
    #define __INTERRUPT_ROUTINES_H__
    
    #include "project.h"
    #include "RGB_driver.h"
    
    volatile uint8_t byte_C, byte_T, received, flag;

    volatile uint8_t timeout, seconds;

    volatile color input_color;
    
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    CY_ISR_PROTO(Custom_Timer_ISR);
    
#endif

/* [] END OF FILE */
