/* 
 * File:   ecu_ seven_seg.c
 * Author: Ahmad Paykli
 *
 * Created on February 3, 2026, 3:46 PM
 */

#include "ecu_ seven_seg.h"

uint8 counter = 0;

std_ReturnType seven_segment_initialize(const segment_t *seg){
    std_ReturnType ret = E_OK;

    if(NULL == seg){
        ret = E_NOT_OK;
    }
    else{
        for(counter = 0; counter < 4; counter++){
            ret = gpio_pin_intialize(&(seg->segment_pins[counter]));
        }
    }
    
    return ret;
}

std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
    std_ReturnType ret = E_OK;

    if(NULL == seg){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN0]), number & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN1]), (number>>1) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN2]), (number>>2) & 0x01);
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGEMENT_PIN3]), (number>>3) & 0x01);
    }
    
    return ret;
}

std_ReturnType mix_seven_segment_initialize(const mix_segment_t *mix_seg){
    std_ReturnType ret = E_OK;

    if(NULL == mix_seg){
        ret = E_NOT_OK;
    }
    else{
        for(counter = 0; counter < 6; counter++){
            ret = gpio_pin_intialize(&(mix_seg->mix_segment_pins[counter]));
        }
    }
    return ret;
}    

std_ReturnType mix_seven_segment_write_number(const mix_segment_t *mix_seg, uint8 number){
    std_ReturnType ret = E_OK;
    
    if(NULL == mix_seg){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN0]), (((number % 10)>>0) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN1]), (((number % 10)>>1) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN2]), (((number % 10)>>2) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN3]), (((number % 10)>>3) & 0x01));
        
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[MIX_ENA_SEGEMENT_PIN1]), (MIX_SEG_ENABLE_PIN));
        
        __delay_ms(15);
        
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[MIX_ENA_SEGEMENT_PIN1]), (MIX_SEG_DISABLE_PIN));

        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN0]), (((number / 10)>>0) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN1]), (((number / 10)>>1) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN2]), (((number / 10)>>2) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[SEGEMENT_PIN3]), (((number / 10)>>3) & 0x01));
        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[MIX_ENA_SEGEMENT_PIN0]), (MIX_SEG_ENABLE_PIN));
        
        __delay_ms(15);

        ret = gpio_pin_write_logic(&(mix_seg->mix_segment_pins[MIX_ENA_SEGEMENT_PIN0]), (MIX_SEG_DISABLE_PIN));
    }
    
    return ret;
}