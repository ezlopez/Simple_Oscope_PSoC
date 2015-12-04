/*******************************************************************************
* File Name: MUX_DAC.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_MUX_DAC_H)
#define CY_AMUX_MUX_DAC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void MUX_DAC_Start(void) ;
#define MUX_DAC_Init() MUX_DAC_Start()
void MUX_DAC_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void MUX_DAC_Stop(void); */
/* void MUX_DAC_Select(uint8 channel); */
/* void MUX_DAC_Connect(uint8 channel); */
/* void MUX_DAC_Disconnect(uint8 channel); */
/* void MUX_DAC_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define MUX_DAC_CHANNELS  2u
#define MUX_DAC_MUXTYPE   1
#define MUX_DAC_ATMOSTONE 1

/***************************************
*             API Constants
***************************************/

#define MUX_DAC_NULL_CHANNEL 0xFFu
#define MUX_DAC_MUX_SINGLE   1
#define MUX_DAC_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if MUX_DAC_MUXTYPE == MUX_DAC_MUX_SINGLE
# if !MUX_DAC_ATMOSTONE
#  define MUX_DAC_Connect(channel) MUX_DAC_Set(channel)
# endif
# define MUX_DAC_Disconnect(channel) MUX_DAC_Unset(channel)
#else
# if !MUX_DAC_ATMOSTONE
void MUX_DAC_Connect(uint8 channel) ;
# endif
void MUX_DAC_Disconnect(uint8 channel) ;
#endif

#if MUX_DAC_ATMOSTONE
# define MUX_DAC_Stop() MUX_DAC_DisconnectAll()
# define MUX_DAC_Select(channel) MUX_DAC_FastSelect(channel)
void MUX_DAC_DisconnectAll(void) ;
#else
# define MUX_DAC_Stop() MUX_DAC_Start()
void MUX_DAC_Select(uint8 channel) ;
# define MUX_DAC_DisconnectAll() MUX_DAC_Start()
#endif

#endif /* CY_AMUX_MUX_DAC_H */


/* [] END OF FILE */
