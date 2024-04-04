/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

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
#define Boton_Pin GPIO_PIN_13
#define Boton_GPIO_Port GPIOC
#define izquierda_Pin GPIO_PIN_1
#define izquierda_GPIO_Port GPIOA
#define izquierda_EXTI_IRQn EXTI1_IRQn
#define estacionar_Pin GPIO_PIN_4
#define estacionar_GPIO_Port GPIOA
#define estacionar_EXTI_IRQn EXTI4_IRQn
#define LD_Pin GPIO_PIN_5
#define LD_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_6
#define LD2_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_7
#define LD3_GPIO_Port GPIOA
#define derecha_Pin GPIO_PIN_0
#define derecha_GPIO_Port GPIOB
#define derecha_EXTI_IRQn EXTI0_IRQn
#define LD4_Pin GPIO_PIN_6
#define LD4_GPIO_Port GPIOB

#define CONTADOR 5

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
