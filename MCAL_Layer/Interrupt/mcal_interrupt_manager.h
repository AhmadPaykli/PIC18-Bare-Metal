/* 
 * File:   mcal_interrupt_manager.h
 * Author: Ahmad Paykli
 *
 * Created on February 1, 2026, 12:55 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB4_High_Or_Low);
void RB5_ISR(uint8 RB5_High_Or_Low);
void RB6_ISR(uint8 RB6_High_Or_Low);
void RB7_ISR(uint8 RB7_High_Or_Low);
 
void ADC_ISR(void);

void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

