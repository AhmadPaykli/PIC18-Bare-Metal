/* 
 * File:   hal_gpio.c
 * Author: Ahmad Paykli
 *
 * Created on January 23, 2026, 5:24 AM
 */

//*************************************************************************************************************************************************//
//*************************************************************************************************************************************************//

#include "hal_gpio.h"

/* Reference to the Data Direction Control Registers */
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};

/* Reference to the Data Latch Register (Read and Write to Data Latch) */
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};

/* Reference to the Port Status Register  */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

//*************************************************************************************************************************************************//
//*************************************************************************************************************************************************//

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT: 
                SET_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status){
    std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(*tris_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret, *direction_status;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            case GPIO_HIGH: 
                SET_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || NULL == logic){
        ret = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_registers[_pin_config->port], _pin_config->pin);
    }
    
    return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @return 
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
    std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(_pin_config);
        ret = gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    
    return ret;
}
#endif

//*************************************************************************************************************************************************//
//*************************************************************************************************************************************************//

/**
 * 
 * @param port
 * @param direction
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction){
    std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param direction_status
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status){
    std_ReturnType ret = E_OK;
    
    if(NULL == direction_status || (port > PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK;
    }
    else{
        *direction_status = *tris_registers[port];
    }
    
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
    std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }
    return ret;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
    std_ReturnType ret = E_OK;
    
    if(NULL == logic || (port > PORT_MAX_NUMBER-1)){
        ret = E_NOT_OK;
    }
    else{
        *logic = *lat_registers[port];
    }
    
    return ret;
}
#endif

/**
 * 
 * @param port
 * @return 
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
std_ReturnType gpio_port_toggle_logic(port_index_t port){
    std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] ^= PORTC_MASK;
    }
    return ret;
}
#endif