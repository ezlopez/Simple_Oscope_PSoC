/*******************************************************************************
* File Name: MUX_DAC.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "MUX_DAC.h"

static uint8 MUX_DAC_lastChannel = MUX_DAC_NULL_CHANNEL;


/*******************************************************************************
* Function Name: MUX_DAC_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void MUX_DAC_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < MUX_DAC_CHANNELS ; chan++)
    {
#if (MUX_DAC_MUXTYPE == MUX_DAC_MUX_SINGLE)
        MUX_DAC_Unset(chan);
#else
        MUX_DAC_CYAMUXSIDE_A_Unset(chan);
        MUX_DAC_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    MUX_DAC_lastChannel = MUX_DAC_NULL_CHANNEL;
}


#if (!MUX_DAC_ATMOSTONE)
/*******************************************************************************
* Function Name: MUX_DAC_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void MUX_DAC_Select(uint8 channel) 
{
    MUX_DAC_DisconnectAll();        /* Disconnect all previous connections */
    MUX_DAC_Connect(channel);       /* Make the given selection */
    MUX_DAC_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: MUX_DAC_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void MUX_DAC_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( MUX_DAC_lastChannel != MUX_DAC_NULL_CHANNEL)
    {
        MUX_DAC_Disconnect(MUX_DAC_lastChannel);
    }

    /* Make the new channel connection */
#if (MUX_DAC_MUXTYPE == MUX_DAC_MUX_SINGLE)
    MUX_DAC_Set(channel);
#else
    MUX_DAC_CYAMUXSIDE_A_Set(channel);
    MUX_DAC_CYAMUXSIDE_B_Set(channel);
#endif


    MUX_DAC_lastChannel = channel;   /* Update last channel */
}


#if (MUX_DAC_MUXTYPE == MUX_DAC_MUX_DIFF)
#if (!MUX_DAC_ATMOSTONE)
/*******************************************************************************
* Function Name: MUX_DAC_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void MUX_DAC_Connect(uint8 channel) 
{
    MUX_DAC_CYAMUXSIDE_A_Set(channel);
    MUX_DAC_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: MUX_DAC_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void MUX_DAC_Disconnect(uint8 channel) 
{
    MUX_DAC_CYAMUXSIDE_A_Unset(channel);
    MUX_DAC_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (MUX_DAC_ATMOSTONE)
/*******************************************************************************
* Function Name: MUX_DAC_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void MUX_DAC_DisconnectAll(void) 
{
    if(MUX_DAC_lastChannel != MUX_DAC_NULL_CHANNEL) 
    {
        MUX_DAC_Disconnect(MUX_DAC_lastChannel);
        MUX_DAC_lastChannel = MUX_DAC_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
