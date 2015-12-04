/*******************************************************************************
* File Name: TIMER_DMA_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "TIMER_DMA.h"

static TIMER_DMA_backupStruct TIMER_DMA_backup;


/*******************************************************************************
* Function Name: TIMER_DMA_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_DMA_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TIMER_DMA_SaveConfig(void) 
{
    #if (!TIMER_DMA_UsingFixedFunction)
        TIMER_DMA_backup.TimerUdb = TIMER_DMA_ReadCounter();
        TIMER_DMA_backup.InterruptMaskValue = TIMER_DMA_STATUS_MASK;
        #if (TIMER_DMA_UsingHWCaptureCounter)
            TIMER_DMA_backup.TimerCaptureCounter = TIMER_DMA_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TIMER_DMA_UDB_CONTROL_REG_REMOVED)
            TIMER_DMA_backup.TimerControlRegister = TIMER_DMA_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TIMER_DMA_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_DMA_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_DMA_RestoreConfig(void) 
{   
    #if (!TIMER_DMA_UsingFixedFunction)

        TIMER_DMA_WriteCounter(TIMER_DMA_backup.TimerUdb);
        TIMER_DMA_STATUS_MASK =TIMER_DMA_backup.InterruptMaskValue;
        #if (TIMER_DMA_UsingHWCaptureCounter)
            TIMER_DMA_SetCaptureCount(TIMER_DMA_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TIMER_DMA_UDB_CONTROL_REG_REMOVED)
            TIMER_DMA_WriteControlRegister(TIMER_DMA_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TIMER_DMA_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_DMA_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TIMER_DMA_Sleep(void) 
{
    #if(!TIMER_DMA_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TIMER_DMA_CTRL_ENABLE == (TIMER_DMA_CONTROL & TIMER_DMA_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TIMER_DMA_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TIMER_DMA_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TIMER_DMA_Stop();
    TIMER_DMA_SaveConfig();
}


/*******************************************************************************
* Function Name: TIMER_DMA_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  TIMER_DMA_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_DMA_Wakeup(void) 
{
    TIMER_DMA_RestoreConfig();
    #if(!TIMER_DMA_UDB_CONTROL_REG_REMOVED)
        if(TIMER_DMA_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TIMER_DMA_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
