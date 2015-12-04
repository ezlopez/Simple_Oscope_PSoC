/*******************************************************************************
* File Name: DMA_FRAME_READY.h
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
#if !defined(CY_ISR_DMA_FRAME_READY_H)
#define CY_ISR_DMA_FRAME_READY_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void DMA_FRAME_READY_Start(void);
void DMA_FRAME_READY_StartEx(cyisraddress address);
void DMA_FRAME_READY_Stop(void);

CY_ISR_PROTO(DMA_FRAME_READY_Interrupt);

void DMA_FRAME_READY_SetVector(cyisraddress address);
cyisraddress DMA_FRAME_READY_GetVector(void);

void DMA_FRAME_READY_SetPriority(uint8 priority);
uint8 DMA_FRAME_READY_GetPriority(void);

void DMA_FRAME_READY_Enable(void);
uint8 DMA_FRAME_READY_GetState(void);
void DMA_FRAME_READY_Disable(void);

void DMA_FRAME_READY_SetPending(void);
void DMA_FRAME_READY_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the DMA_FRAME_READY ISR. */
#define DMA_FRAME_READY_INTC_VECTOR            ((reg32 *) DMA_FRAME_READY__INTC_VECT)

/* Address of the DMA_FRAME_READY ISR priority. */
#define DMA_FRAME_READY_INTC_PRIOR             ((reg8 *) DMA_FRAME_READY__INTC_PRIOR_REG)

/* Priority of the DMA_FRAME_READY interrupt. */
#define DMA_FRAME_READY_INTC_PRIOR_NUMBER      DMA_FRAME_READY__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable DMA_FRAME_READY interrupt. */
#define DMA_FRAME_READY_INTC_SET_EN            ((reg32 *) DMA_FRAME_READY__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the DMA_FRAME_READY interrupt. */
#define DMA_FRAME_READY_INTC_CLR_EN            ((reg32 *) DMA_FRAME_READY__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the DMA_FRAME_READY interrupt state to pending. */
#define DMA_FRAME_READY_INTC_SET_PD            ((reg32 *) DMA_FRAME_READY__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the DMA_FRAME_READY interrupt. */
#define DMA_FRAME_READY_INTC_CLR_PD            ((reg32 *) DMA_FRAME_READY__INTC_CLR_PD_REG)


#endif /* CY_ISR_DMA_FRAME_READY_H */


/* [] END OF FILE */
