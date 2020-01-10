/******** Define to prevent recursive inclusion*****************************/
#ifndef RE_PORT_TIMER_H
#define RE_PORT_TIMER_H

/*******************************************************************************
*Includes
*******************************************************************************/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"
#include "re_err_handler.h"

/*******************************************************************************
*Function prototypes
*******************************************************************************/
void RE_TIM3_Configure(void);
void RE_TIM3_IRQHandler(void);

#endif

/*****************************END OF FILE**************************************/


