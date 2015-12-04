/***************************************************************************
* File Name: LPF_TO_MEM_dma.c  
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
#include <LPF_TO_MEM_dma.H>



/****************************************************************************
* 
* The following defines are available in Cyfitter.h
* 
* 
* 
* LPF_TO_MEM__DRQ_CTL_REG
* 
* 
* LPF_TO_MEM__DRQ_NUMBER
* 
* Number of TD's used by this channel.
* LPF_TO_MEM__NUMBEROF_TDS
* 
* Priority of this channel.
* LPF_TO_MEM__PRIORITY
* 
* True if LPF_TO_MEM_TERMIN_SEL is used.
* LPF_TO_MEM__TERMIN_EN
* 
* TERMIN interrupt line to signal terminate.
* LPF_TO_MEM__TERMIN_SEL
* 
* 
* True if LPF_TO_MEM_TERMOUT0_SEL is used.
* LPF_TO_MEM__TERMOUT0_EN
* 
* 
* TERMOUT0 interrupt line to signal completion.
* LPF_TO_MEM__TERMOUT0_SEL
* 
* 
* True if LPF_TO_MEM_TERMOUT1_SEL is used.
* LPF_TO_MEM__TERMOUT1_EN
* 
* 
* TERMOUT1 interrupt line to signal completion.
* LPF_TO_MEM__TERMOUT1_SEL
* 
****************************************************************************/


/* Zero based index of LPF_TO_MEM dma channel */
uint8 LPF_TO_MEM_DmaHandle = DMA_INVALID_CHANNEL;

/*********************************************************************
* Function Name: uint8 LPF_TO_MEM_DmaInitalize
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
uint8 LPF_TO_MEM_DmaInitialize(uint8 BurstCount, uint8 ReqestPerBurst, uint16 UpperSrcAddress, uint16 UpperDestAddress) 
{

    /* Allocate a DMA channel. */
    LPF_TO_MEM_DmaHandle = (uint8)LPF_TO_MEM__DRQ_NUMBER;

    /* Configure the channel. */
    (void)CyDmaChSetConfiguration(LPF_TO_MEM_DmaHandle,
                                  BurstCount,
                                  ReqestPerBurst,
                                  (uint8)LPF_TO_MEM__TERMOUT0_SEL,
                                  (uint8)LPF_TO_MEM__TERMOUT1_SEL,
                                  (uint8)LPF_TO_MEM__TERMIN_SEL);

    /* Set the extended address for the transfers */
    (void)CyDmaChSetExtendedAddress(LPF_TO_MEM_DmaHandle, UpperSrcAddress, UpperDestAddress);

    /* Set the priority for this channel */
    (void)CyDmaChPriority(LPF_TO_MEM_DmaHandle, (uint8)LPF_TO_MEM__PRIORITY);
    
    return LPF_TO_MEM_DmaHandle;
}

/*********************************************************************
* Function Name: void LPF_TO_MEM_DmaRelease
**********************************************************************
* Summary:
*   Frees the channel associated with LPF_TO_MEM.
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
void LPF_TO_MEM_DmaRelease(void) 
{
    /* Disable the channel */
    (void)CyDmaChDisable(LPF_TO_MEM_DmaHandle);
}

