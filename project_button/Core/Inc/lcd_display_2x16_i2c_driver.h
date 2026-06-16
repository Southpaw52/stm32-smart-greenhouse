/*
 * lcd_display_2x16_i2c_driver.h
 *
 *  Created on: Feb 14, 2026
 *      Author: bahti
 */

#ifndef INC_LCD_DISPLAY_2X16_I2C_DRIVER_H_
#define INC_LCD_DISPLAY_2X16_I2C_DRIVER_H_

#include "main.h"
#include "stdbool.h"
#include "stdarg.h"

#define LCD_I2C_DEVICE_ADRESS 			    (0x4EU)

//Function Set Flags
#define LCD_8BIT_MODE						(0x10U)
#define LCD_4BIT_MODE						(0x00U)
#define LCD_2_LINE							(0x08U)
#define LCD_1_LINE							(0x00U)
#define LCD_5x11_DOTS						(0x04U)
#define LCD_5x8_DOTS						(0x00U)

// Entry Mode Set Flags
#define LCD_ENTRY_RIGHT						(0x00U)
#define LCD_ENTRY_LEFT						(0x02U)
#define LCD_ENTRY_SHIFT_INCREMENT 			(0x01U)
#define LCD_ENTRY_SHIFT_DECREMENT			(0x00U)

/*  ********** LCD Commands ********** */
typedef enum
{
	LCD_Cmd_ClearDisplay					=(0x01U), 	//0<<1
	LCD_Cmd_ReturnHome						=(0x02U),	//1<<1
	LCD_Cmd_EntryMode						=(0x04U),	//2<<1
	LCD_Cmd_DisplayOnOff					=(0x08U),
	LCD_Cmd_CursorShift						=(0x10U),
	LCD_Cmd_FunctionSet						=(0x20U),
	LCD_Cmd_Set_CGRAM_Address				=(0x40U),
	LCD_Cmd_Set_DDRAM_Address				=(0x80U)
}LCD_Commands;

/*  ********** Display Setups ********** */
typedef enum
{
	LCD_Display_On							=(0x04U),
	LCD_Display_Cursor						=(0x02U),
	LCD_Display_BlinkOn						=(0x01U)
}LCD_Display_Control_Flags;

/*  ********** LCD Structure ********** */
typedef struct
{
	I2C_HandleTypeDef 	*hi2c;
	uint8_t				i2c_addr;
	uint8_t				colums;
	uint8_t				rows;
	bool				backlight;
	uint8_t				display_control;
}LCD_t;

/*  ********** LCD APIs Functions ********** */
void LCD_Init(LCD_t *lcd);
void LCD_Send_InitNibble(LCD_t *lcd, uint8_t nibble);
void LCD_Clear(LCD_t *lcd);
void LCD_Home(LCD_t *lcd);
void LCD_Set_Cursor(LCD_t *lcd, uint8_t row, uint8_t col);
void LCD_Send_Char(LCD_t *lcd, char ch);
void LCD_Send_String(LCD_t *lcd, const char *str);
void LCD_Send_Command(LCD_t *lcd, uint8_t cmd);
void LCD_Send_Data(LCD_t *lcd, uint8_t data);
void LCD_Backlight_On(LCD_t *lcd);
void LCD_Backlight_Off(LCD_t *lcd);
void LCD_Cursor_Show(LCD_t *lcd);
void LCD_Cursor_Hide(LCD_t *lcd);
void LCD_Printf(LCD_t *lcd, const char *format, ...);	//3 nokta sınırsız sayıda değer alabilir
void LCD_Scroll_Text(LCD_t *lcd, const char *text, uint8_t, uint16_t delayMS);	//Mesajı kaydırarak yazma

#endif /* INC_LCD_DISPLAY_2X16_I2C_DRIVER_H_ */
