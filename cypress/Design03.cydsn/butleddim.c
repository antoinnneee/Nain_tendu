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
#include <stdio.h>

void analog_dim()
{
    
    
    uint16 value = 0;
    
    ADC_JOY_Start();

    ADC_JOY_StartConvert();
    
    PWM_1_Enable();
    PWM_1_Start();
    PWM_1_WriteCompare(value);
    PWM_1_WritePeriod(255);
    
    uint8 onoff = 1;
    
    while (1)
    {
        value = ADC_JOY_GetResult16(0);
        value = value >> 8;
//        CyDelay(50);
        PWM_1_WriteCompare(value);
        if (!Pin_B_A_Read())
        {
            CyDelay(5);
            if (!Pin_B_A_Read())
            {
                if (onoff)
                {
                    onoff = 0;
                    PWM_1_Stop();
                }
                else
                {
                    onoff = 1;
                    PWM_1_Start();
                }
                while(!Pin_B_A_Read());
            }
        }
    }
}


void active_dim_led(uint8 (*f)(void))
{
    
    uint16 value = 0;
    uint8 leddim = 1;
    
    PWM_1_Enable();
    PWM_1_Start();
    PWM_1_WriteCompare(value);
    while (1)
    {
 
        if (!(*f)())
        {
            CyDelay(5);
            if (!(*f)())
            {
                if (leddim)
                    value += 3;
                else
                    value -= 3;
                
                if (value >= 1000)
                    leddim = 0;
                else if (value <= 0)
                    leddim = 1;
                PWM_1_WriteCompare(value);
            }
        }
 
    } 
    
}

/* [] END OF FILE */
