/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define LED_RED_1_Pin GPIO_PIN_1
#define LED_RED_1_GPIO_Port GPIOA
#define LED_YEL_1_Pin GPIO_PIN_2
#define LED_YEL_1_GPIO_Port GPIOA
#define LED_GRN_1_Pin GPIO_PIN_3
#define LED_GRN_1_GPIO_Port GPIOA
#define LED_RED_2_Pin GPIO_PIN_4
#define LED_RED_2_GPIO_Port GPIOA
#define LED_YEL_2_Pin GPIO_PIN_5
#define LED_YEL_2_GPIO_Port GPIOA
#define LED_GRN_2_Pin GPIO_PIN_6
#define LED_GRN_2_GPIO_Port GPIOA
#define LED_SEG1_A_Pin GPIO_PIN_7
#define LED_SEG1_A_GPIO_Port GPIOA
#define LED_SEG3_B_Pin GPIO_PIN_0
#define LED_SEG3_B_GPIO_Port GPIOB
#define LED_SEG3_C_Pin GPIO_PIN_1
#define LED_SEG3_C_GPIO_Port GPIOB
#define LED_SEG3_D_Pin GPIO_PIN_2
#define LED_SEG3_D_GPIO_Port GPIOB
#define LED_SEG5_D_Pin GPIO_PIN_10
#define LED_SEG5_D_GPIO_Port GPIOB
#define BUTTON_1_Pin GPIO_PIN_11
#define BUTTON_1_GPIO_Port GPIOB
#define BUTTON_2_Pin GPIO_PIN_12
#define BUTTON_2_GPIO_Port GPIOB
#define BUTTON_3_Pin GPIO_PIN_13
#define BUTTON_3_GPIO_Port GPIOB
#define LED_SEG1_B_Pin GPIO_PIN_8
#define LED_SEG1_B_GPIO_Port GPIOA
#define LED_SEG1_C_Pin GPIO_PIN_9
#define LED_SEG1_C_GPIO_Port GPIOA
#define LED_SEG1_D_Pin GPIO_PIN_10
#define LED_SEG1_D_GPIO_Port GPIOA
#define LED_SEG2_A_Pin GPIO_PIN_11
#define LED_SEG2_A_GPIO_Port GPIOA
#define LED_SEG2_B_Pin GPIO_PIN_12
#define LED_SEG2_B_GPIO_Port GPIOA
#define LED_SEG2_C_Pin GPIO_PIN_13
#define LED_SEG2_C_GPIO_Port GPIOA
#define LED_SEG2_D_Pin GPIO_PIN_14
#define LED_SEG2_D_GPIO_Port GPIOA
#define LED_SEG3_A_Pin GPIO_PIN_15
#define LED_SEG3_A_GPIO_Port GPIOA
#define LED_SEG4_A_Pin GPIO_PIN_3
#define LED_SEG4_A_GPIO_Port GPIOB
#define LED_SEG4_B_Pin GPIO_PIN_4
#define LED_SEG4_B_GPIO_Port GPIOB
#define LED_SEG4_C_Pin GPIO_PIN_5
#define LED_SEG4_C_GPIO_Port GPIOB
#define LED_SEG4_D_Pin GPIO_PIN_6
#define LED_SEG4_D_GPIO_Port GPIOB
#define LED_SEG5_A_Pin GPIO_PIN_7
#define LED_SEG5_A_GPIO_Port GPIOB
#define LED_SEG5_B_Pin GPIO_PIN_8
#define LED_SEG5_B_GPIO_Port GPIOB
#define LED_SEG5_C_Pin GPIO_PIN_9
#define LED_SEG5_C_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
