/* 
 * File:   ecu_keypad.h
 * Author: Ahmad Paykli
 *
 * Created on February 4, 2026, 9:56 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4 

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif	/* ECU_KEYPAD_H */

