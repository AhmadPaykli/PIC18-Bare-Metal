/* 
 * File:   ecu_layer_init.h
 * Author: Ahmad Paykli
 *
 * Created on February 4, 2026, 10:01 AM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* ----------------- Includes -----------------*/
#include "LED/ecu_led.h"
#include "Relay/ecu_relay.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "button/ecu_button.h"
#include "../MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "7_segment/ecu_ seven_seg.h"
#include "Keypad/ecu_keypad.h"
#include "../MCAL_Layer/mcal_std_types.h"
#include "chr_lcd/Ecu_chr_lcd.h"
#include "../MCAL_Layer/ADC/hal_adc.h"
#include "../MCAL_Layer/Timer_0/hal_timer0.h"
#include "../MCAL_Layer/Timer_1/hal_timer1.h"
#include "../MCAL_Layer/Timer_2/hal_timer2.h"
#include "../MCAL_Layer/Timer_3/hal_timer3.h"
#include "../MCAL_Layer/CCP/hal_ccp.h"

/* ----------------- Macro Declarations -----------------*/
std_ReturnType ret = E_NOT_OK;

extern timer3_t timer3_obj;
extern led_t led_1;
extern ccp_t ccp1;


/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */