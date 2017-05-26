/*******************************************************************************
* File Name: ADC_JOY_PM.c
* Version 2.40
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_JOY.h"


/***************************************
* Local data allocation
***************************************/

static ADC_JOY_BACKUP_STRUCT  ADC_JOY_backup =
{
    ADC_JOY_DISABLED
};


/*******************************************************************************
* Function Name: ADC_JOY_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_JOY_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_JOY_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_JOY_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_JOY_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_JOY_backup - modified.
*
*******************************************************************************/
void ADC_JOY_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    ADC_JOY_SAR_DFT_CTRL_REG |= ADC_JOY_ADFT_OVERRIDE;
    if((ADC_JOY_SAR_CTRL_REG  & ADC_JOY_ENABLE) != 0u)
    {
        if((ADC_JOY_SAR_SAMPLE_CTRL_REG & ADC_JOY_CONTINUOUS_EN) != 0u)
        {
            ADC_JOY_backup.enableState = ADC_JOY_ENABLED | ADC_JOY_STARTED;
        }
        else
        {
            ADC_JOY_backup.enableState = ADC_JOY_ENABLED;
        }
        ADC_JOY_StopConvert();
        ADC_JOY_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((ADC_JOY_SAR_CTRL_REG & ADC_JOY_BOOSTPUMP_EN) != 0u)
        {
            ADC_JOY_SAR_CTRL_REG &= (uint32)~ADC_JOY_BOOSTPUMP_EN;
            ADC_JOY_backup.enableState |= ADC_JOY_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        ADC_JOY_backup.enableState = ADC_JOY_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_JOY_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_JOY_backup - used.
*
*******************************************************************************/
void ADC_JOY_Wakeup(void)
{
    ADC_JOY_SAR_DFT_CTRL_REG &= (uint32)~ADC_JOY_ADFT_OVERRIDE;
    if(ADC_JOY_backup.enableState != ADC_JOY_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((ADC_JOY_backup.enableState & ADC_JOY_BOOSTPUMP_ENABLED) != 0u)
        {
            ADC_JOY_SAR_CTRL_REG |= ADC_JOY_BOOSTPUMP_EN;
        }
        ADC_JOY_Enable();
        if((ADC_JOY_backup.enableState & ADC_JOY_STARTED) != 0u)
        {
            ADC_JOY_StartConvert();
        }
    }
}
/* [] END OF FILE */
