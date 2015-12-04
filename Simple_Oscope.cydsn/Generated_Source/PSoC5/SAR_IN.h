/*******************************************************************************
* File Name: SAR_IN.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SAR_IN_H) /* Pins SAR_IN_H */
#define CY_PINS_SAR_IN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SAR_IN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SAR_IN__PORT == 15 && ((SAR_IN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SAR_IN_Write(uint8 value) ;
void    SAR_IN_SetDriveMode(uint8 mode) ;
uint8   SAR_IN_ReadDataReg(void) ;
uint8   SAR_IN_Read(void) ;
uint8   SAR_IN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SAR_IN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SAR_IN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SAR_IN_DM_RES_UP          PIN_DM_RES_UP
#define SAR_IN_DM_RES_DWN         PIN_DM_RES_DWN
#define SAR_IN_DM_OD_LO           PIN_DM_OD_LO
#define SAR_IN_DM_OD_HI           PIN_DM_OD_HI
#define SAR_IN_DM_STRONG          PIN_DM_STRONG
#define SAR_IN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SAR_IN_MASK               SAR_IN__MASK
#define SAR_IN_SHIFT              SAR_IN__SHIFT
#define SAR_IN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SAR_IN_PS                     (* (reg8 *) SAR_IN__PS)
/* Data Register */
#define SAR_IN_DR                     (* (reg8 *) SAR_IN__DR)
/* Port Number */
#define SAR_IN_PRT_NUM                (* (reg8 *) SAR_IN__PRT) 
/* Connect to Analog Globals */                                                  
#define SAR_IN_AG                     (* (reg8 *) SAR_IN__AG)                       
/* Analog MUX bux enable */
#define SAR_IN_AMUX                   (* (reg8 *) SAR_IN__AMUX) 
/* Bidirectional Enable */                                                        
#define SAR_IN_BIE                    (* (reg8 *) SAR_IN__BIE)
/* Bit-mask for Aliased Register Access */
#define SAR_IN_BIT_MASK               (* (reg8 *) SAR_IN__BIT_MASK)
/* Bypass Enable */
#define SAR_IN_BYP                    (* (reg8 *) SAR_IN__BYP)
/* Port wide control signals */                                                   
#define SAR_IN_CTL                    (* (reg8 *) SAR_IN__CTL)
/* Drive Modes */
#define SAR_IN_DM0                    (* (reg8 *) SAR_IN__DM0) 
#define SAR_IN_DM1                    (* (reg8 *) SAR_IN__DM1)
#define SAR_IN_DM2                    (* (reg8 *) SAR_IN__DM2) 
/* Input Buffer Disable Override */
#define SAR_IN_INP_DIS                (* (reg8 *) SAR_IN__INP_DIS)
/* LCD Common or Segment Drive */
#define SAR_IN_LCD_COM_SEG            (* (reg8 *) SAR_IN__LCD_COM_SEG)
/* Enable Segment LCD */
#define SAR_IN_LCD_EN                 (* (reg8 *) SAR_IN__LCD_EN)
/* Slew Rate Control */
#define SAR_IN_SLW                    (* (reg8 *) SAR_IN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SAR_IN_PRTDSI__CAPS_SEL       (* (reg8 *) SAR_IN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SAR_IN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SAR_IN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SAR_IN_PRTDSI__OE_SEL0        (* (reg8 *) SAR_IN__PRTDSI__OE_SEL0) 
#define SAR_IN_PRTDSI__OE_SEL1        (* (reg8 *) SAR_IN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SAR_IN_PRTDSI__OUT_SEL0       (* (reg8 *) SAR_IN__PRTDSI__OUT_SEL0) 
#define SAR_IN_PRTDSI__OUT_SEL1       (* (reg8 *) SAR_IN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SAR_IN_PRTDSI__SYNC_OUT       (* (reg8 *) SAR_IN__PRTDSI__SYNC_OUT) 


#if defined(SAR_IN__INTSTAT)  /* Interrupt Registers */

    #define SAR_IN_INTSTAT                (* (reg8 *) SAR_IN__INTSTAT)
    #define SAR_IN_SNAP                   (* (reg8 *) SAR_IN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SAR_IN_H */


/* [] END OF FILE */
