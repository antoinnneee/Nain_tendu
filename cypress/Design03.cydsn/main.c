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
#include "test_func.h"
#include "nain_tendu.h"
#include "stdio.h"

void generate_com(t_pad * pad, char *com)
{
    sprintf(com, "$A%dB%dX%dY%dL%dR%dSt%de%dm%dDu%dd%dl%dr%dJlx%.3dly%.3drx%.3dry%.3dTl%+.3dr%+.3d",
        pad->but.a, pad->but.b, pad->but.x, pad->but.y,
        pad->but.lb, pad->but.rb,
        pad->but.start, pad->but.select, pad->but.menu,
        pad->but.du, pad->but.dd, pad->but.dl, pad->but.dr,
        pad->joy.j0ax, pad->joy.j0ay, pad->joy.j1ax, pad->joy.j1ay,
        pad->trig.l, pad->trig.l
    );
}

static void set_ref(t_pad *pad)
{
    char *com;
    
    com = pad->com;
    
    pad->ref.ba = &com[2];
    pad->aref[0] = pad->ref.ba;
    pad->ref.bb = &com[4];
    pad->aref[1] = pad->ref.bb;
    pad->ref.bx = &com[6];
    pad->aref[2] = pad->ref.bx;
    pad->ref.by = &com[8];
    pad->aref[3] = pad->ref.by;
    pad->ref.bl = &com[10];
    pad->aref[4] = pad->ref.bl;
    pad->ref.br = &com[12];
    pad->aref[5] = pad->ref.br;
    pad->ref.bst = &com[15];
    pad->aref[6] = pad->ref.bst;
    pad->ref.bse = &com[17];
    pad->aref[7] = pad->ref.bse;
    pad->ref.bsm = &com[19];
    pad->aref[8] = pad->ref.bsm;
    
    pad->ref.bdu = &com[22];
    pad->aref[9] = pad->ref.bdu;
    pad->ref.bdd = &com[24];
    pad->aref[10] = pad->ref.bdd;
    pad->ref.bdl = &com[26];
    pad->aref[11] = pad->ref.bdl;
    pad->ref.bdr = &com[28];
    pad->aref[12] = pad->ref.bdr;

    
    pad->ref.j0x = &com[32];
    pad->aref[13] = pad->ref.j0x;
    pad->ref.j0y = &com[38];
    pad->aref[14] = pad->ref.j0y;
    pad->ref.j1x = &com[44];
    pad->aref[15] = pad->ref.j1x;
    pad->ref.j1y = &com[50];
    pad->aref[16] = pad->ref.j1y;
    
    
    pad->ref.tl = &com[56];
    pad->aref[17] = pad->ref.tl;
    pad->ref.tl = &com[60];
    pad->aref[18] = pad->ref.tr;


}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    int32 i = 0;
    t_pad mypad = init_pad();
    t_pad *pad = &mypad;
    set_ref(pad);
    //active_dim_led(&Pin_B_A_Read);
    //analog_dim();

    while(1)
    {
        get_pad_struct(pad);
                
            
        i++;
        if (i > 10000)
        i = 0;
    }
    return (0);
}

/* [] END OF FILE */
