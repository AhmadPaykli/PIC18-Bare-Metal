/* 
 * File:   mcal_internal_interrupt.c
 * Author: Ahmad Paykli
 *
 * Created on February 1, 2026, 12:55 PM
 */

#include "mcal_internal_interrupt.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/************************************************************************************************/
static ADC_Handler ADC_InterruptHandler = NULL;
/************************************************************************************************/
std_ReturnType ADC_SetInterruptHandler(ADC_Handler _Handler);
/************************************************************************************************/
std_ReturnType ADC_SetInterruptHandler(ADC_Handler _Handler){
  std_ReturnType ret = E_OK;
    
    if(NULL == _Handler){
        ret = E_NOT_OK;
    }
    else{
        ADC_InterruptHandler = _Handler;
    }
    
    return ret;  
}
/************************************************************************************************/
void ADC_ISR(void){
    /* The ADC interrupt occurred (Flag must be cleared in software) */
    ADC_InterruptFlagClear();
    /* Code */
    /* Callback function gets called every time this ISR executes */
    if(ADC_InterruptHandler){ ADC_InterruptHandler(); }
    else{/* Nothing */}
}
#endif