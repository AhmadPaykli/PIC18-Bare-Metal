/* 
 * File:   ecu_relay.h
 * Author: Ahmad Paykli
 *
 * Created on January 29, 2026, 4:10 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    uint8 relay_port : 3;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType relay_initialize(const relay_t *relay);
std_ReturnType relay_turn_on(const relay_t *relay);
std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

