/*
 * lcdi2c.h
 *
 *  Created on: 23 мар. 2019 г.
 *      Author: enq
 */

#ifndef LCDI2C_H_
#define LCDI2C_H_

#define LCD_ADDR (0x27 << 1)

#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)

#define LCD_DELAY_MS 5

void I2C_Scan();
HAL_StatusTypeDef LCD_SendInternal(uint8_t lcd_addr, uint8_t data, uint8_t flags);
void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd);
void LCD_SendData(uint8_t lcd_addr, uint8_t data);
void LCD_Init(uint8_t lcd_addr);
void LCD_SendString(uint8_t lcd_addr, char *str);
void LCD_GotoXY(uint8_t x, uint8_t y);

#endif /* LCDI2C_H_ */
