/**
  ******************************************************************************
  * @file    hooks.c 
  * @author  Trembach D.N.
  * @version V1.0.0
  * @date    22-11-2015
  * @brief   Файл вспомогательных функций портирования FreeRTOS.
  *
  *
  ******************************************************************************
  * @attention
  *
  *
  * <h2><center>&copy; COPYRIGHT 2015 DEX</center></h2>
  ******************************************************************************
  */

#include <stdio.h>
#include "main.h"
#include "hooks.h"
#include "stm32g0xx_hal_tim_ex.h"
#include "pin_dbg.h"

static volatile unsigned int stackOverflow;
static volatile unsigned int mallocFailed;

/* Указать размешение heap */
#if ( configAPPLICATION_ALLOCATED_HEAP == 1 )
/* Allocate the memory for the heap. */
uint8_t __attribute__((section("RTOS_RAM"))) ucHeap[configTOTAL_HEAP_SIZE];	
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/**
  * @brief  Функция вызывается при переполнении стека FreeRTOS, 
  * @param  TaskHandle_t xTask - хэндл задачи
  * @param  signed portCHAR *pcTaskName  - имя текущей задачи
  * @retval None
  */
void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   signed portCHAR *pcTaskName)
{
	stackOverflow++;
	printf("StackOverflowHook: %s\n", pcTaskName);
        while(1);
}

/**
  * @brief  Функция вызывается при отсутствии памяти в куче FreeRTOS, 
  *    
  * @param  None
  * @retval None
  */
void vApplicationMallocFailedHook(void)
{
	mallocFailed++;
	printf("MallocFailedHook: %d\n", xPortGetFreeHeapSize());
        while(1);
}

/* TIM handle declaration */
TIM_HandleTypeDef    TimHandle;

/**
  * @brief  Функция настройки и запуска таймера, 
  *         который используется для подсчета времени работы задач FreeRTOS 
  *         
  *         Время тика таймера должено быть, по крайней мере в 10 раз меньше
  *         частоты тика FreeRTOS
  *    
  * @param  None
  * @retval None
  */
void vConfigureTimerForRunTimeStats(void)
{
  /* Enable TIM2 clock */
  __HAL_RCC_TIM14_CLK_ENABLE();  
        
  /* Set TIMx instance */
  TimHandle.Instance = TIM14;

  TimHandle.Init.Period            = 0xFFFF;
  TimHandle.Init.Prescaler         = 6400 - 1;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;

  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }        
        
  /* Start Channel1 */
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }        
        
}

unsigned long hi_cntr = 0;
unsigned long old_cnt = 0;
unsigned long new_cnt = 0;

/**
  * @brief  Функция возращает значения счетчика таймера, 
  *         который используется для подсчета времени работы задач FreeRTOS 
  *         
  * @param  None
  * @retval unsigned long значение счетчика таймера
  */
unsigned long ulGetRuntimeCounterValue(void)
{ 
  new_cnt = (unsigned long)(TIM14->CNT);
  if (old_cnt > new_cnt) 
  {
    hi_cntr += 0x00010000;
    T1_HI;
  }  
  else
  {
    T1_LO;
  } 
  old_cnt = new_cnt;
  return hi_cntr + new_cnt;		
}


/**************    COPYRIGHT 2015 DEX Tech. Co., Ltd.   *****END OF FILE*******/