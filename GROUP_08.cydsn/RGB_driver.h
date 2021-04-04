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
#ifndef __RGB_DRIVER_H__
    #define __RGB_DRIVER_H__
    
    #include "project.h"
    
    //Struct holding color data
    
    typedef struct {
        uint8_t red;    // 0-255
        uint8_t green;  // 0-255
        uint8_t blue;   // 0-255
    } color ;
    
    //function which will start PWM 
    void RGBLed_Start();
   
    //function which will set the color
    void RGBLed_setColor();
    
    //function that resets to idle the state of LED
    void set_idle();
    
    //function that starts the timeout 
    void timer_count();
    
#endif
/* [] END OF FILE */
