/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gyro.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t can1_count = 0;
uint16_t can2_count = 0;
uint8_t tx_data[8];
uint8_t rx_data[8];
CAN_RxHeaderTypeDef canRxHeader;
uint16_t can2_clear = 0;
uint8_t speed = 0x88;
uint8_t swl_state = 0;
uint8_t swe_state = 1;
uint8_t swr_state = 0;

uint8_t check_who_am_i = 0;
uint8_t who_am_i = 0;
uint8_t check_count = 0;

uint16_t uart1_count = 0;
uint16_t uart2_count = 0;
uint16_t uart3_count = 0;
uint16_t uart4_count = 0;
uint16_t uart5_count = 0;
uint16_t uart6_count = 0;
uint16_t all_uart_count = 0;

uint8_t tx_uart[2] = {0x00, 0x00};
uint8_t rx_uart[2];
uint8_t time_count = 0;

//For Gyro Test
float g_angle_pitch = 0.0f;
float g_angle_roll  = 0.0f;
float g_angle_yaw = 0.0f;
float g_omega_pitch = 0.0f;
float g_omega_roll  = 0.0f;
float g_omega_yaw = 0.0f;
uint16_t main_loop = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim6.Instance) {
		time_count++;
	}
	if(time_count == 0)	{
		HAL_GPIO_TogglePin(LED5_GPIO_Port, LED5_Pin);
		HAL_GPIO_TogglePin(LED6_GPIO_Port, LED6_Pin);
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
	all_uart_count++;

	if (UartHandle->Instance == huart1.Instance) {	//Propo-receive Interrupts
		uart1_count++;
		HAL_UART_Receive_IT(&huart1, rx_uart, 2);
	}
	else if (UartHandle->Instance == huart2.Instance) {
		uart2_count++;
		HAL_UART_Receive_IT(&huart2, rx_uart, 2);
	}
	else if (UartHandle->Instance == huart3.Instance) {
		uart3_count++;
		HAL_UART_Receive_IT(&huart3, rx_uart, 2);
	}
	else if (UartHandle->Instance == huart4.Instance) {
		uart4_count++;
		HAL_UART_Receive_IT(&huart4, rx_uart, 2);
	}
	else if (UartHandle->Instance == huart5.Instance) {
		uart5_count++;
		HAL_UART_Receive_IT(&huart5, rx_uart, 2);
	}
	else if (UartHandle->Instance == huart6.Instance) {
		uart6_count++;
		HAL_UART_Receive_IT(&huart6, rx_uart, 2);
	}
	if(all_uart_count % 5 == 0){
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

	}
}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {
	if (UartHandle->Instance == huart3.Instance) {
		//Custom_data_Transmit
	}
}

//can fifo0 receive interrupt
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/* Get RX message */
	if (hcan->Instance == hcan2.Instance)
	{// can2 bus receive interrupt
		can2_count++;
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &canRxHeader, rx_data);
		//check ESC identifier
		if(canRxHeader.StdId == 0x1ff){
			can2_clear++;
		}
	}
	if (hcan->Instance == hcan1.Instance)
	{// can1 bus receive interrupt
		can1_count++;
	}

	if(can2_clear % 5 == 0){
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);

	}
}

void initCanFilter() {
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 0;

	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);

	sFilterConfig.SlaveStartFilterBank = 0;
	sFilterConfig.FilterBank = 0;

	HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig);
}

void initGyro(void) {
	uint8_t who_am_i = ReadByte(ADDRESS_WHO_AM_I);

	if(who_am_i != VALUE_WHO_AM_I)
	{
		who_am_i = ReadByte(ADDRESS_WHO_AM_I);
		check_who_am_i = who_am_i;
		while(who_am_i != VALUE_WHO_AM_I){
			who_am_i = ReadByte(ADDRESS_WHO_AM_I);
			HAL_Delay(100);
			check_count++;
		}
	}

	check_who_am_i = who_am_i;
	WriteByte(ADDRESS_REG_BANK_SEL,VALUE_USER_BANK_0);
	HAL_Delay(10);
/*
 	WriteByte(0x03,0x78);
	HAL_Delay(10);
*/
  	WriteByte(ADDRESS_PWR_MGMT_1,RESET_PWR_MGMT_1);
	HAL_Delay(10);
	WriteByte(ADDRESS_PWR_MGMT_1,VALUE_PWR_MGMT_1);
	HAL_Delay(10);
	WriteByte(ADDRESS_PWR_MGMT_2,VALUE_PWR_MGMT_2);
	HAL_Delay(10);
	WriteByte(ADDRESS_CONFIG,VALUE_CONFIG);
	HAL_Delay(10);

	WriteByte(ADDRESS_REG_BANK_SEL,VALUE_USER_BANK_2);
	HAL_Delay(10);
	WriteByte(ADDRESS_GYRO_CONFIG1,VALUE_GYRO_CONFIG1);
	HAL_Delay(10);
	WriteByte(ADDRESS_GYRO_SMPLRT_DIV,VALUE_GYRO_SMPLRT_DIV);
	HAL_Delay(10);
	WriteByte(ADDRESS_GYRO_CONFIG2,VALUE_GYRO_CONFIG2);
	HAL_Delay(10);

	WriteByte(ADDRESS_REG_BANK_SEL,VALUE_USER_BANK_0);
	HAL_Delay(10);
	WriteByte(ADDRESS_PWR_MGMT_1,VALUE_LOW_POWER);
	HAL_Delay(10);
}

void transCAN()
{
	CAN_TxHeaderTypeDef header;
	uint32_t TxMailbox;
	uint8_t i;

	header.StdId = 0x1ff;
	header.RTR = CAN_RTR_DATA;
	header.IDE = CAN_ID_STD;
	header.DLC = 8;
	for(i=0;i<8;i++){
		tx_data[i] = 2*i;
	}
	HAL_CAN_AddTxMessage(&hcan1, &header, tx_data, &TxMailbox);
}

uint8_t selectMode()
{
	uint8_t mode;
	while(swe_state == HAL_GPIO_ReadPin(SWE_GPIO_Port, SWE_Pin)){
	  if(swl_state != HAL_GPIO_ReadPin(SWL_GPIO_Port, SWL_Pin))
	  {
		  mode++;
		  swl_state = HAL_GPIO_ReadPin(SWL_GPIO_Port, SWL_Pin);
	  }
	  if(swr_state != HAL_GPIO_ReadPin(SWR_GPIO_Port, SWR_Pin))
	  {
		  mode--;
		  swr_state = HAL_GPIO_ReadPin(SWR_GPIO_Port, SWR_Pin);
	  }

	  if(mode > 252)	mode = 0;
	  mode = mode % 9;

//	  showMode(mode);
//	  printf("mode:%d\n",mode);
	  HAL_Delay(10);

	}
//	printf("START-mode%d\n",mode);
}

void showMode(uint8_t val)
{
	HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, val == 8);
	HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, val == 7);
	HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, val == 6);
	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, val == 5);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, val == 4);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, val == 3);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, val == 2);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, val == 1);
}


int __io_putchar(int c) {
  if( c == '\n' ) {
    int _c = '\r';
    HAL_UART_Transmit(&huart3, &_c, 1, 1);
  }
  HAL_UART_Transmit(&huart3, &c, 1, 1);
  return 0;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_SPI3_Init();
  MX_TIM7_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, 1);
  HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, 1);

  initCanFilter();
  initGyro();

  HAL_Delay(100);
  HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 1);
  HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 1);

  HAL_CAN_Start(&hcan1);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);

  HAL_Delay(100);
  HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1);
  HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1);

  HAL_TIM_Base_Start_IT(&htim6);

  HAL_Delay(100);
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);
  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

//	HAL_UART_Receive_DMA(&huart4, rx_uart, 2);
//printf("OOEDO_SAMURAI_BEGINNING\n");

  HAL_UART_Receive_IT(&huart1, rx_uart, 2);
  HAL_UART_Receive_IT(&huart2, rx_uart, 2);
  HAL_UART_Receive_IT(&huart3, rx_uart, 2);
  HAL_UART_Receive_IT(&huart4, rx_uart, 2);
  HAL_UART_Receive_IT(&huart5, rx_uart, 2);
  HAL_UART_Receive_IT(&huart6, rx_uart, 2);

  MelodySummer();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		  main_loop++;
		  HAL_UART_Transmit(&huart1,tx_uart,2,1);
		  HAL_UART_Transmit(&huart2,tx_uart,2,1);
		  HAL_UART_Transmit(&huart3,tx_uart,2,1);
		  HAL_UART_Transmit(&huart4,tx_uart,2,1);
		  HAL_UART_Transmit(&huart5,tx_uart,2,1);
		  HAL_UART_Transmit(&huart6,tx_uart,2,1);

		  transCAN();
		  HAL_GPIO_TogglePin(LED7_GPIO_Port, LED7_Pin);
		  HAL_GPIO_TogglePin(LED8_GPIO_Port, LED8_Pin);

		  HAL_Delay(500);

//	  selectMode();
/*	  speed = 50;

	  tx_uart[0] = time_count;
//	  HAL_UART_Transmit(&huart1,tx_uart, 2, 1);
//	  HAL_UART_Transmit(&huart3,tx_uart,2,1);

	  transCAN();
*/
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
