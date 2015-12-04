/***************************************************************************
* File Name: ADC_TO_LPF_dma.c  
* Version 1.70
*
*  Description:
*   Provides an API for the DMAC component. The API includes functions
*   for the DMA controller, DMA channels and Transfer Descriptors.
*
*
*   Note:
*     This module requires the developer to finish or fill in the auto
*     generated funcions and setup the dma channel and TD's.
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#include <CYLIB.H>
#include <CYDMAC.H>
#include <ADC_TO_LPF_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* ADC_TO_LPF__DRQ_CTL_REG
* 
* 
* ADC_TO_LPF__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* ADC_TO_LPF__NUMBEROF_TDS
* 
* Priority of this channel.
* ADC_TO_LPF__PRIORITY
* 
* True if ADC_TO_LPF_TERMIN_SEL is used.
* ADC_TO_LPF__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* ADC_TO_LPF__TERMIN_SEL
* 
* 
* True if ADC_TO_LPF_TERMOUT0_SEL is used.
* ADC_TO_LPF__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* ADC_TO_LPF__TERMOUT0_SEL
* 
* 
* True if ADC_TO_LPF_TERMOUT1_SEL is used.
* ADC_TO_LPF__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* ADC_TO_LPF__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of ADC_TO_LPF dma channel */
uint8 ADC_TO_LPF_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 ADC_TO_LPF_DmaInitalize
**********************************************************************
* Summary:
*   Allocates and initialises a channel of the DMAC to be used by the
*   caller.
*
* Parameters:
*   BurstCount.
*       
*       
*   ReqestPerBurst.
*       
*       
*   UpperSrcAddress.
*       
*       
*   UpperDestAddress.
*       
*
* Return:
*   The channel that can be used by the caller for DMA activity.
*   DMA_INVALID_CHANNEL (0xFF) if there are no channels left. 
*
*
*******************************************************************/
uint8 ADC_TO_LPF_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    ADC_TO_LPF_DmaHandle = (uint8)ADC_TO_LPF__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(ADC_TO_LPF_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)ADC_TO_LPF__TERMOUT0_SEL,
                                  (uint8)ADC_TO_LPF__TERMOUT1_SEL,
                                  (uint8)ADC_TO_LPF__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(ADC_TO_LPF_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(ADC_TO_LPF_DmaHandle, (uint8)ADC_TO_LPF__PRIORITY);
    
    return ADC_TO_LPF_DmaHandle;
}

/*********************************************************************
* Function Name: void ADC_TO_LPF_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with ADC_TO_LPF.
*
*
* Parameters:
*   void.
*
*
*
* Return:
*   void.
*
*******************************************************************/
void ADC_TO_LPF_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(ADC_TO_LPF_DmaHandle);
}

