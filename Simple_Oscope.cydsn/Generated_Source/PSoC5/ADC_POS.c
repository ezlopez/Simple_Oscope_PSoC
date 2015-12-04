/*******************************************************************************
* File Name: ADC_POS.c  
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
#include "ADC_POS.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ADC_POS__PORT == 15 && ((ADC_POS__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ADC_POS_Write
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
void ADC_POS_Write(uint8 value) 
{
    uint8 staticBits = (ADC_POS_DR & (uint8)(~ADC_POS_MASK));
    ADC_POS_DR = staticBits | ((uint8)(value << ADC_POS_SHIFT) & ADC_POS_MASK);
}


/*******************************************************************************
* Function Name: ADC_POS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ADC_POS_DM_STRONG     Strong Drive 
*  ADC_POS_DM_OD_HI      Open Drain, Drives High 
*  ADC_POS_DM_OD_LO      Open Drain, Drives Low 
*  ADC_POS_DM_RES_UP     Resistive Pull Up 
*  ADC_POS_DM_RES_DWN    Resistive Pull Down 
*  ADC_POS_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ADC_POS_DM_DIG_HIZ    High Impedance Digital 
*  ADC_POS_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ADC_POS_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ADC_POS_0, mode);
}


/*******************************************************************************
* Function Name: ADC_POS_Read
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
*  Macro ADC_POS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ADC_POS_Read(void) 
{
    return (ADC_POS_PS & ADC_POS_MASK) >> ADC_POS_SHIFT;
}


/*******************************************************************************
* Function Name: ADC_POS_ReadDataReg
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
uint8 ADC_POS_ReadDataReg(void) 
{
    return (ADC_POS_DR & ADC_POS_MASK) >> ADC_POS_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ADC_POS_INTSTAT) 

    /*******************************************************************************
    * Function Name: ADC_POS_ClearInterrupt
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
    uint8 ADC_POS_ClearInterrupt(void) 
    {
        return (ADC_POS_INTSTAT & ADC_POS_MASK) >> ADC_POS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
