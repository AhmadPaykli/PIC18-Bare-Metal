/* 
 * File:   hal_timer2.c
 * Author: Ahmad Paykli
 *
 * Created on February 28, 2026, 8:47 AM
 */

#include "hal_timer2.h"

#if TMR1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR2_InterruptHandler)(void) = NULL;
#endif
    
static volatile uint8 timer2_preload = ZERO_INIT;

std_ReturnType Timer2_Init(const timer2_t *_timer){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER2 */
        TIMER2_MODULE_DISABLE();
        
        TIMER2_Post_scale_Value_Set(_timer->Post_scale_value);
        TIMER2_Pre_scale_Value_Set(_timer->pre_scaler_value);        

        timer2_preload = _timer->timer2_preload_value;  
/*==========================================================*/
/* Interrupt Configurations */         
#if TMR2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR2_InterruptDisable();
        TMR2_InterruptFlagClear();
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            TMR2_HighPrioritySet();
            INTERRUPT_GlobalInterruptHighEnable();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            TMR2_LowPrioritySet();
            INTERRUPT_GlobalInterruptLowEnable();
        }
        else{/* Nothing */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif       
        TMR2_InterruptEnable();
#endif
/*==========================================================*/       
        TIMER2_MODULE_ENABLE();
    }
    
    return ret;
}

std_ReturnType Timer2_DeInit(const timer2_t *_timer){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the TIMER2 */
        TIMER2_MODULE_DISABLE();
        /* Interrupt Configurations */  
#if TMR2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TMR2_InterruptDisable();
#endif
    }
    
    return ret;
}

std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = _value;
    }
    
    return ret;
}

std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value){
    std_ReturnType ret = E_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        *_value = TMR2;
    }
    
    return ret;
}


void TMR2_ISR(void){
    TMR2_InterruptFlagClear();              /* Clear the interrupt flag */
    
    TMR2 = timer2_preload;                  /* Initialize the pre-loaded value again */
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();            /* Call the callback function */
    }
}