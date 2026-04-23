/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: Ahmad Paykli
 *
 * Created on February 1, 2026, 2:27 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE    1
#define INTERRUPT_FEATURE_DISABLE   0

#define INTERRUPT_PRIORITY_LEVELS_ENABLE                INTERRUPT_FEATURE_DISABLE

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE          INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE      INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE        INTERRUPT_FEATURE_ENABLE

#define TMR0_INTERRUPT_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define TMR1_INTERRUPT_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define TMR2_INTERRUPT_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE
#define TMR3_INTERRUPT_FEATURE_ENABLE       INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_FEATURE_ENABLE        INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE        INTERRUPT_FEATURE_ENABLE

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */
































/* ----------------- Includes -----------------*/

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/