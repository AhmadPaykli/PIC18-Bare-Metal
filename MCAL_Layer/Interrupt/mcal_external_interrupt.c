/* 
 * File:   mcal_external_interrupt.c
 * Author: Ahmad Paykli
 *
 * Created on February 1, 2026, 12:55 PM
 */

#include "mcal_external_interrupt.h"
/************************************************************************************************/
static interrupt_handler_t INT0_InterruptHandler = NULL;
static interrupt_handler_t INT1_InterruptHandler = NULL;
static interrupt_handler_t INT2_InterruptHandler = NULL;
/************************************************************************************************/
static interrupt_handler_t RB4_InterruptHandler_High = NULL;
static interrupt_handler_t RB4_InterruptHandler_Low = NULL;
static interrupt_handler_t RB5_InterruptHandler_High = NULL;
static interrupt_handler_t RB5_InterruptHandler_Low = NULL;
static interrupt_handler_t RB6_InterruptHandler_High = NULL;
static interrupt_handler_t RB6_InterruptHandler_Low = NULL;
static interrupt_handler_t RB7_InterruptHandler_High = NULL;
static interrupt_handler_t RB7_InterruptHandler_Low = NULL;
/************************************************************************************************/
static std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);
/************************************************************************************************/
static std_ReturnType INT0_SetInterruptHandler(interrupt_handler_t);
static std_ReturnType INT1_SetInterruptHandler(interrupt_handler_t);
static std_ReturnType INT2_SetInterruptHandler(interrupt_handler_t);
static std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
/************************************************************************************************/
static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *RB_obj);
static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *RB_obj);
static std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *RB_obj);
static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *RB_obj);
/************************************************************************************************/
std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the External interrupt */
        ret =  Interrupt_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External interrupt did not occur */
        ret =  Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure External interrupt edge */
        ret =  Interrupt_INTx_Edge_Init(int_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        /* Configure External interrupt Priority */
        ret =  Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /* Configure External interrupt I/O pin */
        ret =  Interrupt_INTx_Pin_Init(int_obj);
        /* Configure Default Interrupt CallBack */
        ret =  Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the External interrupt */
        ret =  Interrupt_INTx_Enable(int_obj);
    }
    
    return ret;
}

std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
       ret =  Interrupt_INTx_Disable(int_obj);
    }
    
    return ret;
}
/************************************************************************************************/
void INT0_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    /* Code */
    /* Callback function gets called every time this ISR executes */
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else{/* Nothing */}
}

void INT1_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    /* Code */

    /* Callback function gets called every time this ISR executes */
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else{/* Nothing */}
}

void INT2_ISR(void){
    /* The INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    /* Code */

    /* Callback function gets called every time this ISR executes */
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else{/* Nothing */}
}
/************************************************************************************************/
static std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable(); 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_INT1_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_INT1_HighPrioritySet();
                }
                else{/* Nothing */}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_InterruptEnable(); 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_INT2_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_INT2_HighPrioritySet();
                }
                else{/* Nothing */}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable(); 
                break;
        }
    }
    
    return ret;
}

static std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptDisable(); break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptDisable(); break;
        }
    }
    
    return ret;
}
 #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT1_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT1_HighPrioritySet();
                }
                else{/* Nothing */}
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT2_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT2_HighPrioritySet();
                }
                else{/* Nothing */}
                break;
        }
    }
    
    return ret;
}
#endif
static std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->edge){
            case INTERRUPT_EXTERNAL_INT0 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT0_FallingEdgeSet();
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT0_RisingEdgeSet();
                }
                else{/* Nothing */}
                break;
            case INTERRUPT_EXTERNAL_INT1 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT1_FallingEdgeSet();
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT1_RisingEdgeSet();
                }
                else{/* Nothing */}
                break;
            case INTERRUPT_EXTERNAL_INT2 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT2_FallingEdgeSet();
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT2_RisingEdgeSet();
                }
                else{/* Nothing */}
                break;
        }
    }
    
    return ret;
}

static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    
    return ret;
}

static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : EXT_INT0_InterruptFlagClear(); break;
            case INTERRUPT_EXTERNAL_INT1 : EXT_INT1_InterruptFlagClear(); break;
            case INTERRUPT_EXTERNAL_INT2 : EXT_INT2_InterruptFlagClear(); break;
        }
    }
    
    return ret;
}
/************************************************************************************************/
static std_ReturnType INT0_SetInterruptHandler(void (*interrupt_handler_t)(void)){
    std_ReturnType ret = E_OK;              
    
    if(NULL == interrupt_handler_t){
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = interrupt_handler_t;
    }
    
    return ret;
}

static std_ReturnType INT1_SetInterruptHandler(void (*interrupt_handler_t)(void)){
    std_ReturnType ret = E_OK;
    
    if(NULL == interrupt_handler_t){
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = interrupt_handler_t;
    }
    
    return ret;
}

static std_ReturnType INT2_SetInterruptHandler(void (*interrupt_handler_t)(void)){
  std_ReturnType ret = E_OK;
    
    if(NULL == interrupt_handler_t){
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = interrupt_handler_t;
    }
    
    return ret;  
}

static std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler); break;
            case INTERRUPT_EXTERNAL_INT1 : ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler); break;
            case INTERRUPT_EXTERNAL_INT2 : ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler); break;
        }
    }
    
    return ret;
}
/************************************************************************************************/
std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *RB_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == RB_obj){
        ret = E_NOT_OK;
    }
    else{
        Interrupt_RBx_Disable(RB_obj);
        EXT_RBx_InterruptFlagClear();
        Interrupt_RBx_Pin_Init(RB_obj);
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        Interrupt_RBx_Priority_Init(RB_obj);
        #endif

        switch(RB_obj->mcu_pin.pin){
            case GPIO_PIN4:
                RB4_InterruptHandler_High = RB_obj->EXT_InterruptHandler_High;
                RB4_InterruptHandler_Low = RB_obj->EXT_InterruptHandler_Low;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_High = RB_obj->EXT_InterruptHandler_High;
                RB5_InterruptHandler_Low = RB_obj->EXT_InterruptHandler_Low;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_High = RB_obj->EXT_InterruptHandler_High;
                RB6_InterruptHandler_Low = RB_obj->EXT_InterruptHandler_Low;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_High = RB_obj->EXT_InterruptHandler_High;
                RB7_InterruptHandler_Low = RB_obj->EXT_InterruptHandler_Low;
                break;
        }
        
        Interrupt_RBx_Enable(RB_obj);
    }
    
    return ret;
}

std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *RB_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == RB_obj){
        ret = E_NOT_OK;
    }
    else{
        
    }
    
    return ret;
}
/************************************************************************************************/
void RB4_ISR(uint8 RB4_High_Or_Low){
    /* The RB4 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    /* Callback function gets called every time this ISR executes */
    if(0 == RB4_High_Or_Low){
        if(RB4_InterruptHandler_Low){ RB4_InterruptHandler_Low(); }
        else{/* Nothing */}
    }
    else if(1 == RB4_High_Or_Low){
        if(RB4_InterruptHandler_High){ RB4_InterruptHandler_High(); }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}

void RB5_ISR(uint8 RB5_High_Or_Low){
    /* The RB5 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    /* Callback function gets called every time this ISR executes */
    if(0 == RB5_High_Or_Low){
        if(RB5_InterruptHandler_Low){ RB5_InterruptHandler_Low(); }
        else{/* Nothing */}
    }
    else if(1 == RB5_High_Or_Low){
        if(RB5_InterruptHandler_High){ RB5_InterruptHandler_High(); }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}

void RB6_ISR(uint8 RB6_High_Or_Low){
    /* The RB6 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    /* Callback function gets called every time this ISR executes */
    if(0 == RB6_High_Or_Low){
        if(RB6_InterruptHandler_Low){ RB6_InterruptHandler_Low(); }
        else{/* Nothing */}
    }
    else if(1 == RB6_High_Or_Low){
        if(RB6_InterruptHandler_High){ RB6_InterruptHandler_High(); }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}

void RB7_ISR(uint8 RB7_High_Or_Low){
    /* The RB7 external interrupt occurred (must be cleared in software) */
    EXT_RBx_InterruptFlagClear();
    /* Code */
    /* Callback function gets called every time this ISR executes */
    if(0 == RB7_High_Or_Low){
        if(RB7_InterruptHandler_Low){ RB7_InterruptHandler_Low(); }
        else{/* Nothing */}
    }
    else if(1 == RB7_High_Or_Low){
        if(RB7_InterruptHandler_High){ RB7_InterruptHandler_High(); }
        else{/* Nothing */}
    }
    else{/* Nothing */}
}

/************************************************************************************************/
static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *RB_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == RB_obj){
        ret = E_NOT_OK;
    }
    else{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        
        switch(RB_obj->priority){
            case INTERRUPT_HIGH_PRIORITY :
                INTERRUPT_GlobalInterruptHighEnable();
                break;
            case INTERRUPT_LOW_PRIORITY :
                INTERRUPT_GlobalInterruptLowEnable();
                break;
        }
#else
        ret = INTERRUPT_GlobalInterruptEnable();
        ret = INTERRUPT_PeripheralInterruptEnable();
        ret = EXT_RBx_InterruptEnable();
#endif
        
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *RB_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == RB_obj){
        ret = E_NOT_OK;
    }
    else{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsDisable();
        
        switch(RB_obj->priority){
            case INTERRUPT_HIGH_PRIORITY :
                INTERRUPT_GlobalInterruptHighDisable();
                break;
            case INTERRUPT_LOW_PRIORITY :
                INTERRUPT_GlobalInterruptLowDisable();
                break;
        }
#else
        ret = INTERRUPT_GlobalInterruptDisable();
        ret = INTERRUPT_PeripheralInterruptDisable();
        ret = EXT_RBx_InterruptDisable();
#endif
        
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *RB_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == RB_obj){
        ret = E_NOT_OK;
    }
    else{
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        switch(RB_obj->priority){
            case INTERRUPT_HIGH_PRIORITY :
                EXT_RBx_Priority_High();
                break;
            case INTERRUPT_LOW_PRIORITY :
                EXT_RBx_Priority_Low();
                break;
        }
        #endif
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *RB_obj){
    std_ReturnType ret = E_OK;
    
    if(NULL == RB_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(RB_obj->mcu_pin));
    }
    
    return ret;
}
/************************************************************************************************/