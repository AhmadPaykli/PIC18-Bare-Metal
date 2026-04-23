/* 
 * File:   ecu_keypad.c
 * Author: Ahmad Paykli
 *
 * Created on February 4, 2026, 9:56 AM
 */

#include "ecu_keypad.h"

#define _XTAL_FREQ 8000000

static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'}
};

std_ReturnType keypad_initialize(const keypad_t *_keypad_obj){
    std_ReturnType ret = E_OK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
    
    
    if(NULL == _keypad_obj){
        ret = E_NOT_OK;
    }
    else{
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++){
            ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter = 0; columns_counter < ECU_KEYPAD_ROWS; columns_counter++){
            ret = gpio_pin_direction_intialize(&(_keypad_obj->keypad_row_pins[columns_counter]));
        }
    }
    
    return ret;
}

std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value){
    std_ReturnType ret = E_OK;
    uint8 reset_rows_counter = ZERO_INIT, reset_columns_counter = ZERO_INIT, *button_value = ZERO_INIT;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
    
    
    if(NULL == _keypad_obj){
        ret = E_NOT_OK;
    }
    else{
        for(reset_rows_counter = 0; reset_rows_counter < ECU_KEYPAD_ROWS; reset_rows_counter++){
            ret = gpio_pin_write_logic(&_keypad_obj->keypad_row_pins[reset_rows_counter], GPIO_LOW);
            for(reset_columns_counter = 0; reset_columns_counter < ECU_KEYPAD_COLUMNS; reset_columns_counter++){
                ret = gpio_pin_write_logic(&_keypad_obj->keypad_columns_pins[reset_columns_counter], GPIO_LOW);
            }
        }
        
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++){
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[rows_counter]), GPIO_HIGH);
            for(columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++){
                gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pins[columns_counter]), &button_value);
                if (button_value == GPIO_HIGH) { 
                    *value = btn_values[rows_counter][columns_counter];
                }
                __delay_ms(1);
            }
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[rows_counter]), GPIO_LOW);
        }
    }
    
    return ret;
}