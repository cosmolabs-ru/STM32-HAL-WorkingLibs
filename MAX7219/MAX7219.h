/*
 * MAX7219.h
 *
 *  Created on: 3 мар. 2018 г.
 *      Author: enq
 */

#ifndef MAX7219_H_
#define MAX7219_H_

#include "stm32f1xx_hal.h"

#define NOP 0x00
#define DIGIT0 0x01
#define DIGIT1 0x02
#define DIGIT2 0x03
#define DIGIT3 0x04
#define DIGIT4 0x05
#define DIGIT5 0x06
#define DIGIT6 0x07
#define DIGIT7 0x08
#define DECODE 0x09
#define INTENSITY  0x0A
#define SCAN_LIMIT 0x0B
#define SHUTDOWN   0x0C
#define TEST       0x0F

#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define S8 8
#define S9 9
#define SM 0x0A //minus
#define SE 0x0B
#define SH 0x0C
#define SL 0x0D
#define SP 0x0E
#define SZ 0x0F //blank

#define NSS_L HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
#define NSS_H HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

extern SPI_HandleTypeDef * MAX7219_SPI;
extern uint8_t MAX7219_packet[2];
extern uint8_t MAX7219_buffer[8];

void SPI_Write(uint8_t* packet);
void MAX7219_Init(SPI_HandleTypeDef * spi);
void MAX7219_setShutdown(uint8_t shutdown); //0=off, 1=on
void MAX7219_SetIntensity(uint8_t intensity);
void MAX7219_DirectPrintB(uint8_t code, uint8_t place);
void MAX7219_uitob(uint16_t i, uint8_t pos);
void MAX7219_ClearBuffer();
void MAX7219_MaskDots(uint8_t mask);
void MAX7219_Update();

#endif /* MAX7219_H_ */
