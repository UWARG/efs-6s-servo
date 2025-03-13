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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ST_CH2_Pin GPIO_PIN_14
#define ST_CH2_GPIO_Port GPIOC
#define ST_CH1_Pin GPIO_PIN_15
#define ST_CH1_GPIO_Port GPIOC
#define NEOPIXEL_PWM_Pin GPIO_PIN_1
#define NEOPIXEL_PWM_GPIO_Port GPIOA
#define PWM_4_Pin GPIO_PIN_2
#define PWM_4_GPIO_Port GPIOA
#define ST_CH3_Pin GPIO_PIN_3
#define ST_CH3_GPIO_Port GPIOA
#define VSENSE_6V_Pin GPIO_PIN_5
#define VSENSE_6V_GPIO_Port GPIOA
#define VSENSE_BAT_Pin GPIO_PIN_6
#define VSENSE_BAT_GPIO_Port GPIOA
#define VSENSE_3V3_Pin GPIO_PIN_7
#define VSENSE_3V3_GPIO_Port GPIOA
#define VSENSE_5V_Pin GPIO_PIN_0
#define VSENSE_5V_GPIO_Port GPIOB
#define CSENSE_BAT_Pin GPIO_PIN_1
#define CSENSE_BAT_GPIO_Port GPIOB
#define PWM_1_Pin GPIO_PIN_8
#define PWM_1_GPIO_Port GPIOA
#define PWM_2_Pin GPIO_PIN_9
#define PWM_2_GPIO_Port GPIOA
#define PWM_3_Pin GPIO_PIN_10
#define PWM_3_GPIO_Port GPIOA
#define ST_CH4_Pin GPIO_PIN_15
#define ST_CH4_GPIO_Port GPIOA
#define IN4_Pin GPIO_PIN_4
#define IN4_GPIO_Port GPIOB
#define IN3_Pin GPIO_PIN_5
#define IN3_GPIO_Port GPIOB
#define IN2_Pin GPIO_PIN_6
#define IN2_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_7
#define IN1_GPIO_Port GPIOB
#define DIAG_EN_Pin GPIO_PIN_3
#define DIAG_EN_GPIO_Port GPIOH

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
