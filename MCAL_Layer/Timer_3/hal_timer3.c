/* 
 * File:   hal_timer3.c
 * Author: Ahmad Paykli
 *
 * Created on February 28, 2026, 3:07 PM
 */

#include "hal_timer3.h"

#if TMR3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR3_InterruptHandler)(void) = NULL;
#endif
    
static volatile uint16 timer3_preload = ZERO_INIT;

static inline void Timer3_Mode_Select(const timer3_t *_timer);

std_ReturnType Timer3_Init(const timer3_t *_timer){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER1 */
        TIMER3_MODULE_DISABLE();
        
        Prescale_Value_Set(_timer->prescaler_value);
        
        Timer3_Mode_Select(_timer);
        
        TMR3H = (uint8)(_timer->timer3_preload_value >> 8);
        TMR3L = (uint8)(_timer->timer3_preload_value);
        
        timer3_preload = _timer->timer3_preload_value;  
/*==========================================================*/
/* Interrupt Configurations */         
#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR3_InterruptDisable();
        TMR3_InterruptFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            TMR3_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            TMR3_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif       
        TMR3_InterruptEnable();
#endif
/*==========================================================*/       
        TIMER3_MODULE_ENABLE();
    }
    
    return ret;
}

std_ReturnType Timer3_DeInit(const timer3_t *_timer){
    std_ReturnType ret = E_OK;

    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER1 */
        TIMER3_MODULE_DISABLE();
        /* Interrupt Configurations */  
#if TMR3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR3_InterruptDisable();
#endif
    }
    
    return ret;
}

std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value){
    std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (uint8)(_value >> 8);
        TMR3L = (uint8)(_value);
    }
    return ret;
}

std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value){
    std_ReturnType ret = E_OK;
    
    uint8 l_byte = ZERO_INIT, h_byte = ZERO_INIT;
    

    if(NULL == _timer || NULL == _value){
        ret = E_NOT_OK;
    }
    else{
        l_byte = TMR3L; 
        h_byte = TMR3H;
        
        *_value = (uint16)(h_byte << 8) + l_byte;
    }
    
    return ret;
}


void TMR3_ISR(void){
    TMR3_InterruptFlagClear();              /* Clear the interrupt flag */
    TMR3H = (uint8)(timer3_preload >> 8);   /* Initialize the pre-loaded value again */
    TMR3L = (uint8)(timer3_preload);        /* Initialize the pre-loaded value again */
    if(TMR3_InterruptHandler){
        TMR3_InterruptHandler();            /* Call the callback function */
    }
}

static inline void Timer3_Mode_Select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        
        if(TIMER3_COUNTER_ASYNC == _timer->timer3_counter_SYNC){
            TIMER3_COUNTER_ASYNC_ENABLE();
        }
        else if(TIMER3_COUNTER_SYNC == _timer->timer3_counter_SYNC){
            TIMER3_COUNTER_SYNC_ENABLE();
        }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}