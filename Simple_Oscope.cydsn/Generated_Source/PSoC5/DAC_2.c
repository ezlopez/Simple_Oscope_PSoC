/*******************************************************************************
* File Name: DAC_2.c
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

#include "DAC_2.h"

uint8  DAC_2_initVar = 0u;

const uint8 CYCODE DAC_2_wave1[DAC_2_WAVE1_LENGTH] = { 128u,129u,131u,133u,135u,137u,139u,141u,142u,144u,146u,148u,150u,152u,154u,155u,157u,159u,161u,163u,165u,167u,169u,170u,172u,174u,176u,178u,180u,182u,183u,185u,187u,189u,191u,193u,195u,197u,198u,200u,202u,204u,206u,208u,210u,211u,213u,215u,217u,219u,221u,223u,225u,226u,228u,230u,232u,234u,236u,238u,239u,241u,243u,245u,247u,249u,251u,252u,251u,249u,247u,245u,243u,241u,239u,238u,236u,234u,232u,230u,228u,226u,225u,223u,221u,219u,217u,215u,213u,211u,210u,208u,206u,204u,202u,200u,198u,197u,195u,193u,191u,189u,187u,185u,183u,182u,180u,178u,176u,174u,172u,170u,169u,167u,165u,163u,161u,159u,157u,155u,154u,152u,150u,148u,146u,144u,142u,141u,139u,137u,135u,133u,131u,129u,128u,126u,124u,122u,120u,118u,116u,114u,113u,111u,109u,107u,105u,103u,101u,100u,98u,96u,94u,92u,90u,88u,86u,85u,83u,81u,79u,77u,75u,73u,72u,70u,68u,66u,64u,62u,60u,58u,57u,55u,53u,51u,49u,47u,45u,44u,42u,40u,38u,36u,34u,32u,30u,29u,27u,25u,23u,21u,19u,17u,16u,14u,12u,10u,8u,6u,4u,3u,4u,6u,8u,10u,12u,14u,16u,17u,19u,21u,23u,25u,27u,29u,30u,32u,34u,36u,38u,40u,42u,44u,45u,47u,49u,51u,53u,55u,57u,58u,60u,62u,64u,66u,68u,70u,72u,73u,75u,77u,79u,81u,83u,85u,86u,88u,90u,92u,94u,96u,98u,100u,101u,103u,105u,107u,109u,111u,113u,114u,116u,118u,120u,122u,124u,126u };
const uint8 CYCODE DAC_2_wave2[DAC_2_WAVE2_LENGTH] = { 161u,161u,161u,161u,163u,163u,163u,163u,163u,163u,163u,163u,166u,166u,166u,166u,168u,168u,168u,168u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,171u,173u,173u,173u,173u,184u,184u,184u,184u,186u,186u,186u,186u,189u,189u,189u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,194u,196u,196u,196u,196u,199u,199u,199u,199u,230u,230u,230u,230u,230u,230u,230u,230u,235u,235u,235u,235u,237u,237u,237u,237u,237u,237u,237u,237u,240u,240u,240u,240u,235u,235u,235u,235u,235u,235u,235u,235u,232u,232u,232u,232u,232u,232u,232u,232u,232u,232u,232u,232u,232u,232u,232u,230u,230u,230u,230u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,227u,224u,224u,224u,224u,189u,189u,189u,189u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,186u,191u,191u,191u,191u,196u,196u,196u,196u,201u,201u,201u,201u,207u,207u,207u,207u,194u,194u,194u,194u,184u,184u,184u,184u,181u,182u,183u,184u,148u,148u,148u,148u,145u,145u,145u,145u,145u,145u,145u,145u,143u,144u,144u,145u,143u,143u,143u,143u,143u,143u,143u,143u,143u,143u,143u,140u,141u,142u,143u,140u,140u,140u,140u,99u,99u,99u,99u,97u,97u,97u,97u,92u,93u,93u,94u,84u,84u,84u,84u,79u,79u,79u,79u,76u,77u,78u,79u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,74u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,110u,107u,107u,107u,107u,105u,105u,105u,105u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,102u,99u,99u,99u,99u,99u,99u,99u,99u,99u,99u,99u,99u,150u,150u,150u,150u,153u,153u,153u,153u,158u,158u,158u,158u,158u,158u,158u,158u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,161u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u,158u };

static uint8  DAC_2_Wave1Chan;
static uint8  DAC_2_Wave2Chan;
static uint8  DAC_2_Wave1TD;
static uint8  DAC_2_Wave2TD;


/*******************************************************************************
* Function Name: DAC_2_Init
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
void DAC_2_Init(void) 
{
	DAC_2_VDAC8_Init();
	DAC_2_VDAC8_SetSpeed(DAC_2_HIGHSPEED);
	DAC_2_VDAC8_SetRange(DAC_2_DAC_RANGE);

	#if(DAC_2_DAC_MODE == DAC_2_CURRENT_MODE)
		DAC_2_IDAC8_SetPolarity(DAC_2_DAC_POL);
	#endif /* DAC_2_DAC_MODE == DAC_2_CURRENT_MODE */

	#if(DAC_2_OUT_MODE == DAC_2_BUFFER_MODE)
	   DAC_2_BuffAmp_Init();
	#endif /* DAC_2_OUT_MODE == DAC_2_BUFFER_MODE */

	/* Get the TD Number for the DMA channel 1 and 2   */
	DAC_2_Wave1TD = CyDmaTdAllocate();
	DAC_2_Wave2TD = CyDmaTdAllocate();
	
	/* Initialize waveform pointers  */
	DAC_2_Wave1Setup(DAC_2_wave1, DAC_2_WAVE1_LENGTH) ;
	DAC_2_Wave2Setup(DAC_2_wave2, DAC_2_WAVE2_LENGTH) ;
	
	/* Initialize the internal clock if one present  */
	#if defined(DAC_2_DacClk_PHASE)
	   DAC_2_DacClk_SetPhase(DAC_2_CLK_PHASE_0nS);
	#endif /* defined(DAC_2_DacClk_PHASE) */
}


/*******************************************************************************
* Function Name: DAC_2_Enable
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
void DAC_2_Enable(void) 
{
	DAC_2_VDAC8_Enable();

	#if(DAC_2_OUT_MODE == DAC_2_BUFFER_MODE)
	   DAC_2_BuffAmp_Enable();
	#endif /* DAC_2_OUT_MODE == DAC_2_BUFFER_MODE */

	/* 
	* Enable the channel. It is configured to remember the TD value so that
	* it can be restored from the place where it has been stopped.
	*/
	(void)CyDmaChEnable(DAC_2_Wave1Chan, 1u);
	(void)CyDmaChEnable(DAC_2_Wave2Chan, 1u);
	
	/* set the initial value */
	DAC_2_SetValue(0u);
	
	#if(DAC_2_CLOCK_SRC == DAC_2_CLOCK_INT)  	
	   DAC_2_DacClk_Start();
	#endif /* DAC_2_CLOCK_SRC == DAC_2_CLOCK_INT */
}


/*******************************************************************************
* Function Name: DAC_2_Start
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
void DAC_2_Start(void) 
{
	/* If not Initialized then initialize all required hardware and software */
	if(DAC_2_initVar == 0u)
	{
		DAC_2_Init();
		DAC_2_initVar = 1u;
	}
	
	DAC_2_Enable();
}


/*******************************************************************************
* Function Name: DAC_2_StartEx
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
void DAC_2_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)

{
	DAC_2_Wave1Setup(wavePtr1, sampleSize1);
	DAC_2_Wave2Setup(wavePtr2, sampleSize2);
	DAC_2_Start();
}


/*******************************************************************************
* Function Name: DAC_2_Stop
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
void DAC_2_Stop(void) 
{
	/* Turn off internal clock, if one present */
	#if(DAC_2_CLOCK_SRC == DAC_2_CLOCK_INT)  	
	   DAC_2_DacClk_Stop();
	#endif /* DAC_2_CLOCK_SRC == DAC_2_CLOCK_INT */
	
	/* Disble DMA channels */
	(void)CyDmaChDisable(DAC_2_Wave1Chan);
	(void)CyDmaChDisable(DAC_2_Wave2Chan);

	/* Disable power to DAC */
	DAC_2_VDAC8_Stop();
}


/*******************************************************************************
* Function Name: DAC_2_Wave1Setup
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
void DAC_2_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)

{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (DAC_2_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
		
		DAC_2_Wave1Chan = DAC_2_Wave1_DMA_DmaInitialize(
		DAC_2_Wave1_DMA_BYTES_PER_BURST, DAC_2_Wave1_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		DAC_2_Wave1Chan = DAC_2_Wave1_DMA_DmaInitialize(
		DAC_2_Wave1_DMA_BYTES_PER_BURST, DAC_2_Wave1_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(DAC_2_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
    * Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(DAC_2_Wave1TD, sampleSize, DAC_2_Wave1TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)DAC_2_Wave1_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(DAC_2_Wave1TD, LO16((uint32)wavePtr), LO16(DAC_2_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(DAC_2_Wave1Chan, DAC_2_Wave1TD);
}


/*******************************************************************************
* Function Name: DAC_2_Wave2Setup
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
void DAC_2_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
 
{
	#if (CY_PSOC3)
		uint16 memoryType; /* determining the source memory type */
		memoryType = (DAC_2_HI16FLASHPTR == HI16(wavePtr)) ? HI16(CYDEV_FLS_BASE) : HI16(CYDEV_SRAM_BASE);
			
		DAC_2_Wave2Chan = DAC_2_Wave2_DMA_DmaInitialize(
		DAC_2_Wave2_DMA_BYTES_PER_BURST, DAC_2_Wave2_DMA_REQUEST_PER_BURST,
		memoryType, HI16(CYDEV_PERIPH_BASE));
	#else /* PSoC 5 */
		DAC_2_Wave2Chan = DAC_2_Wave2_DMA_DmaInitialize(
		DAC_2_Wave2_DMA_BYTES_PER_BURST, DAC_2_Wave2_DMA_REQUEST_PER_BURST,
		HI16(wavePtr), HI16(DAC_2_DAC8__D));
	#endif /* CY_PSOC3 */
	
	/*
	* TD is looping on itself. 
	* Increment the source address, but not the destination address. 
	*/
	(void)CyDmaTdSetConfiguration(DAC_2_Wave2TD, sampleSize, DAC_2_Wave2TD, 
                                    (uint8)CY_DMA_TD_INC_SRC_ADR | (uint8)DAC_2_Wave2_DMA__TD_TERMOUT_EN); 
	
	/* Set the TD source and destination address */
	(void)CyDmaTdSetAddress(DAC_2_Wave2TD, LO16((uint32)wavePtr), LO16(DAC_2_DAC8__D));
	
	/* Associate the TD with the channel */
	(void)CyDmaChSetInitialTd(DAC_2_Wave2Chan, DAC_2_Wave2TD);
}


/* [] END OF FILE */
