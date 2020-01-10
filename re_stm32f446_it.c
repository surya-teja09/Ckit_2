/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_stm32f446_it.h"

/*******************************************************************************
*Typedefs
*******************************************************************************/
extern CAN_HandleTypeDef hcan1;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim3;

/**
  * @brief  CAN Rx FIFO message pending IRQ Handler
  * @param  None
  * @retval None  
  */
void CAN1_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan1);
}

/**
  * @brief  CAN SCE interrupt handler
  * @param  None
  * @retval None  
  */
void CAN1_SCE_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan1);
}


/**
  * @brief  SPI IRQ Handler
  * @param  None
  * @retval None  
  */
void SPI_IRQHandler(void)
{
    HAL_SPI_IRQHandler(&hspi1);
}

/**
  * @brief  TIMER IRQ interrupt handler
  * @param  None
  * @retval None  
  */
void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim3);
}


/**
  * @brief  SysTick IRQ Handler
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

/**
  * @brief  GPIO IRQ Handler for Pin0
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
  * @brief  GPIO IRQ Handler for Pin1
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

/**
  * @brief  GPIO IRQ Handler for Pin2
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

/**
  * @brief  GPIO IRQ Handler for Pin3
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

/**
  * @brief  GPIO IRQ Handler for Pin7
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
}

/*****************************END OF FILE**************************************/
