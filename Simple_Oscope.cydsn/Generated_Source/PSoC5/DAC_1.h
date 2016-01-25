/*******************************************************************************
* File Name: DAC_1.h  
* Version 2.0
*
* Description:
*  This file contains the function prototypes and constants used in
*  the 8-bit Waveform DAC (WaveDAC8) Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_WaveDAC8_DAC_1_H) 
#define CY_WaveDAC8_DAC_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include <DAC_1_Wave1_DMA_dma.h>
#include <DAC_1_Wave2_DMA_dma.h>
#include <DAC_1_VDAC8.h>


/***************************************
*  Initial Parameter Constants
***************************************/

#define DAC_1_WAVE1_TYPE     (0u)     /* Waveform for wave1 */
#define DAC_1_WAVE2_TYPE     (0u)     /* Waveform for wave2 */
#define DAC_1_SINE_WAVE      (0u)
#define DAC_1_SQUARE_WAVE    (1u)
#define DAC_1_TRIANGLE_WAVE  (2u)
#define DAC_1_SAWTOOTH_WAVE  (3u)
#define DAC_1_ARB_DRAW_WAVE  (10u) /* Arbitrary (draw) */
#define DAC_1_ARB_FILE_WAVE  (11u) /* Arbitrary (from file) */

#define DAC_1_WAVE1_LENGTH   (268u)   /* Length for wave1 */
#define DAC_1_WAVE2_LENGTH   (268u)   /* Length for wave2 */
	
#define DAC_1_DEFAULT_RANGE    (1u) /* Default DAC range */
#define DAC_1_DAC_RANGE_1V     (0u)
#define DAC_1_DAC_RANGE_1V_BUF (16u)
#define DAC_1_DAC_RANGE_4V     (1u)
#define DAC_1_DAC_RANGE_4V_BUF (17u)
#define DAC_1_VOLT_MODE        (0u)
#define DAC_1_CURRENT_MODE     (1u)
#define DAC_1_DAC_MODE         (((DAC_1_DEFAULT_RANGE == DAC_1_DAC_RANGE_1V) || \
									  (DAC_1_DEFAULT_RANGE == DAC_1_DAC_RANGE_4V) || \
							  		  (DAC_1_DEFAULT_RANGE == DAC_1_DAC_RANGE_1V_BUF) || \
									  (DAC_1_DEFAULT_RANGE == DAC_1_DAC_RANGE_4V_BUF)) ? \
									   DAC_1_VOLT_MODE : DAC_1_CURRENT_MODE)

#define DAC_1_DACMODE DAC_1_DAC_MODE /* legacy definition for backward compatibility */

#define DAC_1_DIRECT_MODE (0u)
#define DAC_1_BUFFER_MODE (1u)
#define DAC_1_OUT_MODE    (((DAC_1_DEFAULT_RANGE == DAC_1_DAC_RANGE_1V_BUF) || \
								 (DAC_1_DEFAULT_RANGE == DAC_1_DAC_RANGE_4V_BUF)) ? \
								  DAC_1_BUFFER_MODE : DAC_1_DIRECT_MODE)

#if(DAC_1_OUT_MODE == DAC_1_BUFFER_MODE)
    #include <DAC_1_BuffAmp.h>
#endif /* DAC_1_OUT_MODE == DAC_1_BUFFER_MODE */

#define DAC_1_CLOCK_INT      (1u)
#define DAC_1_CLOCK_EXT      (0u)
#define DAC_1_CLOCK_SRC      (1u)

#if(DAC_1_CLOCK_SRC == DAC_1_CLOCK_INT)  
	#include <DAC_1_DacClk.h>
	#if defined(DAC_1_DacClk_PHASE)
		#define DAC_1_CLK_PHASE_0nS (1u)
	#endif /* defined(DAC_1_DacClk_PHASE) */
#endif /* DAC_1_CLOCK_SRC == DAC_1_CLOCK_INT */

#if (CY_PSOC3)
	#define DAC_1_HI16FLASHPTR   (0xFFu)
#endif /* CY_PSOC3 */

#define DAC_1_Wave1_DMA_BYTES_PER_BURST      (1u)
#define DAC_1_Wave1_DMA_REQUEST_PER_BURST    (1u)
#define DAC_1_Wave2_DMA_BYTES_PER_BURST      (1u)
#define DAC_1_Wave2_DMA_REQUEST_PER_BURST    (1u)


/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct
{
	uint8   enableState;
}DAC_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void DAC_1_Start(void)             ;
void DAC_1_StartEx(const uint8 * wavePtr1, uint16 sampleSize1, const uint8 * wavePtr2, uint16 sampleSize2)
                                        ;
void DAC_1_Init(void)              ;
void DAC_1_Enable(void)            ;
void DAC_1_Stop(void)              ;

void DAC_1_Wave1Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;
void DAC_1_Wave2Setup(const uint8 * wavePtr, uint16 sampleSize)
                                        ;

void DAC_1_Sleep(void)             ;
void DAC_1_Wakeup(void)            ;

#define DAC_1_SetSpeed(speed)      DAC_1_VDAC8_SetSpeed(speed)
#define DAC_1_SetRange(range)      DAC_1_VDAC8_SetRange(range)
#define DAC_1_SetValue(value)      DAC_1_VDAC8_SetValue(value)
#define DAC_1_DacTrim(void)        DAC_1_VDAC8_DacTrim()
#define DAC_1_SaveConfig(void)     DAC_1_VDAC8_SaveConfig()
#define DAC_1_RestoreConfig(void)  DAC_1_VDAC8_RestoreConfig()


/***************************************
*    Variable with external linkage 
***************************************/

extern uint8 DAC_1_initVar;

extern const uint8 CYCODE DAC_1_wave1[DAC_1_WAVE1_LENGTH];
extern const uint8 CYCODE DAC_1_wave2[DAC_1_WAVE2_LENGTH];


/***************************************
*            API Constants
***************************************/

/* SetRange constants */
#if(DAC_1_DAC_MODE == DAC_1_VOLT_MODE)
    #define DAC_1_RANGE_1V       (0x00u)
    #define DAC_1_RANGE_4V       (0x04u)
#else /* current mode */
    #define DAC_1_RANGE_32uA     (0x00u)
    #define DAC_1_RANGE_255uA    (0x04u)
    #define DAC_1_RANGE_2mA      (0x08u)
    #define DAC_1_RANGE_2048uA   DAC_1_RANGE_2mA
#endif /* DAC_1_DAC_MODE == DAC_1_VOLT_MODE */

/* Power setting for SetSpeed API */
#define DAC_1_LOWSPEED       (0x00u)
#define DAC_1_HIGHSPEED      (0x02u)


/***************************************
*              Registers        
***************************************/

#define DAC_1_DAC8__D DAC_1_VDAC8_viDAC8__D


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE */
#define DAC_1_HS_MASK        (0x02u)
#define DAC_1_HS_LOWPOWER    (0x00u)
#define DAC_1_HS_HIGHSPEED   (0x02u)

/* Bit Field  DAC_MODE */
#define DAC_1_MODE_MASK      (0x10u)
#define DAC_1_MODE_V         (0x00u)
#define DAC_1_MODE_I         (0x10u)

/* Bit Field  DAC_RANGE */
#define DAC_1_RANGE_MASK     (0x0Cu)
#define DAC_1_RANGE_0        (0x00u)
#define DAC_1_RANGE_1        (0x04u)
#define DAC_1_RANGE_2        (0x08u)
#define DAC_1_RANGE_3        (0x0Cu)
#define DAC_1_IDIR_MASK      (0x04u)

#define DAC_1_DAC_RANGE      ((uint8)(1u << 2u) & DAC_1_RANGE_MASK)
#define DAC_1_DAC_POL        ((uint8)(1u >> 1u) & DAC_1_IDIR_MASK)


#endif /* CY_WaveDAC8_DAC_1_H  */

/* [] END OF FILE */
