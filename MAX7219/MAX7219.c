/*
 * MAX7219.c
 *
 *  Created on: 3 мар. 2018 г.
 *      Author: enq
 */

#include "stm32f1xx_hal.h"
#include "MAX7219.h"

SPI_HandleTypeDef * MAX7219_SPI;
uint8_t MAX7219_packet[2];
uint8_t MAX7219_buffer[8];

#define CMD  0x00
#define DATA 0x01
#define NSS_L HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET);
#define NSS_H HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET);

void SPI_Write(uint8_t* packet){
	NSS_L;
	HAL_SPI_Transmit(MAX7219_SPI, packet, 2, 10);
	NSS_H;
}

void MAX7219_SetBCode(uint8_t enabled){
	MAX7219_packet[CMD]  = DECODE;
	if(enabled > 0) {
		MAX7219_packet[DATA] = 0xFF;
	} else {
		MAX7219_packet[DATA] = 0x00;
	}
	SPI_Write (MAX7219_packet);
	HAL_Delay(10);
}

void MAX7219_SetIntensity(uint8_t intensity){
	MAX7219_packet[CMD]  = INTENSITY;
	MAX7219_packet[DATA] = intensity;
	SPI_Write (MAX7219_packet);
	HAL_Delay(1);
}

void MAX7219_setShutdown(uint8_t shutdown){
	//0=off, 1=on
	MAX7219_packet[CMD]  = SHUTDOWN;
	MAX7219_packet[DATA] = shutdown;
	SPI_Write (MAX7219_packet);
	HAL_Delay(10);
}

void MAX7219_Init(SPI_HandleTypeDef * spi){
	MAX7219_SPI = spi;

	MAX7219_packet[CMD]  = SHUTDOWN;
	MAX7219_packet[DATA] = 0x01;
	SPI_Write (MAX7219_packet);
	HAL_Delay(10);

	MAX7219_SetIntensity(0x0F);

	MAX7219_SetBCode(1);

	MAX7219_packet[CMD]  = SCAN_LIMIT;
	MAX7219_packet[DATA] = 0x07;
	SPI_Write (MAX7219_packet);
	HAL_Delay(10);
}

void MAX7219_DirectPrintB(uint8_t code, uint8_t place){
	MAX7219_packet[CMD]  = DECODE;
	MAX7219_packet[DATA] = 0xFF;
	SPI_Write (MAX7219_packet);
	HAL_Delay(10);

	MAX7219_packet[CMD]  = place;
	MAX7219_packet[DATA] = code;
	SPI_Write (MAX7219_packet);
	HAL_Delay(10);
}

void MAX7219_uitob(uint16_t i, uint8_t pos){
	//converts uint16_t to B-Code and prints at given position
	MAX7219_buffer[pos] = i / 100;
	if(MAX7219_buffer[pos] == 0) MAX7219_buffer[pos] = SZ;
	MAX7219_buffer[pos-1] = (i % 100) /10;
	MAX7219_buffer[pos-2] = i - (i/100)*100 - MAX7219_buffer[pos-1]*10;

	if (MAX7219_buffer[pos] == SZ) {
		MAX7219_buffer[pos] = MAX7219_buffer[pos-1];
		MAX7219_buffer[pos-1] = MAX7219_buffer[pos-2];
		MAX7219_buffer[pos-2] = SZ;
	}

}

void MAX7219_ClearBuffer(){
	for (short i=DIGIT0; i<=DIGIT7; i++){
		MAX7219_buffer[i-1] = SZ;
	}
}

void MAX7219_MaskDots(uint8_t mask){
	for (short i = DIGIT0; i<= DIGIT7; i++){
		if (mask & 1<<(i-1)) MAX7219_buffer[i-1] |= 1<<7; else MAX7219_buffer[i-1] &= ~(1<<7);
	}
}

#ifdef __STM32F1xx_HAL_RTC_H
void MAX7219_PrintTime(RTC_TimeTypeDef * time, uint8_t pos){
	if(pos < DIGIT3 || pos > DIGIT7) return;
	pos--;
	MAX7219_buffer[pos] = time->Hours / 10;
	MAX7219_buffer[pos-1] = time->Hours % 10;
	MAX7219_buffer[pos-2] = time->Minutes / 10;
	MAX7219_buffer[pos-3] = time->Minutes % 10;

	if(time->Seconds %2 == 0){
		MAX7219_buffer[pos-1] |= 1<<7;
	}else{
		MAX7219_buffer[pos-1] &= ~(1<<7);
	}

}
#endif

void MAX7219_Update(){
	for (short i=DIGIT0; i<=DIGIT7; i++){
		MAX7219_packet[CMD] = i;
		MAX7219_packet[DATA]= MAX7219_buffer[i-1];
		SPI_Write(MAX7219_packet);
	}
}
