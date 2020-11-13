/*
 * gyro.c
 *
 *  Created on: 2020/01/01
 *      Author: 標 祥太郎
 */

#include "gyro.h"
#include "main.h"
#include "spi.h"

#define TIME_STEP 0.001f

uint8_t ReadByte(uint8_t addres)
{
	uint8_t trans_addres[2];
	uint8_t receive_data[2];

	trans_addres[0] = addres | 0x80;
	trans_addres[1] = 0x00;

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,RESET);
	HAL_SPI_TransmitReceive(&hspi1,trans_addres,receive_data,2,1);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,SET);
	return receive_data[1];
}

void WriteByte(uint8_t addres,uint8_t data)
{
	uint8_t trans_data[2];
	uint8_t receive_data[2];

	trans_data[0] = addres & 0x7f;
	trans_data[1] = data;

	HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,RESET);
	HAL_SPI_TransmitReceive(&hspi1,trans_data,receive_data,2,1);
	HAL_GPIO_WritePin(SPI_CS_GPIO_Port,SPI_CS_Pin,SET);

}


float ReadGyroYaw(void){
	int16_t omega_raw_z;
	float omega;
	uint8_t yaw_value_h = ReadByte(GYRO_ZOUT_H);						//Read 7-4bit (addres 0x47)
	uint8_t yaw_value_l = ReadByte(GYRO_ZOUT_L);						//Read 3-0bit (addres 0x48)

	omega_raw_z = (int16_t)(yaw_value_h << 8 | yaw_value_l);
	omega = (float)(omega_raw_z / GYRO_FIX);
	return omega;
}

float ReadGyroRoll(void)
{
	int16_t omega_raw_y;
	float omega;

	uint8_t roll_value_h = ReadByte(GYRO_YOUT_H);						//Read 7-4bit (addres 0x45)
	uint8_t roll_value_l = ReadByte(GYRO_YOUT_L);						//Read 3-0bit (addres 0x46)

	omega_raw_y = (int16_t)(roll_value_h << 8 | roll_value_l);
	omega = (float)(omega_raw_y / GYRO_FIX);
	return omega;
}

float ReadGyroPitch(void)
{
	int16_t omega_raw_x;
	float omega;
	uint8_t pitch_value_h = ReadByte(GYRO_XOUT_H);						//Read 7-4bit (addres 0x43)
	uint8_t pitch_value_l = ReadByte(GYRO_XOUT_L);						//Read 3-0bit (addres 0x44)

	omega_raw_x = (int16_t)(pitch_value_h << 8 | pitch_value_l);
	omega = (float)(omega_raw_x / GYRO_FIX);
	return omega;
}
