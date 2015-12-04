/*******************************************************************************
* File Name: LPF_PVT.h
* Version 2.30
*
* Description:
*  This header file contains internal definitions for the FILT component.
*  It must be included after LPF.h.
*
* Note:
* 
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(LPF_PVT_H) /* FILT Header File */
#define LPF_PVT_H

#include "LPF.H"


/*******************************************************************************
* FILT component internal function prototypes.
*******************************************************************************/

extern void LPF_SetInterruptMode(uint8 events) ;
extern void LPF_SetDMAMode(uint8 events) ;


/*******************************************************************************
* FILT component internal variables.
*******************************************************************************/

extern const uint8 CYCODE LPF_control[LPF_CSA_RAM_SIZE_CUR]; 
extern const uint8 CYCODE LPF_data_a[LPF_DA_RAM_SIZE_CUR];
extern const uint8 CYCODE LPF_data_b[LPF_DB_RAM_SIZE_CUR];
extern const uint8 CYCODE LPF_cfsm[LPF_CFSM_RAM_SIZE_CUR];
extern const uint8 CYCODE LPF_acu[LPF_ACU_RAM_SIZE_CUR];


/*******************************************************************************
* FILT component internal constants.
*******************************************************************************/

/* Parameters */
#define LPF_INIT_INTERRUPT_MODE    (0u)
#define LPF_INIT_DMA_MODE          (1u)
#define LPF_INIT_COHER             (0x00u)
#define LPF_INIT_DALIGN            (0x0Fu)

/* RAM memory map offsets */
#define LPF_DA_RAM                 (void XDATA *) (LPF_DFB__DPA_SRAM_DATA)
#define LPF_DB_RAM                 (void XDATA *) (LPF_DFB__DPB_SRAM_DATA)
#define LPF_CSA_RAM                (void XDATA *) (LPF_DFB__CSA_SRAM_DATA)
#define LPF_CSB_RAM                (void XDATA *) (LPF_DFB__CSB_SRAM_DATA)
#define LPF_CFSM_RAM               (void XDATA *) (LPF_DFB__FSM_SRAM_DATA)
#define LPF_ACU_RAM                (void XDATA *) (LPF_DFB__ACU_SRAM_DATA)

/* RAM register space sizes in bytes. */
#if (CY_PSOC3)
    #define LPF_DA_RAM_SIZE            ((int16)0x0200)
    #define LPF_DB_RAM_SIZE            ((int16)0x0200)
    #define LPF_CSA_RAM_SIZE           ((int16)0x0100)
    #define LPF_CSB_RAM_SIZE           ((int16)0x0100)
    #define LPF_CFSM_RAM_SIZE          ((int16)0x0100)
    #define LPF_ACU_RAM_SIZE           ((int16)0x0040)
#else
    #define LPF_DA_RAM_SIZE            ((uint16)0x0200u)
    #define LPF_DB_RAM_SIZE            ((uint16)0x0200u)
    #define LPF_CSA_RAM_SIZE           ((uint16)0x0100u)
    #define LPF_CSB_RAM_SIZE           ((uint16)0x0100u)
    #define LPF_CFSM_RAM_SIZE          ((uint16)0x0100u)
    #define LPF_ACU_RAM_SIZE           ((uint16)0x0040u)
#endif /* (CY_PSOC3) */


/*******************************************************************************
* FILT component internal register contents.
*******************************************************************************/

#define LPF_PM_ACT_MSK             LPF_DFB__PM_ACT_MSK 
#define LPF_PM_STBY_MSK            LPF_DFB__PM_STBY_MSK 

#define LPF_RUN_MASK               (0x01u)
#define LPF_EVENT_MASK             (0x1Fu)
#define LPF_SR_EVENT_SHIFT         (0x03u)
#define LPF_DMA_CTRL_MASK          (0x0Fu)
#define LPF_RAM_DIR_BUS            (0x3Fu)
#define LPF_RAM_DIR_DFB            (0x00u)


/*******************************************************************************
* FILT component internal DFB registers.
*******************************************************************************/

/* DFB interrupt control register */
#define LPF_INT_CTRL_REG           (* (reg8 *) LPF_DFB__INT_CTRL)
#define LPF_INT_CTRL_PTR           (  (reg8 *) LPF_DFB__INT_CTRL)

/* DFB DMA control register */
#define LPF_DMA_CTRL_REG           (* (reg8 *) LPF_DFB__DMA_CTRL)
#define LPF_DMA_CTRL_PTR           (  (reg8 *) LPF_DFB__DMA_CTRL)

/* DFB ram direction register */
#define LPF_RAM_DIR_REG            (* (reg8 *) LPF_DFB__RAM_DIR)
#define LPF_RAM_DIR_PTR            (  (reg8 *) LPF_DFB__RAM_DIR)

/* DFB DSI control register */
#define LPF_DSI_CTRL_REG           (* (reg8 *) LPF_DFB__DSI_CTRL)
#define LPF_DSI_CTRL_PTR           (  (reg8 *) LPF_DFB__DSI_CTRL)

/* DFB HOLDA(Output LSB) register */
#define LPF_HOLDA_REG              (* (reg8 *) LPF_DFB__HOLDA)
#define LPF_HOLDA_PTR              (  (reg8 *) LPF_DFB__HOLDA)

/* DFB HOLDAH(Output MSB) register */
#define LPF_HOLDAH_REG             (* (reg8 *) LPF_DFB__HOLDAH)
#define LPF_HOLDAH_PTR             (  (reg8 *) LPF_DFB__HOLDAH)

/* DFB HOLDAM(Output middle) register */
#define LPF_HOLDAM_REG             (* (reg8 *) LPF_DFB__HOLDAM)
#define LPF_HOLDAM_PTR             (  (reg8 *) LPF_DFB__HOLDAM)

/* DFB HOLDB(Output LSB) register */
#define LPF_HOLDB_REG              (* (reg8 *) LPF_DFB__HOLDB)
#define LPF_HOLDB_PTR              (  (reg8 *) LPF_DFB__HOLDB)

/* DFB HOLDBH(Output MSB) register */
#define LPF_HOLDBH_REG             (* (reg8 *) LPF_DFB__HOLDBH)
#define LPF_HOLDBH_PTR             (  (reg8 *) LPF_DFB__HOLDBH)

/* DFB HOLDBM(Output middle) register */
#define LPF_HOLDBM_REG             (* (reg8 *) LPF_DFB__HOLDBM)
#define LPF_HOLDBM_PTR             (  (reg8 *) LPF_DFB__HOLDBM)

/* Active mode power control register */
#define LPF_PM_ACT_CFG_REG         (* (reg8 *) LPF_DFB__PM_ACT_CFG)
#define LPF_PM_ACT_CFG_PTR         (  (reg8 *) LPF_DFB__PM_ACT_CFG)

/* Alternative active mode power control register */
#define LPF_PM_STBY_CFG_REG        (* (reg8 *) LPF_DFB__PM_STBY_CFG)
#define LPF_PM_STBY_CFG_PTR        (  (reg8 *) LPF_DFB__PM_STBY_CFG)

/* DFB ram enable register */
#define LPF_RAM_EN_REG             (* (reg8 *) LPF_DFB__RAM_EN)
#define LPF_RAM_EN_PTR             (  (reg8 *) LPF_DFB__RAM_EN)

/* DFB STAGEA(Input LSB) register */
#define LPF_STAGEA_REG             (* (reg8 *) LPF_DFB__STAGEA)
#define LPF_STAGEA_PTR             (  (reg8 *) LPF_DFB__STAGEA)

/* DFB STAGEAH(Input MSB) register */
#define LPF_STAGEAH_REG            (* (reg8 *) LPF_DFB__STAGEAH)
#define LPF_STAGEAH_PTR            (  (reg8 *) LPF_DFB__STAGEAH)

/* DFB STAGEAM(Input middle) register */
#define LPF_STAGEAM_REG            (* (reg8 *) LPF_DFB__STAGEAM)
#define LPF_STAGEAM_PTR            (  (reg8 *) LPF_DFB__STAGEAM)

/* DFB STAGEB(Input LSB) register */
#define LPF_STAGEB_REG             (* (reg8 *) LPF_DFB__STAGEB )
#define LPF_STAGEB_PTR             (  (reg8 *) LPF_DFB__STAGEB )

/* DFB STAGEBH(Input MSB) register */
#define LPF_STAGEBH_REG            (* (reg8 *) LPF_DFB__STAGEBH)
#define LPF_STAGEBH_PTR            (  (reg8 *) LPF_DFB__STAGEBH)

/* DFB STAGEBM(Input middle) register */
#define LPF_STAGEBM_REG            (* (reg8 *) LPF_DFB__STAGEBM)
#define LPF_STAGEBM_PTR            (  (reg8 *) LPF_DFB__STAGEBM)

/* DFB coherence register */
#define LPF_COHER_REG              (* (reg8 *) LPF_DFB__COHER)
#define LPF_COHER_PTR              (  (reg8 *) LPF_DFB__COHER)

/* DFB data align register */
#define LPF_DALIGN_REG             (* (reg8 *) LPF_DFB__DALIGN)
#define LPF_DALIGN_PTR             (  (reg8 *) LPF_DFB__DALIGN)

/* DFB semaphore register */
#define LPF_SEMA_REG               (* (reg8 *) LPF_DFB__SEMA)
#define LPF_SEMA_PTR               (  (reg8 *) LPF_DFB__SEMA)

/* DFB output register which are 16 bit aligned */
#define LPF_HOLDA16_REG            (* (reg16 *) LPF_DFB__HOLDAM)
#define LPF_HOLDA16_PTR            (  (reg16 *) LPF_DFB__HOLDAM)

#define LPF_HOLDB16_REG            (* (reg16 *) LPF_DFB__HOLDBM)
#define LPF_HOLDB16_PTR            (  (reg16 *) LPF_DFB__HOLDBM)

/* DFB input register which are 16 bit aligned */
#define LPF_STAGEA16_REG           (* (reg16 *) LPF_DFB__STAGEAM)
#define LPF_STAGEA16_PTR           (  (reg16 *) LPF_DFB__STAGEAM)

#define LPF_STAGEB16_REG           (* (reg16 *) LPF_DFB__STAGEBM)
#define LPF_STAGEB16_PTR           (  (reg16 *) LPF_DFB__STAGEBM)

/* DFB output registers which are 24 bit aligned */
#define LPF_HOLDA24_REG            (* (reg32 *) LPF_DFB__HOLDA)
#define LPF_HOLDA24_PTR            (  (reg32 *) LPF_DFB__HOLDA)

#define LPF_HOLDB24_REG            (* (reg32 *) LPF_DFB__HOLDB)
#define LPF_HOLDB24_PTR            (  (reg32 *) LPF_DFB__HOLDB)

/* DFB input registers which are 24 bit aligned */
#define LPF_STAGEA24_REG           (* (reg32 *) LPF_DFB__STAGEA)
#define LPF_STAGEA24_PTR           (  (reg32 *) LPF_DFB__STAGEA)

#define LPF_STAGEB24_REG           (* (reg32 *) LPF_DFB__STAGEB)
#define LPF_STAGEB24_PTR           (  (reg32 *) LPF_DFB__STAGEB)

#endif /* End LPF_PVT_H Header File */


/* [] END OF FILE */
