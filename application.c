/* 
 * File:   application.c
 * Author: Ahmad Paykli
 *
 * Created on January 23, 2026, 5:24 AM
 */

#include "application.h"
/*********************************************/
uint8 timer3_register_value = 0;
uint16 timer3_flag = 0;
/******************************************************************************************/
void Defualt_TMR3_InterruptHandler(void);
/******************************************************************************************/

/*********************************************/
int main() {
    ret = ecu_layer_initialize();
    
    while(1){
        ret = Timer3_Read_Value(&timer3_obj, &timer3_register_value);
    }
    
    return (EXIT_SUCCESS);
}

void Defualt_TMR3_InterruptHandler(void){
    timer3_flag++;
    led_turn_toggle(&led_1);
}