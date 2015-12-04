/*******************************************************************************
* File Name: DAC_1.c
* Version 2.0
*
* Description:
*  This file provides the source code for the 8-bit Waveform DAC 
*  (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DAC_1.h"

uint8  DAC_1_initVar = 0u;

const uint8 CYCODE DAC_1_wave1[DAC_1_WAVE1_LENGTH] = { 62u,64u,65u,67u,68u,70u,71u,73u,74u,76u,77u,78u,80u,81u,83u,84u,85u,87u,88u,89u,91u,92u,93u,95u,96u,97u,98u,99u,101u,102u,103u,104u,105u,106u,107u,108u,109u,110u,111u,112u,113u,114u,115u,115u,116u,117u,118u,118u,119u,120u,120u,121u,121u,122u,122u,123u,123u,123u,124u,124u,124u,124u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,124u,124u,124u,124u,123u,123u,123u,122u,122u,121u,121u,120u,120u,119u,118u,118u,117u,116u,115u,115u,114u,113u,112u,111u,110u,109u,108u,107u,106u,105u,104u,103u,102u,101u,99u,98u,97u,96u,95u,93u,92u,91u,89u,88u,87u,85u,84u,83u,81u,80u,78u,77u,76u,74u,73u,71u,70u,68u,67u,65u,64u,63u,61u,60u,58u,57u,55u,54u,52u,51u,49u,48u,47u,45u,44u,42u,41u,40u,38u,37u,36u,34u,33u,32u,30u,29u,28u,27u,26u,24u,23u,22u,21u,20u,19u,18u,17u,16u,15u,14u,13u,12u,11u,10u,10u,9u,8u,7u,7u,6u,5u,5u,4u,4u,3u,3u,2u,2u,2u,1u,1u,1u,1u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,1u,1u,1u,1u,2u,2u,2u,3u,3u,4u,4u,5u,5u,6u,7u,7u,8u,9u,10u,10u,11u,12u,13u,14u,15u,16u,17u,18u,19u,20u,21u,22u,23u,24u,26u,27u,28u,29u,30u,32u,33u,34u,36u,37u,38u,40u,41u,42u,44u,45u,47u,48u,49u,51u,52u,54u,55u,57u,58u,60u,61u };
const uint8 CYCODE DAC_1_wave2[DAC_1_WAVE2_LENGTH] = { 125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,125u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u,0u };

static uint8  DAC_1_Wave1Chan;
static uint8  DAC_1_Wave2Chan;
static uint8  DAC_1_Wave1TD;
static uint8  DAC_1_Wave2TD;


/*******************************************************************************
* Function Name: DAC_1_Init
********************************************************************************
*
* Summary:
*  Initializes component with parameters set in the customizer.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void DAC_1_Init(void) 
{
	DAC_1_VDAC8_Init();
	DAC_1_VDAC8_SetSpeed(DAC_1_HIGHSPEED);
	DAC_1_VDAC8_SetRange(DAC_1_DAC_RANGE);

	#if(DAC_1_DAC_MODE == DAC_1_CURRENT_MODE)
		DAC_1_IDAC8_SetPolarity(DAC_1_DAC_POL);
	#endif /* DAC_1_DAC_MODE == DAC_1_CURRENT_MODE */

	#if(DAC_1_OUT_MODE == DAC_1_BUFFER_MODE)
	   DAC_1_BuffAmp_Init();
	#endif /* DAC_1_OUT_MODE == DAC_1_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	DAC_1_Wave1TD = CyDmaTdAllocate();
	DAC_1_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	DAC_1_Wave1Setup(DAC_1_wave1, DAC_1_WAVE1_LENGTH) ;
	DAC_1_Wave2Setup(DAC_1_wave2, DAC_1_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(DAC_1_DacClk_PHASE)
	   DAC_1_DacClk_SetPhase(DAC_1_CLK_PHASE_0nS);
	#endif /* defined(DAC_1_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: DAC_1_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DAC block and DMA operation.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
*******************************************************************************/
void DAC_1_Enable(void) 
{
	DAC_1_VDAC8_Enable();

	#if(DAC_1_OUT_MODE == DAC_1_BUFFER_MODE)
	   DAC_1_BuffAmp_Enable();
	#endif /* DAC_1_OUT_MODE == DAC_1_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(DAC_1_Wave1Chan, 1u);
	(void)CyDmaChEnable(DAC_1_Wave2Chan, 1u);
	
	/* set the initial value */
	DAC_1_SetValue(0u);
	
	#if(DAC_1_CLOCK_SRC == DAC_1_CLOCK_INT)  	
	   DAC_1_DacClk_Start();
	#endif /* DAC_1_CLOCK_SRC == DAC_1_CLOCK_INT */
}


/*******************************************************************************
* Function Name: DAC_1_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as 
*  executing the stop function.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void DAC_1_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(DAC_1_initVar == 0u)
	{
		DAC_1_Init();
		DAC_1_initVar = 1u;
	}
	
	DAC_1_Enable();
}


/*******************************************************************************
* Function Name: DAC_1_StartEx
********************************************************************************
*
* Summary:
*  The StartEx function sets pointers and sizes for both waveforms
*  and then starts the component.
*
* Parameters:  
*   uint8 * wavePtr1:     Pointer to the waveform 1 array.
*   uint16  sampleSize1:  The amount of samples in the waveform 1.
*   uint8 * wavePtr2:     Pointer to the waveform 2 array.
*   uint16  sampleSize2:  The amount of samples in the waveform 2.
*
* Return: 
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void DAC_1_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	DAC_1_Wave1Setup(wavePtr1, sampleSize1);
	DAC_1_Wave2Setup(wavePtr2, sampleSize2);
	DAC_1_Start();
}


/*******************************************************************************
* Function Name: DAC_1_Stop
********************************************************************************
*
* Summary:
*  Stops the clock (if internal), disables the DMA channels
*  and powers down the DAC.
*
* Parameters:  
*  None  
*
* Return: 
*  None
*
*******************************************************************************/
void DAC_1_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(DAC_1_CLOCK_SRC == DAC_1_CLOCK_INT)  	
	   DAC_1_DacClk_Stop();
	#endif /* DAC_1_CLOCK_SRC == DAC_1_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(DAC_1_Wave1Chan);
	(void)CyDmaChDisable(DAC_1_Wave2Chan);

	/* Disable power to DAC */
	DAC_1_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: DAC_1_Wave1Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 1.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None 
*
*******************************************************************************/
void DAC_1_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (DAC_1_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		DAC_1_Wave1Chan = DAC_1_Wave1_DMA_DmaInitialize(
		DAC_1_Wave1_DMA_BYTES_PER_BURST, DAC_1_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		DAC_1_Wave1Chan = DAC_1_Wave1_DMA_DmaInitialize(
		DAC_1_Wave1_DMA_BYTES_PER_BURST, DAC_1_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(DAC_1_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(DAC_1_Wave1TD, sampleSize, DAC_1_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)DAC_1_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(DAC_1_Wave1TD, LO16((uint32)wavePtr), LO16(DAC_1_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(DAC_1_Wave1Chan, DAC_1_Wave1TD);
}


/*******************************************************************************
* Function Name: DAC_1_Wave2Setup
********************************************************************************
*
* Summary:
*  Sets pointer and size for waveform 2.                                    
*
* Parameters:  
*  uint8 * WavePtr:     Pointer to the waveform array.
*  uint16  SampleSize:  The amount of samples in the waveform.
*
* Return: 
*  None
*
*******************************************************************************/
void DAC_1_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (DAC_1_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		DAC_1_Wave2Chan = DAC_1_Wave2_DMA_DmaInitialize(
		DAC_1_Wave2_DMA_BYTES_PER_BURST, DAC_1_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		DAC_1_Wave2Chan = DAC_1_Wave2_DMA_DmaInitialize(
		DAC_1_Wave2_DMA_BYTES_PER_BURST, DAC_1_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(DAC_1_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(DAC_1_Wave2TD, sampleSize, DAC_1_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)DAC_1_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(DAC_1_Wave2TD, LO16((uint32)wavePtr), LO16(DAC_1_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(DAC_1_Wave2Chan, DAC_1_Wave2TD);
}


/* [] END OF FILE */
