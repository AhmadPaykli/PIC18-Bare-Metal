/* 
 * File:   hal_timer1.c
 * Author: Ahmad Paykli
 *
 * Created on February 18, 2026, 8:44 PM
 */

#include "hal_timer1.h"

#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR1_InterruptHandler)(void) = NULL;
#endif
    
static volatile uint16 timer1_preload = ZERO_INIT;

static inline void Timer1_Mode_Select(const timer1_t *_timer);

std_ReturnType Timer1_Init(const timer1_t *_timer){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        uint8 value_H_byte, value_L_byte;
        
        /* Disable the TIMER1 */
        TIMER1_MODULE_DISABLE();
        Prescale_Value_Set(_timer->prescaler_value);
        
        Timer1_Mode_Select(_timer);
        
        TMR1H = (uint8)(_timer->timer1_preload_value >> 8);
        TMR1L = (uint8)(_timer->timer1_preload_value);
        
        timer1_preload = _timer->timer1_preload_value;  
/*==========================================================*/
/* Interrupt Configurations */         
#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR1_InterruptDisable();
        TMR1_InterruptFlagClear();
        TMR1_InterruptHandler = _timer->TMR1_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            TMR1_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            TMR1_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif       
        TMR1_InterruptEnable();
#endif
/*==========================================================*/       
        TIMER1_MODULE_ENABLE();
    }
    
    return ret;
}

std_ReturnType Timer1_DeInit(const timer1_t *_timer){
    std_ReturnType ret = E_OK;

    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER1 */
        TIMER1_MODULE_DISABLE();
        /* Interrupt Configurations */  
#if TMR0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR1_InterruptDisable();
#endif
    }
    
    return ret;
}

std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value){
    std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (uint8)(_value >> 8);
        TMR1L = (uint8)(_value);
    }
    return ret;
}

std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value){
    std_ReturnType ret = E_OK;
    
    uint16 timer_val;
    uint8 l_byte, h_byte;
    
    l_byte = TMR1L; 
    h_byte = TMR1H;

    if(NULL == _timer || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        *_value = (uint16)(h_byte << 8) + l_byte;
    }
    
    return ret;
}


void TMR1_ISR(void){
    TMR1_InterruptFlagClear();              /* Clear the interrupt flag */
    TMR1H = (uint8)(timer1_preload >> 8);   /* Initialize the pre-loaded value again */
    TMR1L = (uint8)(timer1_preload);        /* Initialize the pre-loaded value again */
    if(TMR1_InterruptHandler){
        TMR1_InterruptHandler();            /* Call the callback function */
    }
}

static inline void Timer1_Mode_Select(const timer1_t *_timer){
    if(TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        
        if(TIMER1_COUNTER_ASYNC == _timer->timer1_counter_SYNC){
            TIMER1_COUNTER_ASYNC_ENABLE();
        }
        else if(TIMER1_COUNTER_SYNC == _timer->timer1_counter_SYNC){
            TIMER1_COUNTER_SYNC_ENABLE();
        }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}