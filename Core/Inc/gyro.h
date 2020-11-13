#ifndef gyro_H_
#define gyro_H_

#include<stdint.h>

// MPU6500 Resister
//#define WHO_AM_I 0x75
//#define GYRO_CORREST_REACTION 0x70

#define ADDRESS_REG_BANK_SEL 	0x7F
#define VALUE_USER_BANK_0		0x00
#define VALUE_USER_BANK_1		0x10
#define VALUE_USER_BANK_2		0x20
#define VALUE_USER_BANK_3		0x30

#define ADDRESS_WHO_AM_I 		0x00
#define VALUE_WHO_AM_I 			0xEA

#define	ADDRESS_PWR_MGMT_1 		0x06
#define	ADDRESS_PWR_MGMT_2 		0x07
#define	ADDRESS_CONFIG 			0x05

#define	RESET_PWR_MGMT_1 		0x81
#define	VALUE_PWR_MGMT_1 		0x01
#define VALUE_LOW_POWER			0x01
#define	VALUE_PWR_MGMT_2 		0x00
#define VALUE_CONFIG			0x40


#define ACCEL_XOUT_H 0x00
#define ACCEL_XOUT_L 0x00
#define ACCEL_YOUT_H 0x00
#define ACCEL_YOUT_L 0x00
#define ACCEL_ZOUT_H 0x00
#define ACCEL_ZOUT_L 0x00

#define GYRO_XOUT_H 0x33
#define GYRO_XOUT_L 0x34
#define GYRO_YOUT_H 0x35
#define GYRO_YOUT_L 0x36
#define GYRO_ZOUT_H 0x37
#define GYRO_ZOUT_L 0x38

/****** USER_BANK 2 *******/
#define ADDRESS_GYRO_SMPLRT_DIV 0x00
#define ADDRESS_GYRO_CONFIG1 	0x01
#define ADDRESS_GYRO_CONFIG2 	0x02

#define VALUE_GYRO_SMPLRT_DIV	0x0f
#define VALUE_GYRO_CONFIG1		0x07
#define VALUE_GYRO_CONFIG2		0x00

#define GYRO_FIX  16.4f

typedef struct
{
  int8_t header_flag;
  int16_t mc_angle;
  int16_t mc_omega;

//Created by Shimegi
  float angle_yaw;
  float angle_roll;
  float angle_pitch;
  float omega_yaw;
  float omega_roll;
  float omega_pitch;
  float base_yaw;
  float base_roll;
  float base_pitch;

  float accel_x;
  float accel_y;
  float accel_z;
  float base_accel_x;
  float base_accel_y;
  float base_accel_z;

} gyro_data;

uint8_t ReadByte(uint8_t);
void WriteByte(uint8_t,uint8_t);

void initGyro();
float ReadGyroYaw(void);
float ReadGyroRoll(void);
float ReadGyroPitch(void);
void GetGyroOffset(uint16_t);
int16_t ConvertOmegaToGimbal(float);
int16_t ConvertAngleToGimbal(float);

void gyroTask(void);



#endif /* gyro_H_ */
