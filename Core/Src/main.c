/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "pin_dbg.h"
#include "printf_dbg.h"
#include "cmd_process.h"

volatile const char __version__[] = "G070RB";    
volatile const char __date__[] = __DATE__;
volatile const char __time__[] = __TIME__;

/**
 * @brief  Start Thread 
 * @param  None
 * @retval None
 */
void system_thread(void *arg)
{ 
  /*Инициализация аппаратной части отладки */
  hal_debug_uart_init();
  hal_debug_pin_init();
  //
  //// Информационная шапка программы
  printf("______________________________________________\r\n");
  printf("\r\n");
  printf("   %s \r\n", __version__);
  printf("   DATA: %s \r\n", __date__);
  printf("   TIME: %s \r\n", __time__);
  printf("   CPU FREQ = %.9lu Hz \r\n", SystemCoreClock);  
  printf("______________________________________________\r\n"); 
  
  //Инициализация задачи диагностического терминала 
  xTaskCreate(terminal_task, (const char*)"CmdTrmnl", configMINIMAL_STACK_SIZE * 2, NULL, TreadPrioAboveNormal, NULL);
  
  for (;;) {
    vTaskDelay(1000);   
  }
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  /* System Clock Configuration, GPIO Ports Clock Enable */
  HAL_Init();
  /* Init thread */
  xTaskCreate(system_thread, (const char*)"SysTask", configMINIMAL_STACK_SIZE * 1, NULL, TreadPrioNormal, NULL);	
  /* Start scheduler */
  vTaskStartScheduler();  
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  while (1){};
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
