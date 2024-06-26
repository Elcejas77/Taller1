/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
uint32_t tiempo_parpadeo=500;
uint8_t estacionando =0;
uint8_t estado=0;
uint32_t tiempo=HAL_GetTick;
uint8_t contador=0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	  /* EXTI line interrupt detected */
	 if(GPIO_Pin==izquierda_Pin)
	  {HAL_UART_Transmit(&huart2, "d_izquierda\r\n", 13, 10);
	  HAL_GPIO_WritePin(GPIOA, LD3_Pin, 0);
	  HAL_GPIO_EXTI_IRQHandler(estacionar_Pin);
	  estado=1;
	  contador =5;
	 }

	 if(GPIO_Pin==derecha_Pin)
	   {HAL_UART_Transmit(&huart2, "d_derecha\r\n", 11, 10);
	   HAL_GPIO_EXTI_IRQHandler(estacionar_Pin);
	   HAL_GPIO_WritePin(GPIOB, LD4_Pin, 0);
	   estado=2;
	     contador =5;
	   }
	 if(GPIO_Pin==estacionar_Pin)
		 {HAL_UART_Transmit(&huart2, "Estacionar\r\n", 14, 10);
		 	estacionando=!estacionando;
		    contador =0xFFFFFF;

		 	HAL_GPIO_EXTI_IRQHandler(estacionar_Pin);
			HAL_GPIO_WritePin(GPIOB, LD4_Pin, 1);
		 	HAL_GPIO_WritePin(GPIOA, LD3_Pin, 1);

		  }



	 //filtro para evitar los rebotes que presenta el boton

	if (GPIO_Pin == izquierda_Pin) {

		if ((HAL_GetTick() < (tiempo + 500))&&(HAL_GetTick() > (tiempo + 150))) { // if last press was in the last 300ms
			contador = 0xFFFFFF; // a long time toggling (infinite)
		} else {
			contador = 5;
		}
		tiempo = HAL_GetTick();
	} if (GPIO_Pin == derecha_Pin) {
		if ((HAL_GetTick() < (tiempo + 500))&&(HAL_GetTick() > (tiempo + 150))) { // if last press was in the last 300ms
			contador = 0xFFFFFF; // a long time toggling (infinite)
		} else {
			contador = 5;
		}
		tiempo = HAL_GetTick();

	}



	if (GPIO_Pin ==estacionar_Pin) {

				if ((HAL_GetTick() > (tiempo + 200))) { // if last press was in the last 300ms
					estacionando=!estacionando; // a long time toggling (infinite)
				} else {
					estacionando = estacionando;
				}tiempo = HAL_GetTick();
	}
}
void heartbeat(void)
{
	static uint32_t heartbeat_tick = 0;
	if (heartbeat_tick < HAL_GetTick()) {
		heartbeat_tick = HAL_GetTick() + 500;
		HAL_GPIO_TogglePin(GPIOA, LD_Pin);
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
   {
     /* USER CODE END WHILE */
 	 heartbeat();
     /* USER CODE BEGIN 3 */

 	 if (estacionando==1){
 	 	   if((HAL_GetTick()-tiempo)>tiempo_parpadeo){
 	 		HAL_GPIO_TogglePin(GPIOA, LD3_Pin);
 	 	   	HAL_GPIO_TogglePin(GPIOB, LD4_Pin);
 	 	   	tiempo=HAL_GetTick();
 	 	    contador--;
 	 	   }

 	 	    if ((estado==1||estado==2)){
 	 	   			estado=0;
 	 	   			estacionando=0;
 	 	   			HAL_GPIO_WritePin(GPIOB, LD4_Pin, 1);
 	 	   			HAL_GPIO_WritePin(GPIOA, LD3_Pin, 1);
 	 	   	}
 	 	   }





 	  if (estado==2){
 	   		if((HAL_GetTick()-tiempo)>tiempo_parpadeo){
 	   			HAL_GPIO_WritePin(GPIOA, LD3_Pin, 1);

 	   			HAL_GPIO_TogglePin(GPIOB, LD4_Pin);
 	   			tiempo=HAL_GetTick();
 	   			contador--;
 	   			if ((contador==0)){
 	   				estado=0;
 	   			 HAL_GPIO_WritePin(GPIOB, LD4_Pin, 1);

 	   			}

 	   		}
 	   		}

 	if (estado==1){
 		if((HAL_GetTick()-tiempo)>tiempo_parpadeo){
 			HAL_GPIO_WritePin(GPIOB, LD4_Pin, 1);
 			HAL_GPIO_TogglePin(GPIOA, LD3_Pin);
 			tiempo=HAL_GetTick();
 			contador--;
 			if ((contador==0)){
 				estado=0;
 				  HAL_GPIO_WritePin(GPIOA, LD3_Pin, 1);

 			}

 		 }
 	   }
   	 }
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD_Pin|LD2_Pin|LD3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : Boton_Pin */
  GPIO_InitStruct.Pin = Boton_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Boton_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : izquierda_Pin estacionar_Pin */
  GPIO_InitStruct.Pin = izquierda_Pin|estacionar_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD_Pin LD2_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD_Pin|LD2_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : derecha_Pin */
  GPIO_InitStruct.Pin = derecha_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(derecha_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD4_Pin */
  GPIO_InitStruct.Pin = LD4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD4_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
