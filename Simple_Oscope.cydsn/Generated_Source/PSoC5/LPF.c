/*******************************************************************************
* File Name: LPF.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the FILT component.
*
* Note:
*  
*******************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "LPF_PVT.h"


/*******************************************************************************
* FILT component internal variables.
*******************************************************************************/

uint8 LPF_initVar = 0x0u;


/*******************************************************************************
* Function Name: LPF_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  LPF_Start().
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void LPF_Init(void) 
{
        /* Power on DFB before initializing the RAMs */
    LPF_PM_ACT_CFG_REG |= LPF_PM_ACT_MSK;

    /* Turn off Run Bit */
    LPF_CR_REG &= (uint8)~LPF_RUN_MASK;
                
    /* Enable the DFB RAMS */
    LPF_RAM_EN_REG = LPF_RAM_DIR_BUS;
        
    /* Put DFB RAM on the bus */
    LPF_RAM_DIR_REG = LPF_RAM_DIR_BUS;
        
    /* Write DFB RAMs */
    /* Control Store RAMs */
    (void)memcpy( LPF_CSA_RAM,
        LPF_control, LPF_CSA_RAM_SIZE); 
    (void)memcpy(LPF_CSB_RAM,
        LPF_control, LPF_CSB_RAM_SIZE); 
    /* CFSM RAM */
    (void)memcpy(LPF_CFSM_RAM,
        LPF_cfsm, LPF_CFSM_RAM_SIZE); 
    /* Data RAMs */
    (void)memcpy(LPF_DA_RAM,
        LPF_data_a, LPF_DA_RAM_SIZE); 
    (void)memcpy(LPF_DB_RAM,
        LPF_data_b, LPF_DB_RAM_SIZE); 
    /* ACU RAM */
    (void)memcpy(LPF_ACU_RAM,
        LPF_acu, LPF_ACU_RAM_SIZE); 

    /* Take DFB RAM off the bus */
    LPF_RAM_DIR_REG = LPF_RAM_DIR_DFB;

    /* Set up interrupt and DMA events */
    LPF_SetInterruptMode(LPF_INIT_INTERRUPT_MODE);
    LPF_SetDMAMode(LPF_INIT_DMA_MODE);
        
    /* Clear any pending interrupts */
    /* Bits [2..0] of this register are readonly. */
    LPF_SR_REG = 0xf8u;   
}


/*******************************************************************************
* Function Name: LPF_Enable
********************************************************************************
*  
* Summary: 
*  Enables the DFB run bit.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void LPF_Enable(void) 
{
    /* Power on DFB in Active mode */
    LPF_PM_ACT_CFG_REG |= LPF_PM_ACT_MSK;
        
    /* Power on DFB in Alternative Active mode */
    LPF_PM_STBY_CFG_REG |= LPF_PM_STBY_MSK;

    /* Turn on Run Bit */
    LPF_CR_REG |= LPF_RUN_MASK;
}


/*******************************************************************************
* Function Name: LPF_Start
********************************************************************************
*
* Summary:
*  This method does the prep work necessary to setup DFB.  This includes loading 
*
* Parameters:  
*  void
* 
* Return: 
*  void
*
* Global variables:
*  LPF_initVar:  Used to check the initial configuration,
*  modified when this function is called for the first time.
*
* Note: 
*  Use LPF_InterruptConfig to control which events trigger 
*  interrupts in the DFB. 
*
*******************************************************************************/
void LPF_Start(void) 
{
     /* If not Initialized then initialize all required hardware and software */
    if(LPF_initVar == 0u)
    {
        LPF_Init();
        LPF_initVar = 1u;
    }

    /* Enable the DFB block */
    LPF_Enable();
}


/*******************************************************************************
* Function Name: LPF_Stop
********************************************************************************
*
* Summary:
*  Turn off the run bit.  If DMA control is used to feed the channels, allow 
*  arguments to turn one of the TD channels off. 
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void LPF_Stop(void) 
{
    LPF_CR_REG &= (uint8)~(LPF_RUN_MASK);

    /* Power off DFB in Active mode */
    LPF_PM_ACT_CFG_REG &= (uint8)~LPF_PM_ACT_MSK;
    
    /* Power off DFB in Alternative Active mode */
    LPF_PM_STBY_CFG_REG &= (uint8)~LPF_PM_STBY_MSK;
}


/*******************************************************************************
* Function Name: LPF_Read8
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  LPF_CHANNEL_A or LPF_CHANNEL_B
*            
* Return: 
*  The most significant 8 bits of the current output value sitting in the 
*  selected channel's holding register or 0x00 for invalid channel numbers.
*
*******************************************************************************/
uint8 LPF_Read8(uint8 channel) 
{
    uint8 value;

    if (channel == LPF_CHANNEL_A)
    {
        value = LPF_HOLDAH_REG;
    }
    else if (channel == LPF_CHANNEL_B)
    {
        value = LPF_HOLDBH_REG;
    }
    else
    {
        value = 0x0u;
    }
    return value;
}


/*******************************************************************************
* Function Name: LPF_Read16
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  LPF_CHANNEL_A or LPF_CHANNEL_B
*            
* Return: 
*  The most significant 16 bits of the current output value sitting in the 
*  selected channel's holding register or 0x0000 for invalid channel numbers
*
* Note:
*  Order of the read is important.  On the read of the high byte, the DFB clears
*  the data ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__) 

    uint16 LPF_Read16(uint8 channel) 
    {
        uint16 val;
    
        if (channel == LPF_CHANNEL_A)
        {        
            val = LPF_HOLDAM_REG;
            val |= (uint16)(LPF_HOLDAH_REG) << 8u;
        }
        else if (channel == LPF_CHANNEL_B)
        {      
            val = LPF_HOLDBM_REG;
            val |= (uint16)LPF_HOLDBH_REG << 8u;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint16 LPF_Read16(uint8 channel) 
    {
        uint16 val;

        if (channel == LPF_CHANNEL_A)
        {        
            val = LPF_HOLDA16_REG;
        }
        else if (channel == LPF_CHANNEL_B)
        {      
            val = LPF_HOLDB16_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: LPF_Read24
********************************************************************************
*
* Summary:
*  Get the value in one of the DFB Output Holding Registers 
*
* Parameters:  
*  channel:  LPF_CHANNEL_A or LPF_CHANNEL_B
*            
* Return: 
*  The current 24-bit output value sitting in the selected channel's
*  holding register or 0x00000000 for invalid channel numbers
*
* Note:
*  Order of the read is important.  On the read of the high byte, the DFB clears
*  the data ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    uint32 LPF_Read24(uint8 channel) 
    {
        uint32 val;
    
        if (channel == LPF_CHANNEL_A)
        {        
            val = LPF_HOLDA_REG;
            val |= (uint32)(LPF_HOLDAM_REG) << 8u;
            val |= (uint32)(LPF_HOLDAH_REG) << 16u;
            
            /* SignExtend */
            if((val & LPF_SIGN_BIT) == LPF_SIGN_BIT)
            {    
				val |= LPF_SIGN_BYTE;
			}
        }
        else if (channel == LPF_CHANNEL_B)
        {      
            val = LPF_HOLDB_REG;
            val |= (uint32)LPF_HOLDBM_REG << 8u;
            val |= (uint32)LPF_HOLDBH_REG << 16u;
            
            /* SignExtend */
            if((val & LPF_SIGN_BIT) == LPF_SIGN_BIT)
            {
				val |= LPF_SIGN_BYTE;
			}
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#else

    uint32 LPF_Read24(uint8 channel) 
    {
        uint32 val;
         
        if (channel == LPF_CHANNEL_A)
        {        
            val = LPF_HOLDA24_REG;
        }
        else if (channel == LPF_CHANNEL_B)
        {      
            val = LPF_HOLDB24_REG;
        }
        else
        {
            val = 0x0u;
        }
        return val;
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: LPF_Write8
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either LPF_CHANNEL_A or 
*            LPF_CHANNEL_B as arguments to the function.  
*  sample:   The 8-bit, right justified input sample. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
void LPF_Write8(uint8 channel, uint8 sample) 
{
    if (channel == LPF_CHANNEL_A)
    {
        LPF_STAGEAH_REG = sample;
    }
    else if (channel == LPF_CHANNEL_B)
    {
        LPF_STAGEBH_REG = sample;
    }
	else
	{
		/* No value is loaded on bad channel input */
	}
}


/*******************************************************************************
* Function Name: LPF_Write16
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either LPF_CHANNEL_A or 
*            LPF_CHANNEL_B as arguments to the function.  
*  sample:   The 16-bit, right justified input sample. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    void LPF_Write16(uint8 channel, uint16 sample) 
    {
        /* Write the STAGE MSB reg last as it signals a complete wrote to the 
           DFB.*/
        if (channel == LPF_CHANNEL_A)
        {
            LPF_STAGEAM_REG = (uint8)(sample);
            LPF_STAGEAH_REG = (uint8)(sample >> 8u);
        }
        else if (channel == LPF_CHANNEL_B)
        {
            LPF_STAGEBM_REG = (uint8)(sample);
            LPF_STAGEBH_REG = (uint8)(sample >> 8u);
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#else

    void LPF_Write16(uint8 channel, uint16 sample) 
    {
        if (channel == LPF_CHANNEL_A)
        {
            LPF_STAGEA16_REG = sample;
        }
        else if (channel == LPF_CHANNEL_B)
        {
            LPF_STAGEB16_REG = sample;
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: LPF_Write24
********************************************************************************
*
* Summary:
*  Set the value in one of the DFB Input Staging Registers 
*
* Parameters:  
*  channel:  Use either LPF_CHANNEL_A or 
*            LPF_CHANNEL_B as arguments to the function.  
*  sample:   The 24-bit, right justified input sample inside of a uint32. 
*
* Return: 
*  void
*
* Note:
*  Order of the write is important.  On the load of the high byte, the DFB sets
*  the input ready bit.
*
*******************************************************************************/
#if defined(__C51__) || defined(__CX51__)

    void LPF_Write24(uint8 channel, uint32 sample) 
    {
        /* Write the STAGE LSB reg last as it signals a complete wrote to 
           the DFB.*/
        if (channel == LPF_CHANNEL_A)
        {
            LPF_STAGEA_REG  = (uint8)(sample);
            LPF_STAGEAM_REG = (uint8)(sample >> 8u);
            LPF_STAGEAH_REG = (uint8)(sample >> 16u);
        }
        else if (channel == LPF_CHANNEL_B)
        {
            LPF_STAGEB_REG = (uint8)(sample);
            LPF_STAGEBM_REG = (uint8)(sample >> 8u);
            LPF_STAGEBH_REG = (uint8)(sample >> 16u);
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#else

    void LPF_Write24(uint8 channel, uint32 sample) 
    {
        if (channel == LPF_CHANNEL_A)
        {
            LPF_STAGEA24_REG = sample;
        }
        else if (channel == LPF_CHANNEL_B)
        {
            LPF_STAGEB24_REG = sample;
        }
        else
		{
			/* No value is loaded on bad channel input */
		}
    }

#endif /* defined(__C51__) || defined(__CX51__) */


/*******************************************************************************
* Function Name: LPF_SetCoherency
********************************************************************************
*
* Summary:
*  Sets the DFB coherency register with the user provided input 
*
* Parameters:  
*  channel:  LPF_CHANNEL_A or LPF_CHANNEL_B
*  byteSelect:  High byte, Middle byte or Low byte as the key coherency byte.
*            
* Return: 
*  None.
*
*******************************************************************************/
void LPF_SetCoherency(uint8 channel, uint8 byteSelect) 
{
    if (channel == LPF_CHANNEL_A)
    {
        LPF_COHER_REG &= 
                (uint8)(~(uint8)(LPF_STAGEA_COHER_MASK | LPF_HOLDA_COHER_MASK));
        LPF_COHER_REG |= byteSelect;
        LPF_COHER_REG |= (uint8)((uint8)byteSelect << 4u);
    }
    else if (channel == LPF_CHANNEL_B)
    {
        LPF_COHER_REG &= 
                (uint8)(~(uint8)(LPF_STAGEB_COHER_MASK | LPF_HOLDB_COHER_MASK));
        LPF_COHER_REG |= (uint8)((uint8)byteSelect << 2u);
        LPF_COHER_REG |= (uint8)((uint8)byteSelect << 6u);
    }
    else
    {
        /* Invalid channel value */
    }
}


/*******************************************************************************
* Function Name: LPF_SetCoherencyEx
********************************************************************************
* 
* Summary:
*  Configures the DFB coherency register for each of the staging and holding 
*  registers. Allows multiple registers with the same configuration to be set 
*  at the same time. This API should be used when the coherency of the staging 
*  and holding register of a channel is different. 
*
* Parameters:  
*  regSelect: This parameter is used to specify the registers that will undergo
*             the change in coherency. These are maskable and multiple registers
*             with the same configuration can passed by performing an OR 
*             operation on the following definitions. 
*            LPF_STAGEA_COHER, 
*            LPF_STAGEB_COHER,
*            LPF_HOLDA_COHER,
*            LPF_HOLDB_COHER.
*  key: The key coherency byte that will be chosen for the register(s).
*       LPF_KEY_LOW, 
*       LPF_KEY_MID,
*       LPF_KEY_HIGH.
*            
* Return: 
*  None.
*
*******************************************************************************/
void LPF_SetCoherencyEx(uint8 regSelect, uint8 key) 
{
    uint8 keyReg;
    
    keyReg = (uint8)(key << 2u) | key;
    keyReg |= (uint8)(keyReg << 4u);
    
    LPF_COHER_REG &= (uint8)~regSelect;
    LPF_COHER_REG |= keyReg & regSelect;
}


/*******************************************************************************
* Function Name: LPF_SetDalign
********************************************************************************
* 
* Summary:
*  Configures the DFB dalign register for each of the staging and holding 
*  registers. Allows multiple registers with the same configuration to be set
*  at the same time. 
*
* Parameters:  
*  regSelect: This parameter is used to specify the registers that will undergo
*             the change in data alignment. These are maskable and multiple 
*             registers with the same configuration can passed by performing 
*             an OR operation on the following definitions.
*             LPF_STAGEA_DALIGN, 
*             LPF_STAGEB_DALIGN,
*             LPF_HOLDA_DALIGN,
*             LPF_HOLDB_DALIGN.
*  state: The state is use to either enable the data alignment bits for the 
*         corresponding registers or to disable them.
*         LPF_ENABLED,
*         LPF_DISABLED
*            
* Return: 
*  None.
*
*******************************************************************************/
void LPF_SetDalign(uint8 regSelect, uint8 state) 
{    
    if (state == LPF_ENABLED)
    {
        LPF_DALIGN_REG |= regSelect;
    }
    else if (state == LPF_DISABLED)
    {
        LPF_DALIGN_REG &= (uint8)(~regSelect);
    }
    else
    {
        /* Invalid state */
    }
}

/* [] END OF FILE */

