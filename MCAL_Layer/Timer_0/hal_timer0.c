/* 
 * File:   hal_timer0.c
 * Author: Ahmad Paykli
 *
 * Created on February 16, 2026, 8:50 AM
 */

#include "hal_timer0.h"

#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TMR0_InterruptHandler)(void) = NULL;
static void TMR0_ISR(void);
static uint16 timer0_preload = ZERO_INIT;
#endif

/**
 * 
 * @param _timer
 * @return 
 */
std_ReturnType Timer0_Init(const timer0_t *_timer){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        uint8 value_H_byte = (uint8)(_timer->timer0_preload_value >> 8);
        uint8 value_L_byte = (uint8)(_timer->timer0_preload_value);
        
        /* Disable the TIMER0 */
        TIMER0_MODULE_DISABLE();
        
        T0CONbits.T0CS = _timer->timer0_mode;
        TMR0H = value_H_byte;
        TMR0L = value_L_byte;
        timer0_preload = _timer->timer0_preload_value;
        T0CONbits.T0SE = _timer->timer0_counter_edge;
        T0CONbits.T08BIT = _timer->timer0_register_size;
        
        if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
            TIMER0_PRESCALER_ENABLE();
            T0CONbits.T0PS = _timer->prescaler_value;
        }
        else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
            TIMER0_PRESCALER_DISABLE();
        }
        else{ /* Nothing */ }
        
/*==========================================================*/
/* Interrupt Configurations */         
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR0_InterruptDisable();
        TMR0_InterruptFlagClear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            TMR0_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            TMR0_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif       
        TMR0_InterruptEnable();
#endif
/*==========================================================*/       
        TIMER0_MODULE_ENABLE();
    }
    
    return ret;
}

/**
 * 
 * @param _timer
 * @return 
 */
std_ReturnType Timer0_DeInit(const timer0_t *_timer){
    std_ReturnType ret = E_OK;

    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER0 */
        TIMER0_MODULE_DISABLE();
        /* Interrupt Configurations */  
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR0_InterruptDisable();
#endif
    }
    
    return ret;
}

/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (uint8)(_value >> 8);
        TMR0L = (uint8)(_value);
    }
    
    return ret;
}

/**
 * 
 * @param _timer
 * @param _value
 * @return 
 */
std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value){
    std_ReturnType ret = E_OK;
    
    uint16 timer_val;
    uint8 l_byte, h_byte;
    
    l_byte = TMR0L; 
    h_byte = TMR0H;

    if(NULL == _timer || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        *_value = (uint16)(h_byte << 8) + l_byte;
    }
    
    return ret;
}

void TMR0_ISR(void){
    TMR0_InterruptFlagClear();
    TMR0H = (uint8)(timer0_preload >> 8);
    TMR0L = (uint8)(timer0_preload);
    if(TMR0_InterruptHandler){ TMR0_InterruptHandler(); }
}