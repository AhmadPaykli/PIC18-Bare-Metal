/* 
 * File:   hal_timer1.h
 * Author: Ahmad Paykli
 *
 * Created on February 18, 2026, 8:43 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* timer1_mode */
#define TIMER1_COUNTER_MODE              1      
#define TIMER1_TIMER_MODE                0
/* timer1_rw_register_size */
#define TIMER1_16BIT_REGISTER_RW_OneOperation     1
#define TIMER1_8BIT_REGISTER_RW_TwoOperations     0
/* Oscillator_enable */
#define TIMER1_Oscillator_ENABLE       1
#define TIMER1_Oscillator_DISABLE      0
/* Oscillator_type */
#define TIMER1_TMR1oscillator_ENABLE          1
#define TIMER1_AnotherOscillator_ENABLE       0
/* prescaler_value */
#define Prescale_Value_1    0
#define Prescale_Value_2    1
#define Prescale_Value_4    2
#define Prescale_Value_8    3
/* timer1_counter_SYNC */
#define TIMER1_COUNTER_ASYNC        1
#define TIMER1_COUNTER_SYNC         0

/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER1_MODULE_ENABLE()              (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()             (T1CONbits.TMR1ON = 0)

#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0)

#define TIMER1_16BIT_REGISTER_RW_OneOperation_ENABLE()  (T1CONbits.RD16 = 1)
#define TIMER1_8BIT_REGISTER_RW_TwoOperations_ENABLE()  (T1CONbits.RD16 = 0)

#define TIMER1_TMR1Oscillator_MODE_ENABLE()             (T1CONbits.T1RUN = 1)
#define TIMER1_AnotherOscillator_MODE_ENABLE()          (T1CONbits.T1RUN = 0)

#define TIMER1_EXToscillator_ENABLE()           (T1CONbits.T1OSCEN = 1)
#define TIMER1_EXToscillator_DISABLE()          (T1CONbits.T1OSCEN = 0)

#define Prescale_Value_Set(_value)          (T1CONbits.T1CKPS = _value)

#define TIMER1_COUNTER_ASYNC_ENABLE()          (T1CONbits.T1SYNC = 1)
#define TIMER1_COUNTER_SYNC_ENABLE()           (T1CONbits.T1SYNC = 0)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TMR1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR1_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif    
    uint16 timer1_preload_value;
    uint8 timer1_mode : 1;
    uint8 timer1_rw_register_size : 1;
    uint8 Oscillator_enable : 1;
    uint8 Oscillator_type : 1;
    uint8 prescaler_value : 2;
    uint8 timer1_counter_SYNC : 1;
}timer1_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType Timer1_Init(const timer1_t *_timer);
std_ReturnType Timer1_DeInit(const timer1_t *_timer);
std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER1_H */

