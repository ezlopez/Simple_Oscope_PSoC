/*******************************************************************************
* File Name: ADC_FRAME.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_ADC_FRAME_H)
#define CY_ISR_ADC_FRAME_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void ADC_FRAME_Start(void);
void ADC_FRAME_StartEx(cyisraddress address);
void ADC_FRAME_Stop(void);

CY_ISR_PROTO(ADC_FRAME_Interrupt);

void ADC_FRAME_SetVector(cyisraddress address);
cyisraddress ADC_FRAME_GetVector(void);

void ADC_FRAME_SetPriority(uint8 priority);
uint8 ADC_FRAME_GetPriority(void);

void ADC_FRAME_Enable(void);
uint8 ADC_FRAME_GetState(void);
void ADC_FRAME_Disable(void);

void ADC_FRAME_SetPending(void);
void ADC_FRAME_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the ADC_FRAME ISR. */
#define ADC_FRAME_INTC_VECTOR            ((reg32 *) ADC_FRAME__INTC_VECT)

/* Address of the ADC_FRAME ISR priority. */
#define ADC_FRAME_INTC_PRIOR             ((reg8 *) ADC_FRAME__INTC_PRIOR_REG)

/* Priority of the ADC_FRAME interrupt. */
#define ADC_FRAME_INTC_PRIOR_NUMBER      ADC_FRAME__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable ADC_FRAME interrupt. */
#define ADC_FRAME_INTC_SET_EN            ((reg32 *) ADC_FRAME__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the ADC_FRAME interrupt. */
#define ADC_FRAME_INTC_CLR_EN            ((reg32 *) ADC_FRAME__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the ADC_FRAME interrupt state to pending. */
#define ADC_FRAME_INTC_SET_PD            ((reg32 *) ADC_FRAME__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the ADC_FRAME interrupt. */
#define ADC_FRAME_INTC_CLR_PD            ((reg32 *) ADC_FRAME__INTC_CLR_PD_REG)


#endif /* CY_ISR_ADC_FRAME_H */


/* [] END OF FILE */
