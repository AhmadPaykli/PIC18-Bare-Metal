/* 
 * File:   hal_timer3.h
 * Author: Ahmad Paykli
 *
 * Created on February 28, 2026, 3:07 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* timer1_mode */
#define TIMER3_COUNTER_MODE              1      
#define TIMER3_TIMER_MODE                0

/* timer1_counter_SYNC */
#define TIMER3_COUNTER_ASYNC        1
#define TIMER3_COUNTER_SYNC         0

/* prescaler_value */
#define Prescale_Value_1    0
#define Prescale_Value_2    1
#define Prescale_Value_4    2
#define Prescale_Value_8    3

/* timer1_rw_register_size */
#define TIMER3_16BIT_REGISTER_RW     1
#define TIMER3_8BIT_REGISTER_RW      0

/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER3_MODULE_ENABLE()                  (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                 (T3CONbits.TMR3ON = 0)

#define TIMER3_COUNTER_MODE_ENABLE()            (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE_ENABLE()              (T3CONbits.TMR3CS = 0)

#define TIMER3_COUNTER_ASYNC_ENABLE()           (T3CONbits.nT3SYNC = 1)
#define TIMER3_COUNTER_SYNC_ENABLE()            (T3CONbits.nT3SYNC = 0)

#define Prescale_Value_Set(_value)              (T3CONbits.T3CKPS = _value)

#define TIMER3_16BIT_REGISTER_RW_ENABLE()       (T3CONbits.RD16 = 1)
#define TIMER3_8BIT_REGISTER_RW_ENABLE()        (T3CONbits.RD16 = 0)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TMR3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR3_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif    
    uint16 timer3_preload_value;
    
    uint8 timer3_mode : 1;
    uint8 timer3_counter_SYNC : 1;
    uint8 prescaler_value : 2;
    uint8 timer3_rw_register_size : 1;
    
}timer3_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType Timer3_Init(const timer3_t *_timer);
std_ReturnType Timer3_DeInit(const timer3_t *_timer);
std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value);
std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER3_H */

