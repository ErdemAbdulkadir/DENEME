/*
 * ADXL345.c
+ *
 *  Created on: Nov 4, 2023
 *      Author: Abdulkadir Erdem
 */

#include "ADXL345.h"


uint8_t rData[6]={0};
uint16_t Xvalue , Yvalue , Zvalue;
void ADXL345_Init()
{
     ADXL345_Read(0x00, 1); // 0x00 registerından okuma yapıyoruz 0xe5 değeri gelirse sensörde sorun yok
     if(rData[0]!=0xE5)
    	 {
    	 HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
    	 while(1);
    	 }
     ADXL345_Write(0x2D,0x00);// ilk önce power conrol reset atıyoruz.
     ADXL345_Write(0x2D,0x08);// 0x2D (power control register) measure biti 1 geri kalan 0 ve 8Hz freg seçiliyor.

     ADXL345_Write(0x31,0x01);// Data format bitinden range (g) -+4g seçildi
}
static void ADXL345_Read(uint8_t rRegister, uint8_t NumberOfByte)
{

	HAL_I2C_Mem_Read(&hi2c1,ADXL345_ADDREES, rRegister, 1, rData, NumberOfByte, 100000);

}


void ADXL345_Write(uint8_t wRegister, uint8_t value)
{
     uint8_t wData[2];
     wData[0]=wRegister;
     wData[1]= value;
	 HAL_I2C_Master_Transmit(&hi2c1, ADXL345_ADDREES, wData, 2, 100000);
}
int16_t ADXL345_ReadX()
{
	HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDREES, 0x32, 1, rData, 2, 100000);// 0x32 ,0x33

	Xvalue=((rData[1]<<8) | rData[0]);
	return  Xvalue;
}

int16_t ADXL345_ReadY()
{


	HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDREES, 0x34, 1, &rData[2], 2, 100000);//0x34 ,0x35

	Yvalue=((rData[3]<<8) | rData[2]);

	return Yvalue;
}
int16_t ADXL345_ReadZ()
{


	HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDREES, 0x36, 1, &rData[4], 2, 100000);//0x36 ,0x37
	Zvalue=((rData[5]<<8) | rData[4]);
	return  Zvalue;
}
