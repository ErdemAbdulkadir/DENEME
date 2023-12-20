/*
 * ADXL345.h
 *
 *  Created on: Nov 4, 2023
 *      Author: Abdulkadir Erdem
 */

#ifndef SRC_ADXL345_H_
#define SRC_ADXL345_H_

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
#define ADXL345_ADDREES  0xA6  // 0x53 << 1



void ADXL_Init(void);
static void ADXL345_Read(uint8_t rRegister, uint8_t NumberOfByte);

void ADXL345_Write(uint8_t wRegister , uint8_t NumberOfByte);

int16_t ADXL345_ReadX();
int16_t ADXL345_ReadY();
int16_t ADXL345_ReadZ();

#endif /* SRC_ADXL345_H_ */
