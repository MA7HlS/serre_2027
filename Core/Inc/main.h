/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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
#define PWM_Ventilo_Pin GPIO_PIN_9
#define PWM_Ventilo_GPIO_Port GPIOB
#define T_NRST_Pin GPIO_PIN_2
#define T_NRST_GPIO_Port GPIOF
#define Bouton_Haut_Pin GPIO_PIN_0
#define Bouton_Haut_GPIO_Port GPIOA
#define Bouton_Bas_Pin GPIO_PIN_1
#define Bouton_Bas_GPIO_Port GPIOA
#define T_VCP_TX_Pin GPIO_PIN_2
#define T_VCP_TX_GPIO_Port GPIOA
#define T_VCP_RX_Pin GPIO_PIN_3
#define T_VCP_RX_GPIO_Port GPIOA
#define Bouton_Valider_Pin GPIO_PIN_4
#define Bouton_Valider_GPIO_Port GPIOA
#define Bouton_Retour_Pin GPIO_PIN_5
#define Bouton_Retour_GPIO_Port GPIOA
#define ADC_TEMP_Pin GPIO_PIN_0
#define ADC_TEMP_GPIO_Port GPIOB
#define ADC_HUM_Pin GPIO_PIN_1
#define ADC_HUM_GPIO_Port GPIOB
#define LDC_D7_Pin GPIO_PIN_8
#define LDC_D7_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_6
#define LD3_GPIO_Port GPIOC
#define T_JTMS_Pin GPIO_PIN_13
#define T_JTMS_GPIO_Port GPIOA
#define T_JTCK_Pin GPIO_PIN_14
#define T_JTCK_GPIO_Port GPIOA
#define LDC_RS_Pin GPIO_PIN_3
#define LDC_RS_GPIO_Port GPIOB
#define LDC_E_Pin GPIO_PIN_4
#define LDC_E_GPIO_Port GPIOB
#define LDC_D4_Pin GPIO_PIN_5
#define LDC_D4_GPIO_Port GPIOB
#define LDC_D5_Pin GPIO_PIN_6
#define LDC_D5_GPIO_Port GPIOB
#define LDC_D6_Pin GPIO_PIN_7
#define LDC_D6_GPIO_Port GPIOB
#define PWM_Pompe_Pin GPIO_PIN_8
#define PWM_Pompe_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
