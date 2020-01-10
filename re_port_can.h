/******** Define to prevent recursive inclusion*****************************/
#ifndef RE_PORT_CAN_H
#define RE_PORT_CAN_H

/*******************************************************************************
*Includes
*******************************************************************************/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_can.h"
#include "re_err_handler.h"

/*******************************************************************************
*Function prototypes
*******************************************************************************/
void RE_CAN_Init(void);
void RE_CAN_Filter_Config(void);
void RE_CAN1_SCE_IRQHandler(void);
void RE_CAN1_RX0_IRQHandler(void);

#endif

/*****************************END OF FILE**************************************/


