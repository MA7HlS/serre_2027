/*
 * lcd.h
 *
 *  Created on: Oct 30, 2026
 *      Author: mathi
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"

#define LCD_COLS 16
#define LCD_ROWS 2

void lcd_init(void);
void lcd_clear(void);
int lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_write_char(char c);
int lcd_write_string(const char *text);
int lcd_write_line(uint8_t row, const char *text);

#endif /* INC_LCD_H_ */
