/*******************************************************************************
* File Name: SAR_IN.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SAR_IN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SAR_IN__PORT == 15 && ((SAR_IN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SAR_IN_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void SAR_IN_Write(uint8 value) 
{
    uint8 staticBits = (SAR_IN_DR & (uint8)(~SAR_IN_MASK));
    SAR_IN_DR = staticBits | ((uint8)(value << SAR_IN_SHIFT) & SAR_IN_MASK);
}


/*******************************************************************************
* Function Name: SAR_IN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SAR_IN_DM_STRONG     Strong Drive 
*  SAR_IN_DM_OD_HI      Open Drain, Drives High 
*  SAR_IN_DM_OD_LO      Open Drain, Drives Low 
*  SAR_IN_DM_RES_UP     Resistive Pull Up 
*  SAR_IN_DM_RES_DWN    Resistive Pull Down 
*  SAR_IN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SAR_IN_DM_DIG_HIZ    High Impedance Digital 
*  SAR_IN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SAR_IN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SAR_IN_0, mode);
}


/*******************************************************************************
* Function Name: SAR_IN_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro SAR_IN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SAR_IN_Read(void) 
{
    return (SAR_IN_PS & SAR_IN_MASK) >> SAR_IN_SHIFT;
}


/*******************************************************************************
* Function Name: SAR_IN_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 SAR_IN_ReadDataReg(void) 
{
    return (SAR_IN_DR & SAR_IN_MASK) >> SAR_IN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SAR_IN_INTSTAT) 

    /*******************************************************************************
    * Function Name: SAR_IN_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 SAR_IN_ClearInterrupt(void) 
    {
        return (SAR_IN_INTSTAT & SAR_IN_MASK) >> SAR_IN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
