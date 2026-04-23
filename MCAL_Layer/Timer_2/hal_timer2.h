/* 
 * File:   hal_timer2.h
 * Author: Ahmad Paykli
 *
 * Created on February 28, 2026, 8:47 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* ----------------- Includes -----------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/
/* Post_scale_value */
#define Post_scale_Value_1         0
#define Post_scale_Value_2         1
#define Post_scale_Value_3         2
#define Post_scale_Value_4         3
#define Post_scale_Value_5         4 
#define Post_scale_Value_6         5 
#define Post_scale_Value_7         6 
#define Post_scale_Value_8         7 
#define Post_scale_Value_9         8 
#define Post_scale_Value_10        9 
#define Post_scale_Value_11        10
#define Post_scale_Value_12        11
#define Post_scale_Value_13        12
#define Post_scale_Value_14        13
#define Post_scale_Value_15        14
#define Post_scale_Value_16        15
                     
/* pre_scaler_value */
#define Pre_scale_Value_1         0
#define Pre_scale_Value_4         1
#define Pre_scale_Value_16        2

/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER2_MODULE_ENABLE()              (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()             (T2CONbits.TMR2ON = 0)

#define TIMER2_Post_scale_Value_Set(_value)          (T2CONbits.TOUTPS = _value)

#define TIMER2_Pre_scale_Value_Set(_value)           (T2CONbits.T2CKPS = _value)

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
#if TMR1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR2_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_cfg priority;
#endif
#endif
    uint8 timer2_preload_value : 1;
    uint8 Post_scale_value : 4;
    uint8 pre_scaler_value : 2;
}timer2_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType Timer2_Init(const timer2_t *_timer);
std_ReturnType Timer2_DeInit(const timer2_t *_timer);
std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);

#endif	/* HAL_TIMER2_H */

