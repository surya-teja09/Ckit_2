/******** Define to prevent recursive inclusion*****************************/
#ifndef RE_PORT_SPI_H
#define RE_PORT_SPI_H

/*******************************************************************************
*Includes
*******************************************************************************/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"
#include "re_err_handler.h"

/*******************************************************************************
*Function prototypes
*******************************************************************************/
void RE_SPI_Init(void);
void RE_SPI_IRQHandler(void);

#endif

/*****************************END OF FILE**************************************/


