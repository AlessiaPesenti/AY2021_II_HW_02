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

#define HEADER_COLOR 160
#define TAIL_VALUE 192
#define HEADER_TIMER 161
#define CONNECTION_CMD 118

#define HEADER_NOT_RECEIVED 0
#define HEADER_RECEIVED 1
#define NOT_RECEIVED 0
#define RECEIVED 1

#define FREE 0
#define RECEIVING_COLOR 1
#define RECEIVING_TIMEOUT 2


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
