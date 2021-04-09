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
* Header RGB driver
*
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
    void RGBLed_setColor(color c);
    
    //function that resets to idle the state of LED
    void set_idle();
    
    //function that starts the timeout 
    void timer_count();
    
#endif
/* [] END OF FILE */
