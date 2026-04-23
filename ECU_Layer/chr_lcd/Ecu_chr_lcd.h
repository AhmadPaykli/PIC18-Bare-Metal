/* 
 * File:   Ecu_chr_lcd.h
 * Author: Ahmad Paykli
 *
 * Created on February 7, 2026, 2:13 PM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/* ----------------- Includes -----------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_chr_lcd_cfg.h"

/* ----------------- Macro Declarations -----------------*/
//#define _XTAL_FREQ 8000000

#define _LCD_CLEAR                      0X01 // 0000 0001

#define _LCD_RETURN_HOME                0x02 // 0000 0010

#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04 // 0000 0100
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05 // 0000 0101
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06 // 0000 0110
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07 // 0000 0111

#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10 // 0001 0000
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14 // 0001 0100
#define _LCD_DISPLAY_SHIFT_LEFT         0x18 // 0001 1000
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C // 0001 1100

#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C // 0000 1100
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D // 0000 1101
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E // 0000 1110
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F // 0000 1111
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08 // 0000 1000

#define _LCD_8BIT_MODE_2_LINE           0x38 // 0011 1000
#define _LCD_4BIT_MODE_2_LINE           0x28 // 0010 1000

#define _LCD_CGRAM_START                0x40 // 0100 0000
#define _LCD_DDRAM_START                0x80 // 1000 0000

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/* ----------------- Software Interfaces Declarations -----------------*/
std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd);
std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command);
std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data);
std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row, uint8 column, uint8 data);
std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str);
std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos);

std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);
std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command);
std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);
std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row, uint8 column, uint8 data);
std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str);
std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, 
                                         const uint8 _chr[], uint8 mem_pos);

std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);
std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);
std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);

#endif	/* ECU_CHR_LCD_H */

