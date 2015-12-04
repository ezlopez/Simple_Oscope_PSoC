/*******************************************************************************
* File Name: LPF.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the FILT component.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(LPF_H) /* FILT Header File */
#define LPF_H

#include "cyfitter.h"
#include "CyLib.h"

extern uint8 LPF_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/
#define LPF_DA_RAM_SIZE_CUR        (0x200u)
#define LPF_DB_RAM_SIZE_CUR        (0x200u)
#define LPF_CSA_RAM_SIZE_CUR       (0x100u)
#define LPF_CSB_RAM_SIZE_CUR       (0x100u)
#define LPF_CFSM_RAM_SIZE_CUR      (0x100u)
#define LPF_ACU_RAM_SIZE_CUR       (0x40u)

#define LPF_FIR_A_SIZE       (64u)
	
extern const uint8 CYCODE LPF_ChannelAFirCoefficients[LPF_FIR_A_SIZE];


/***************************************
*     Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct 
{
    uint8 enableState;
    uint8 cr;
    uint8 sr;
    uint8 sema;
    uint8 saveAcu[LPF_ACU_RAM_SIZE_CUR];
}   LPF_backupStruct;


/***************************************
* FILT component function prototypes.
****************************************/

void   LPF_Start(void) ;
void   LPF_Stop(void) ;
uint8 LPF_Read8(uint8 channel) ;
uint16 LPF_Read16(uint8 channel) ;
uint32 LPF_Read24(uint8 channel) ;
void LPF_Write8(uint8 channel, uint8 sample) ;
void LPF_Write16(uint8 channel, uint16 sample) ;
void LPF_Write24(uint8 channel, uint32 sample) ;
void LPF_Sleep(void) ;
void LPF_Wakeup(void) ;
void LPF_SaveConfig(void) ;
void LPF_RestoreConfig(void) ;
void LPF_Init(void) ;
void LPF_Enable(void) ;
void LPF_SetCoherency(uint8 channel, uint8 byteSelect) ;
void LPF_SetCoherencyEx(uint8 regSelect, uint8 key) ;
void LPF_SetDalign(uint8 regSelect, uint8 state) ;

/*****************************************
* FILT component API Constants.
******************************************/

/* Channel Definitions */
#define LPF_CHANNEL_A             (0u)
#define LPF_CHANNEL_B             (1u)

#define LPF_CHANNEL_A_INTR        (0x08u)
#define LPF_CHANNEL_B_INTR        (0x10u)

#define LPF_ALL_INTR              (0xf8u)

#define LPF_SIGN_BIT              ((uint32)0x00800000u)
#define LPF_SIGN_BYTE             ((uint32)0xFF000000u)

/* Component's enable/disable state */
#define LPF_ENABLED               (0x01u)
#define LPF_DISABLED              (0x00u)

/* SetCoherency API constants */
#define LPF_KEY_LOW               (0x00u)
#define LPF_KEY_MID               (0x01u)
#define LPF_KEY_HIGH              (0x02u)


/*******************************************************************************
* FILT component macros.
*******************************************************************************/

#define LPF_ClearInterruptSource() \
   (LPF_SR_REG = LPF_ALL_INTR )

#define LPF_IsInterruptChannelA() \
    (LPF_SR_REG & LPF_CHANNEL_A_INTR)

#define LPF_IsInterruptChannelB() \
    (LPF_SR_REG & LPF_CHANNEL_B_INTR)


/*******************************************************************************
* FILT component DFB registers.
*******************************************************************************/

/* DFB Status register */
#define LPF_SR_REG             (* (reg8 *) LPF_DFB__SR)
#define LPF_SR_PTR             (  (reg8 *) LPF_DFB__SR)

/* DFB Control register */
#define LPF_CR_REG             (* (reg8 *) LPF_DFB__CR)
#define LPF_CR_PTR             (  (reg8 *) LPF_DFB__CR)


/*******************************************************************************
* DFB.COHER bit field defines.
*******************************************************************************/

/* STAGEA key coherency mask */
#define LPF_STAGEA_COHER_MASK    (0x03u)
#define LPF_STAGEA_COHER         LPF_STAGEA_COHER_MASK

/* HOLDA key coherency mask */
#define LPF_HOLDA_COHER_MASK     ((uint8)((uint8)0x03u << 4u))
#define LPF_HOLDA_COHER          LPF_HOLDA_COHER_MASK

/* STAGEB key coherency mask */
#define LPF_STAGEB_COHER_MASK    (0x0Cu)
#define LPF_STAGEB_COHER         LPF_STAGEB_COHER_MASK

/* HOLDB key coherency mask */
#define LPF_HOLDB_COHER_MASK     ((uint8)((uint8)0x0Cu << 4u))
#define LPF_HOLDB_COHER          LPF_HOLDB_COHER_MASK


/*******************************************************************************
* DFB.DALIGN bit field defines.
*******************************************************************************/

/* STAGEA dalign mask */
#define LPF_STAGEA_DALIGN    (0x01u)

/* HOLDA dalign mask */
#define LPF_HOLDA_DALIGN     (0x04u)

/* STAGEB dalign mask */
#define LPF_STAGEB_DALIGN    (0x02u)

/* HOLDB dalign mask */
#define LPF_HOLDB_DALIGN     (0x08u)


#endif /* End FILT Header File */


/* [] END OF FILE */
