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
#include "nain_tendu.h"
#include <stdio.h>

uint8 (*pin_reader[NB_BUT])(void) = {&Pin_B_A_Read,
                                &Pin_B_B_Read,
                                &Pin_B_X_Read,
                                &Pin_B_Y_Read,
                                &Pin_B_L_TRIG_Read,
                                &Pin_B_R_TRIG_Read,
                                &Pin_B_START_Read,
                                &Pin_B_SELECT_Read,
                                &Pin_B_MENU_Read,
                                &Pin_B_DPAD_U_Read,
                                &Pin_B_DPAD_D_Read,
                                &Pin_B_DPAD_L_Read,
                                &Pin_B_DPAD_R_Read};


void get_pad_but(uint8* but, t_pad* pad)
{
    uint8 i = 0;
    
    uint8 cnt = 0;
    char str[1];
    
    uint8 *p_ctrl = (uint8*) &pad->ctrl;
    while(i < NB_BUT)
    {
        if(!(*pin_reader[i])())
        {
            CyDelay(5);
            if(!(*pin_reader[i])())
            {            
                if ( p_ctrl[sizeof(uint8) * i] == 0 )
                {
                    sprintf(str ,"%d", 1);
                    while (cnt < 1)
                    {
                        pad->aref[i][cnt] = str[cnt];
                        cnt++;
                    }
                    sig_change();
                    cnt = 0;
                }
                but[sizeof(uint8)* i] = (uint8) 1;
                p_ctrl[sizeof(uint8)* i] = (uint8) 1;
            }
            else
            {
                if ( p_ctrl[sizeof(uint8) * i] == 1 )
                {
                    sprintf(str ,"%d", 0);
                    while (cnt < 1)
                    {
                        pad->aref[i][cnt] = str[cnt];
                        cnt++;
                    }
                    sig_change();
                    cnt = 0;
                }
                but[sizeof(uint8)* i] = (uint8) 0;
                p_ctrl[sizeof(uint8)* i] = (uint8) 0;
            }
        }
        i++;
    }
    
}

void get_pad_joy(int8* joy, t_pad* pad)
{
    uint8 i = 0;
    
    int8 *p_ctrl = (int8*) &pad->ctrl;
    uint8 offset = sizeof(but_t);
    int8 jval = 0;
    uint8 cnt = 0;
    char str[4];
    while(i < NB_JOY)
    {
        jval = (ADC_JOY_GetResult16(i) >> 7) + 128;
            if ( p_ctrl[sizeof(int8) * i + offset] != jval)
            {
                sprintf(str ,"%+.3d", jval);
                while (cnt < 4)
                {
                    pad->aref[i+ NB_BUT][cnt] = str[cnt];
                    cnt++;
                }
  //              if (!i)
                //sig_change();
                cnt = 0;
            }
        joy[sizeof(int8)* i] = jval;
        p_ctrl[sizeof(int8)* i + offset] = joy[sizeof(int8)* i];    

        i++;
    }
}

void get_pad_trig(uint8* trig, t_pad* pad)
{
        uint8 i = 0;
    
    uint8 *p_ctrl = (uint8*) &pad->ctrl;
    uint8 offset = sizeof(but_t) + sizeof(joy_t);
    uint8 jval = 0;
    uint8 cnt = 0;
    char str[3];
    while(i < NB_TRIG)
    {
        jval = (ADC_JOY_GetResult16(i+ NB_JOY) >> 7);

            if ( p_ctrl[sizeof(int8) * i + offset] != jval)
            {
                sprintf(str ,"%.3d", jval);
                while (cnt < 3)
                {
                    pad->aref[i+ NB_BUT + NB_JOY][cnt] = str[cnt];
                    cnt++;
                }
                //sig_change();
                cnt = 0;
            }
        trig[sizeof(uint8)* i] = jval;
        p_ctrl[sizeof(uint8)* i + offset] = trig[sizeof(int8)* i];    

        i++;
    }    
}


void get_pad_struct(t_pad *pad)
{
    
    uint8*  but = (uint8*)&pad->but;
    uint8*  trig = (uint8*)&pad->trig;
    int8*   joy = (int8*)&pad->joy;
    
    
    get_pad_but(but, pad);
    get_pad_joy(joy, pad);
    get_pad_trig(trig, pad);
}

t_pad init_pad()
{
    t_pad pad;
    
    ADC_JOY_Start();
    ADC_JOY_StartConvert();

    
    pad.but.a = 0;
    pad.but.b = 0;
    pad.but.x = 0;
    pad.but.y = 0;
    pad.but.du = 0;
    pad.but.dd = 0;
    pad.but.dl = 0;
    pad.but.dr = 0;
    pad.but.lb = 0;
    pad.but.rb = 0;
    pad.but.menu = 0;
    pad.but.select = 0;
    pad.but.start = 0;
    
    pad.joy.j0ax = 0;
    pad.joy.j0ay = 0;
    pad.joy.j1ax = 0;
    pad.joy.j1ay = 0;
    
    pad.trig.l = 0;
    pad.trig.r = 0;
    memset(&pad.ctrl,0,sizeof(ctrl_t));
    //generation de la chaine
    generate_com(&pad, pad.com);
    //init structure de controle de com
    
    return pad;
}

void sig_change()
{
    //Pin_LED_Write(1);
}



/* [] END OF FILE */