/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_port_gpio.h"

/*******************************************************************************
*Typedefs
*******************************************************************************/
extern GPIO_InitTypeDef PinConfig;

/**
  * @brief Initialize GPIO peripheral
  * This function configures and initializes the GPIO peripheral
  * @param None
  * @retval None
  */
void RE_GPIO_config_pins(void)
{
    /* Peripheral clock enable */
    __HAL_RCC_GPIOC_CLK_ENABLE(); 
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /**Configuring GPIO */
    PinConfig.Pin      = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    PinConfig.Mode     = GPIO_MODE_INPUT;
    PinConfig.Speed    = GPIO_SPEED_FAST;
    PinConfig.Pull     = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC,&PinConfig);

    PinConfig.Pin      = GPIO_PIN_7;
    PinConfig.Mode     = GPIO_MODE_IT_RISING;
    PinConfig.Speed    = GPIO_SPEED_FAST;
    PinConfig.Pull     = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB,&PinConfig);
    
    PinConfig.Pin      = GPIO_PIN_5;
    PinConfig.Mode     = GPIO_MODE_OUTPUT_PP; 
    HAL_GPIO_Init(GPIOA,&PinConfig);

    PinConfig.Pin      = GPIO_PIN_10;
    PinConfig.Mode     = GPIO_MODE_OUTPUT_PP; 
    HAL_GPIO_Init(GPIOB,&PinConfig);

    PinConfig.Pin      = GPIO_PIN_12;
    PinConfig.Mode     = GPIO_MODE_INPUT;
    PinConfig.Speed    = GPIO_SPEED_FAST;
    PinConfig.Pull     = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA,&PinConfig);

    PinConfig.Pin      =  GPIO_PIN_11;
    PinConfig.Mode     = GPIO_MODE_OUTPUT_PP;
    PinConfig.Speed    = GPIO_SPEED_FAST;
    PinConfig.Pull     = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA,&PinConfig);

    /*Enabling Nested Interrupt vector for GPIO's */
    HAL_NVIC_SetPriority(EXTI0_IRQn,0,1);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI1_IRQn,0,1);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);

    HAL_NVIC_SetPriority(EXTI2_IRQn,0,1);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn,0,1);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI9_5_IRQn,0,1);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* Enabling Nested Interrupt vector for SysTick timer */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()); 
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn,0,0);
}


/*****************************END OF FILE**************************************/
