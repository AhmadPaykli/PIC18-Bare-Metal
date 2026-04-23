/* 
 * File:   ecu_relay.c
 * Author: Ahmad Paykli
 *
 * Created on January 29, 2026, 4:10 AM
 */

#include "ecu_relay.h"

std_ReturnType relay_initialize(const relay_t *relay){
    std_ReturnType ret = E_OK;

    if(NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status
        };
        
        gpio_pin_intialize(&pin_obj);
    }
}

std_ReturnType relay_turn_on(const relay_t *relay){
    std_ReturnType ret = E_OK;

    if(NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status
        };
        
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
}

std_ReturnType relay_turn_off(const relay_t *relay){
        std_ReturnType ret = E_OK;

    if(NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status
        };
        
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
}
