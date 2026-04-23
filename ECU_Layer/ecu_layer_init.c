/* 
 * File:   ecu_layer_init.c
 * Author: Ahmad Paykli
 *
 * Created on February 4, 2026, 10:01 AM
 */

#include "ecu_layer_init.h"

void Defualt_TMR3_InterruptHandler(void);

ccp_t ccp1 ={
    .ccp_inst = CCP1_INST,
    .ccp_mode = CCP_PWM_MODE_SELECTED,
    .ccp_mode_variant = CCP_PWM_MODE,
    .ccp_pin.port = PORTC_INDEX,
    .ccp_pin.pin = GPIO_PIN2,
    .ccp_pin.direction = GPIO_DIRECTION_OUTPUT,
    .ccp_pin.logic = GPIO_LOW,
    .PWM_Frequency = 20000,
    .timer2_postscaler_value = 1,
    .timer2_prescaler_value = 1,
    .ccp_capture_timer = CCP1_CCP2_TIMER1
};

timer3_t timer3_obj = {
    .TMR3_InterruptHandler = Defualt_TMR3_InterruptHandler,
    .timer3_mode = TIMER3_COUNTER_MODE,
    .timer3_preload_value = 0,
    .prescaler_value = Prescale_Value_1,
    .timer3_counter_SYNC = TIMER3_COUNTER_SYNC
};

led_t led_1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = LED_OFF};

std_ReturnType ecu_layer_initialize(void){  
    ret = Timer3_Init(&timer3_obj);
    ret = led_intialize(&led_1);
}