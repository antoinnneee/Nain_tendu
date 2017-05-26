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
#ifndef __NAIN_TENDU_H
    #define __NAIN_TENDU_H

    #include "project.h"
    #define NB_BUT 13
    #define NB_JOY 4
    #define NB_TRIG 2
    #define COMSIZE 64

    typedef struct but_s{
        uint8_t a;
        uint8_t b;
        uint8_t x;
        uint8_t y;
        uint8_t lb;
        uint8_t rb;
        uint8_t start;
        uint8_t select;
        uint8_t menu;
        uint8_t du;
        uint8_t dd;
        uint8_t dl;
        uint8_t dr;
        
    } but_t;
    
    typedef struct joy_s{
        int8_t j0ax;
        int8_t j1ax;
        int8_t j0ay;
        int8_t j1ay;

    }joy_t;
    
    typedef struct trig_s{   
        uint8_t l;
        uint8_t r;
    
    }trig_t;
    
    typedef struct com_control_s
    {
        //bouton
        uint8 ba;
        uint8 bb;
        uint8 bx;
        uint8 by;
        uint8 bdu;
        uint8 bdd;
        uint8 bdl;
        uint8 bdr;
        uint8 bst;
        uint8 bse;
        uint8 bsm;
        uint8 bl;
        uint8 br;
        
        //  triger
        uint8 tl;
        uint8 tr;
        
        //  joystick 2*2axe
        uint8 j0x;
        uint8 j0y;
        uint8 j1x;
        uint8 j1y;
        
    }ctrl_t;
    
    typedef struct ref_control_s
    {
        //bouton
        char *ba;
        char *bb;
        char *bx;
        char *by;
        char *bdu;
        char *bdd;
        char *bdl;
        char *bdr;
        char *bst;
        char *bse;
        char *bsm;
        char *bl;
        char *br;

        //  joystick 2*2axe

        char *j0x;
        char *j0y;
        char *j1x;
        char *j1y;
        
        //  triger
        char *tl;
        char *tr;
        
        
    }ref_t;
    
    typedef struct gamepad_s {
        but_t   but;
        joy_t   joy;
        trig_t  trig;
        ctrl_t  ctrl;
        ref_t   ref;
        char    *aref[19];
        char    com[COMSIZE];
    }t_pad;
    
    void get_pad_struct(t_pad * pad);
    void generate_com(t_pad *pad, char *com);
    t_pad init_pad();
    void sig_change();

#endif


/* [] END OF FILE */
