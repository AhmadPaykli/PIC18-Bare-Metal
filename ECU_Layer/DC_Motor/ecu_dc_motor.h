/* 
 * File:   ecu_dc_motor.h
 * Author: Ahmad Paykli
 *
 * Created on January 31, 2026, 10:09 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* ----------------- Includes -----------------*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
std_ReturnType dc_motor_turn_right(const dc_motor_t *_dc_motor);
std_ReturnType dc_motor_turn_left(const dc_motor_t *_dc_motor);
std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);

#endif	/* ECU_DC_MOTOR_H */

