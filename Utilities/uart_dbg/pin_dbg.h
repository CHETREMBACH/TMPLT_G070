/**
  ******************************************************************************
  * @file    pin_dbg.h
  * @version V1.0.0
  * @date    07-09-2020
  * @brief   Инициализация драйвера GPIO для отладки
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2020 OneTiOne </center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIN_DBG_H
#define __PIN_DBG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"	
	
/**
  * @brief  функция - пауза для тестирования
  * @param  uint32_t - size_delay размер паузы
  * @retval none
  */
void dl_tst(uint32_t size_delay);	
	
#if  (DBG_PIN_ENABLE == 1)

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

#define T1_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()              	
#define T1_PIN            GPIO_PIN_8
#define T1_PORT           GPIOC	
#define T1_HI             T1_PORT->BSRR = T1_PIN
#define T1_LO             T1_PORT->BRR = T1_PIN

#define T2_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()            	
#define T2_PIN            GPIO_PIN_9
#define T2_PORT           GPIOC	
#define T2_HI             T2_PORT->BSRR = T2_PIN
#define T2_LO             T2_PORT->BRR = T2_PIN

#define T3_CLK_ENABLE()   __HAL_RCC_GPIOD_CLK_ENABLE()           	
#define T3_PIN            GPIO_PIN_10
#define T3_PORT           GPIOC	
#define T3_HI             T3_PORT->BSRR = T3_PIN
#define T3_LO             T3_PORT->BRR = T3_PIN
	
#define T4_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()        	
#define T4_PIN            GPIO_PIN_11
#define T4_PORT           GPIOC	
#define T4_HI             T4_PORT->BSRR = T4_PIN
#define T4_LO             T4_PORT->BRR = T4_PIN

#define T5_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()    	
#define T5_PIN            GPIO_PIN_12
#define T5_PORT           GPIOC	
#define T5_HI             T5_PORT->BSRR = T5_PIN
#define T5_LO             T5_PORT->BRR = T5_PIN

#define T6_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()      	
#define T6_PIN            GPIO_PIN_13
#define T6_PORT           GPIOC	
#define T6_HI             T6_PORT->BSRR = T6_PIN
#define T6_LO             T6_PORT->BRR = T6_PIN

#define T7_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()           	
#define T7_PIN            GPIO_PIN_14
#define T7_PORT           GPIOC	
#define T7_HI             T7_PORT->BSRR = T7_PIN
#define T7_LO             T7_PORT->BRR = T7_PIN
	
#define T8_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()           	
#define T8_PIN            GPIO_PIN_15
#define T8_PORT           GPIOC	
#define T8_HI             T8_PORT->BSRR = T8_PIN
#define T8_LO             T8_PORT->BRR = T8_PIN
	
/**
  * @brief  Инициализация GPIO для отладки.
  * @param  None
  * @retval None
  */
void hal_debug_pin_init(void);

#endif /*  (DBG_PIN_ENABLE == 1) */

#ifdef __cplusplus
}
#endif

#endif /* __PIN_DBG_H */

/******************* (C) COPYRIGHT 2020 OneTiOne  *****END OF FILE****/
