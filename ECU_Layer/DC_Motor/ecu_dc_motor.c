/* 
 * File:   ecu_dc_motor.c
 * Author: Ahmad Paykli
 *
 * Created on January 31, 2026, 10:09 AM
 */

#include "ecu_dc_motor.h"

std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    std_ReturnType ret = E_OK;

    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[0]));
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[1]));
    }
}

std_ReturnType dc_motor_turn_right(const dc_motor_t *_dc_motor){
    std_ReturnType ret = E_OK;

    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{        
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_HIGH);
    }
}

std_ReturnType dc_motor_turn_left(const dc_motor_t *_dc_motor){
    std_ReturnType ret = E_OK;

    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{        
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
    }
}

std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    std_ReturnType ret = E_OK;

    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }
    else{        
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
    }
}