/*******************************************************************************
* File Name: LPF_PM.c
* Version 2.30
*
* Description:
*  This file provides the power managaer API source code for the FILT component.
*
* Note:
*  
*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "LPF_PVT.h"

static LPF_backupStruct  LPF_backup = 
{
    LPF_DISABLED,
    LPF_RUN_MASK,
    
};


/*******************************************************************************
* Function Name: LPF_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LPF_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void LPF_SaveConfig(void) 
{
    LPF_backup.sr = LPF_SR_REG;
    LPF_backup.sema = LPF_SEMA_REG;

    /* Put DFB RAM on the bus */
    LPF_RAM_DIR_REG = LPF_RAM_DIR_BUS;

    /* Save the ACU RAM as this is not retension */
    (void)memcpy(LPF_backup.saveAcu,
        LPF_ACU_RAM, LPF_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    LPF_RAM_DIR_REG = LPF_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: LPF_RestoreConfig
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
*  LPF_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void LPF_RestoreConfig(void) 
{
    LPF_SR_REG = LPF_backup.sr;
    LPF_SEMA_REG = LPF_backup.sema;
    
    /* Power on DFB before initializing the RAMs */
    LPF_PM_ACT_CFG_REG |= LPF_PM_ACT_MSK;

    /* Put DFB RAM on the bus */
    LPF_RAM_DIR_REG = LPF_RAM_DIR_BUS;

    /* Restore ACU RAM as this is not retension */
    (void)memcpy(LPF_ACU_RAM,
        LPF_backup.saveAcu, LPF_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    LPF_RAM_DIR_REG = LPF_RAM_DIR_DFB;
}


/*******************************************************************************
* Function Name: LPF_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LPF_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void LPF_Sleep(void) 
{
    /* Save Filter enable state */
    if(LPF_PM_ACT_MSK == (LPF_PM_ACT_CFG_REG & LPF_PM_ACT_MSK))
    {
        /* Component is enabled */
        LPF_backup.enableState = LPF_ENABLED;
    }
    else
    {
        /* Component is disabled */
        LPF_backup.enableState = LPF_DISABLED;
    }

    /* Save the configuration */
    LPF_SaveConfig();
    
    /* Stop the component */
    LPF_Stop();
}


/*******************************************************************************
* Function Name: LPF_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  LPF_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void LPF_Wakeup(void) 
{
    /* Restore the configuration */
    LPF_RestoreConfig();
    
    /* Enable's the component operation */
    if(LPF_backup.enableState == LPF_ENABLED)
    {
        LPF_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
