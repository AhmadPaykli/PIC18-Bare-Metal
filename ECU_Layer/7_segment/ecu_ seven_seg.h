/* 
 * File:   ecu_ seven_seg.h
 * Author: Ahmad Paykli
 *
 * Created on February 3, 2026, 3:46 PM
 */

#ifndef ECU__SEVEN_SEG_H
#define	ECU__SEVEN_SEG_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
#define SEGEMENT_PIN0 0
#define SEGEMENT_PIN1 1
#define SEGEMENT_PIN2 2
#define SEGEMENT_PIN3 3

#define MIX_ENA_SEGEMENT_PIN0 4
#define MIX_ENA_SEGEMENT_PIN1 5

#define MIX_SEG_DISABLE_PIN 0 
#define MIX_SEG_ENABLE_PIN 1

typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE        
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

typedef struct{
    pin_config_t mix_segment_pins[6];
    segment_type_t segment_type; 
}mix_segment_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType seven_segment_initialize(const segment_t *seg);
std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);

std_ReturnType mix_seven_segment_initialize(const mix_segment_t *mix_seg);
std_ReturnType mix_seven_segment_write_number(const mix_segment_t *mix_seg, uint8 number);

#endif	/* ECU__SEVEN_SEG_H */

