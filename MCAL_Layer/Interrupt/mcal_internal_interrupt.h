/* 
 * File:   mcal_internal_interrupt.h
 * Author: Ahmad Paykli
 *
 * Created on February 1, 2026, 12:55 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
/*======================================================================================*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the ADC */
#define ADC_InterruptDisable() (PIE1bits.ADIE = 0)
/* this routine sets the interrupt enable for the ADC */
#define ADC_InterruptEnable() (PIE1bits.ADIE = 1)
/* this routine clears the interrupt flag for the ADC */
#define ADC_InterruptFlagClear() (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the ADC Interrupt Priority to be High priority */
#define ADC_HighPrioritySet()          (IPR1bits.ADIP = 1)
/* This routine set the ADC Interrupt Priority to be Low priority */
#define ADC_LowPrioritySet()           (IPR1bits.ADIP = 0)
#endif

#endif
/*======================================================================================*/
#if TMR0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the TMR0 */
#define TMR0_InterruptDisable() (INTCONbits.TMR0IE = 0)
/* this routine sets the interrupt enable for the TMR0 */
#define TMR0_InterruptEnable() (INTCONbits.TMR0IE = 1)
/* this routine clears the interrupt flag for the TMR0 */
#define TMR0_InterruptFlagClear() (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR0 Interrupt Priority to be High priority */
#define TMR0_HighPrioritySet()          (INTCON2bits.TMR0IP = 1)
/* This routine set the TMR0 Interrupt Priority to be Low priority */
#define TMR0_LowPrioritySet()           (INTCON2bits.TMR0IP = 0)
#endif

#endif 
/*======================================================================================*/
#if TMR1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the TMR1 */
#define TMR1_InterruptDisable() (PIE1bits.TMR1IE = 0)
/* this routine sets the interrupt enable for the TMR1 */
#define TMR1_InterruptEnable() (PIE1bits.TMR1IE = 1)
/* this routine clears the interrupt flag for the TMR1 */
#define TMR1_InterruptFlagClear() (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR1 Interrupt Priority to be High priority */
#define TMR1_HighPrioritySet()          (IPR1bits.TMR1IP = 1)
/* This routine set the TMR1 Interrupt Priority to be Low priority */
#define TMR1_LowPrioritySet()           (IPR1bits.TMR1IP = 0)
#endif

#endif 
/*======================================================================================*/

/*======================================================================================*/
#if TMR2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the TMR2 */
#define TMR2_InterruptDisable() (PIE1bits.TMR2IE = 0)
/* this routine sets the interrupt enable for the TMR2 */
#define TMR2_InterruptEnable() (PIE1bits.TMR2IE = 1)
/* this routine clears the interrupt flag for the TMR2 */
#define TMR2_InterruptFlagClear() (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR2 Interrupt Priority to be High priority */
#define TMR2_HighPrioritySet()          (IPR1bits.TMR2IP = 1)
/* This routine set the TMR2 Interrupt Priority to be Low priority */
#define TMR2_LowPrioritySet()           (IPR1bits.TMR2IP = 0)
#endif

#endif 
/*======================================================================================*/

/*======================================================================================*/
#if TMR3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the TMR3 */
#define TMR3_InterruptDisable() (PIE2bits.TMR3IE = 0)
/* this routine sets the interrupt enable for the TMR3 */
#define TMR3_InterruptEnable() (PIE2bits.TMR3IE = 1)
/* this routine clears the interrupt flag for the TMR3 */
#define TMR3_InterruptFlagClear() (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the TMR3 Interrupt Priority to be High priority */
#define TMR3_HighPrioritySet()          (IPR2bits.TMR3IP = 1)
/* This routine set the TMR3 Interrupt Priority to be Low priority */
#define TMR3_LowPrioritySet()           (IPR2bits.TMR3IP = 0)
#endif

#endif 
/*======================================================================================*/

/*======================================================================================*/
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the CCP1 */
#define CCP1_InterruptDisable() (PIE1bits.CCP1IE = 0)
/* this routine sets the interrupt enable for the CCP1 */
#define CCP1_InterruptEnable() (PIE1bits.CCP1IE = 1)
/* this routine clears the interrupt flag for the CCP1 */
#define CCP1_InterruptFlagClear() (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the CCP1 Interrupt Priority to be High priority */
#define CCP1_HighPrioritySet()          (IPR1bits.CCP1IP = 1)
/* This routine set the CCP1 Interrupt Priority to be Low priority */
#define CCP1_LowPrioritySet()           (IPR1bits.CCP1IP = 0)
#endif

#endif 
/*======================================================================================*/

/*======================================================================================*/
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* this routine clears the interrupt enable for the CCP2 */
#define CCP2_InterruptDisable() (PIE2bits.CCP2IE = 0)
/* this routine sets the interrupt enable for the CCP2 */
#define CCP2_InterruptEnable() (PIE2bits.CCP2IE = 1)
/* this routine clears the interrupt flag for the CCP2 */
#define CCP2_InterruptFlagClear() (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine set the CCP2 Interrupt Priority to be High priority */
#define CCP2_HighPrioritySet()          (IPR2bits.CCP2IP = 1)
/* This routine set the CCP2 Interrupt Priority to be Low priority */
#define CCP2_LowPrioritySet()           (IPR2bits.CCP2IP = 0)
#endif

#endif 
/*======================================================================================*/

/* ----------------- Data Type Declarations -----------------*/
typedef void (*ADC_Handler)(void);

std_ReturnType ADC_SetInterruptHandler(ADC_Handler _Handler);
/* ----------------- Software Interfaces Declarations -----------------*/

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

