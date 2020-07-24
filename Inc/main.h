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
#define NUM_SAMPLES 256
#define PI ( 3.1415926535 )
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MODE1_Pin GPIO_PIN_13
#define MODE1_GPIO_Port GPIOC
#define MODE2_Pin GPIO_PIN_0
#define MODE2_GPIO_Port GPIOH
#define MODE3_Pin GPIO_PIN_1
#define MODE3_GPIO_Port GPIOH
#define MODE4_Pin GPIO_PIN_0
#define MODE4_GPIO_Port GPIOA
#define MODE5_Pin GPIO_PIN_1
#define MODE5_GPIO_Port GPIOA
#define BRIGHT_POT_Pin GPIO_PIN_2
#define BRIGHT_POT_GPIO_Port GPIOA
#define AMP1_MIC_DC_Pin GPIO_PIN_3
#define AMP1_MIC_DC_GPIO_Port GPIOA
#define AMP2_LINE_DC_Pin GPIO_PIN_4
#define AMP2_LINE_DC_GPIO_Port GPIOA
#define AMP1_MIC_OUT_Pin GPIO_PIN_5
#define AMP1_MIC_OUT_GPIO_Port GPIOA
#define AMP2_LINE_OUT_Pin GPIO_PIN_6
#define AMP2_LINE_OUT_GPIO_Port GPIOA
#define INPUT_SEL_Pin GPIO_PIN_7
#define INPUT_SEL_GPIO_Port GPIOA
#define UC_LED1_Pin GPIO_PIN_0
#define UC_LED1_GPIO_Port GPIOB
#define UC_LED3_Pin GPIO_PIN_1
#define UC_LED3_GPIO_Port GPIOB
#define UC_LED5_Pin GPIO_PIN_2
#define UC_LED5_GPIO_Port GPIOB
#define UC_LED7_Pin GPIO_PIN_10
#define UC_LED7_GPIO_Port GPIOB
#define UC_LED9_Pin GPIO_PIN_12
#define UC_LED9_GPIO_Port GPIOB
#define UC_LED11_Pin GPIO_PIN_13
#define UC_LED11_GPIO_Port GPIOB
#define UC_LED13_Pin GPIO_PIN_14
#define UC_LED13_GPIO_Port GPIOB
#define UC_LED15_Pin GPIO_PIN_15
#define UC_LED15_GPIO_Port GPIOB
#define UC_LED17_Pin GPIO_PIN_3
#define UC_LED17_GPIO_Port GPIOB
#define UC_LED19_Pin GPIO_PIN_4
#define UC_LED19_GPIO_Port GPIOB
#define UC_LED21_Pin GPIO_PIN_5
#define UC_LED21_GPIO_Port GPIOB
#define UC_LED23_Pin GPIO_PIN_6
#define UC_LED23_GPIO_Port GPIOB
#define UC_LED25_Pin GPIO_PIN_7
#define UC_LED25_GPIO_Port GPIOB
#define UC_LED27_Pin GPIO_PIN_8
#define UC_LED27_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
