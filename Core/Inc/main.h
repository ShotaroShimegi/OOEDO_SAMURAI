/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED5_Pin GPIO_PIN_13
#define LED5_GPIO_Port GPIOC
#define LED6_Pin GPIO_PIN_14
#define LED6_GPIO_Port GPIOC
#define LED7_Pin GPIO_PIN_15
#define LED7_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_0
#define LED3_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOC
#define SWL_Pin GPIO_PIN_4
#define SWL_GPIO_Port GPIOA
#define GYRO_CS_Pin GPIO_PIN_4
#define GYRO_CS_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_0
#define BUZZER_GPIO_Port GPIOB
#define SERVO1_Pin GPIO_PIN_1
#define SERVO1_GPIO_Port GPIOB
#define SERVO2_Pin GPIO_PIN_14
#define SERVO2_GPIO_Port GPIOB
#define SERVO3_Pin GPIO_PIN_15
#define SERVO3_GPIO_Port GPIOB
#define SERVO4_Pin GPIO_PIN_9
#define SERVO4_GPIO_Port GPIOC
#define SERVO5_Pin GPIO_PIN_8
#define SERVO5_GPIO_Port GPIOA
#define SPI_CS_Pin GPIO_PIN_9
#define SPI_CS_GPIO_Port GPIOA
#define TOUCH_Pin GPIO_PIN_10
#define TOUCH_GPIO_Port GPIOA
#define SWR_Pin GPIO_PIN_15
#define SWR_GPIO_Port GPIOA
#define LED8_Pin GPIO_PIN_10
#define LED8_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOC
#define SWE_Pin GPIO_PIN_8
#define SWE_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_9
#define LED4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
