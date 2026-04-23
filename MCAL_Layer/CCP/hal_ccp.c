/* 
 * File:   hal_ccp1.c
 * Author: Ahmad Paykli
 *
 * Created on March 5, 2026, 2:44 AM
 */

#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*CCP1_InterruptHandler)(void) = NULL;
//static void CCP1_ISR(void);
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*CCP2_InterruptHandler)(void) = NULL;
//static void CCP2_ISR(void);
#endif

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);

/*==========================================================*/

std_ReturnType CCP_Init(const ccp_t *_ccp_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == _ccp_obj){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_INST == _ccp_obj->ccp_inst){
            
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            
        }
        else{/* Nothing */}
    }
    
    return ret;
}
std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED)
std_ReturnType CCP_IsCapturedDataReady(uint8 *_capture_status);
std_ReturnType CCP_Capture_Mode_Read_Value(uint16 *capture_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED)
std_ReturnType CCP_IsCompareComplete(uint8 *_compare_status);
std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, uint16 compare_value);
#endif

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const uint8 _duty);
std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj);
std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj);
#endif

static void CCP_Interrupt_Config(const ccp_t *_ccp_obj){
/* CCP1 Interrupt Configurations */         
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP1_InterruptDisable();
    CCP1_InterruptFlagClear();
    CCP1_InterruptHandler = _ccp_obj->CCP1_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();

    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP1_priority){
        CCP1_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP1_priority){
        CCP1_LowPrioritySet();
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else{/* Nothing */}
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif       
    CCP1_InterruptEnable();
#endif
/*==========================================================*/
/* CCP2 Interrupt Configurations */         
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_InterruptDisable();
    CCP2_InterruptFlagClear();
    CCP2_InterruptHandler = _ccp_obj->CCP2_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PriorityLevelsEnable();

    if(INTERRUPT_HIGH_PRIORITY == _ccp_obj->CCP2_priority){
        CCP2_HighPrioritySet();
        INTERRUPT_GlobalInterruptHighEnable();
    }
    else if(INTERRUPT_LOW_PRIORITY == _ccp_obj->CCP2_priority){
        CCP2_LowPrioritySet();
        INTERRUPT_GlobalInterruptLowEnable();
    }
    else{/* Nothing */}
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif       
    CCP2_InterruptEnable();
#endif 
}

