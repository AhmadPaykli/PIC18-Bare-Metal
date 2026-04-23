/* 
 * File:   hal_timer0.h
 * Author: Ahmad Paykli
 *
 * Created on February 16, 2026, 8:49 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
#define TIMER0_COUNTER_MODE              1
#define TIMER0_TIMER_MODE                0

#define TIMER0_PRESCALER_DISABLE_CFG     1
#define TIMER0_PRESCALER_ENABLE_CFG      0

#define TIMER0_8BIT_REGISTER_MODE        1
#define TIMER0_16BIT_REGISTER_MODE       0

#define TIMER0_COUNTER_RISING_EDGE_CFG   1
#define TIMER0_COUNTER_FALLING_EDGE_CFG  0


/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER0_MODULE_ENABLE()              (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()             (T0CONbits.TMR0ON = 0)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()  (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE() (T0CONbits.T08BIT = 0)

#define TIMER0_COUNTER_MODE_ENABLE()        (T0CONbits.T0CS = 1)
#define TIMER0_TIMER_MODE_ENABLE()          (T0CONbits.T0CS = 0)

#define TIMER0_FALLING_EDGE_ENABLE()        (T0CONbits.T0SE = 1)
#define TIMER0_RISING_EDGE_ENABLE()         (T0CONbits.T0SE = 0)

#define TIMER0_PRESCALER_DISABLE()          (T0CONbits.PSA = 1)
#define TIMER0_PRESCALER_ENABLE()           (T0CONbits.PSA = 0)

/* ----------------- Data Type Declarations -----------------*/
/**
 * Timer0 Pre-Scaler Select 
 */
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256
}timer0_prescaler_select_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR0_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif    
    uint8 timer0_mode : 1;
    uint16 timer0_preload_value;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_register_size : 1;
    uint8 prescaler_enable : 1;
    timer0_prescaler_select_t prescaler_value;
}timer0_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType Timer0_Init(const timer0_t *_timer);
std_ReturnType Timer0_DeInit(const timer0_t *_timer);
std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value);
std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER0_H */

