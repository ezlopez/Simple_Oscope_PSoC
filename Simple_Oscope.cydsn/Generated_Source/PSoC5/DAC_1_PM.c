/*******************************************************************************
* File Name: DAC_1_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for 
*  the WaveDAC8 component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "DAC_1.h"

static DAC_1_BACKUP_STRUCT  DAC_1_backup;


/*******************************************************************************
* Function Name: DAC_1_Sleep
********************************************************************************
*
* Summary:
*  Stops the component and saves its configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  DAC_1_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void DAC_1_Sleep(void) 
{
	/* Save DAC8's enable state */

	DAC_1_backup.enableState = (DAC_1_VDAC8_ACT_PWR_EN == 
		(DAC_1_VDAC8_PWRMGR_REG & DAC_1_VDAC8_ACT_PWR_EN)) ? 1u : 0u ;
	
	DAC_1_Stop();
	DAC_1_SaveConfig();
}


/*******************************************************************************
* Function Name: DAC_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component configuration. Should be called
*  just after awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  void
*
* Global variables:
*  DAC_1_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void DAC_1_Wakeup(void) 
{
	DAC_1_RestoreConfig();

	if(DAC_1_backup.enableState == 1u)
	{
		DAC_1_Enable();
	}
}


/* [] END OF FILE */
