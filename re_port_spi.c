/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_port_spi.h"

/*******************************************************************************
*Typedefs
*******************************************************************************/
extern SPI_HandleTypeDef hspi1;

/**
  * @brief SPI GPIO Initialization
  * This function configures the hardware resources for SPI peripheral
  * @param hspi1: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi1)
{
    GPIO_InitTypeDef Spi_InitConfig;
    if (hspi1 -> Instance == SPI1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**CAN GPIO Configuration    
        PB3     ------> SCK
        PB4     ------> MISO
        PB5     ------> MOSI
        */
        Spi_InitConfig.Pin          = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
        Spi_InitConfig.Mode         = GPIO_MODE_AF_PP;
        Spi_InitConfig.Speed        = GPIO_SPEED_FAST;
        Spi_InitConfig.Alternate    = GPIO_AF5_SPI1;
        Spi_InitConfig.Pull         = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &Spi_InitConfig);

        /* Enabling Nested Interrupt vector */
        HAL_NVIC_SetPriority(SPI1_IRQn,15,0);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
}

/**
  * @brief Initialize SPI peripheral
  * This function configures and initializes the SPI peripheral
  * @param None
  * @retval None
  */

void RE_SPI_Init(void)
{

    hspi1.Instance                        = SPI1;
    hspi1.Init.Mode                       = SPI_MODE_MASTER;
    hspi1.Init.Direction                  = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize                   = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity                = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase                   = SPI_PHASE_1EDGE;
    hspi1.Init.NSS                        = SPI_NSS_HARD_OUTPUT;
    hspi1.Init.BaudRatePrescaler          = SPI_BAUDRATEPRESCALER_16;
    hspi1.Init.FirstBit                   = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode                     = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation             = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial              = 10;

    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }

}


/*****************************END OF FILE**************************************/


