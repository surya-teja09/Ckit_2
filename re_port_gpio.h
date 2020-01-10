/******** Define to prevent recursive inclusion*****************************/
#ifndef RE_PORT_GPIO_H
#define RE_PORT_GPIO_H

/*******************************************************************************
*Includes
*******************************************************************************/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "re_err_handler.h"

/*******************************************************************************
*Function prototypes
*******************************************************************************/
void RE_GPIO_config_pins(void);
int  RE_GEAR_MODE(int,int);
int  RE_GEAR_DIRECTION(int,int);
int  RE_distance_covered(void);
int  RE_speed(void);
void RE_HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void RE_EXTI0_IRQHandler(void);
void RE_EXTI1_IRQHandler(void);
void RE_EXTI2_IRQHandler(void);
void RE_EXTI3_IRQHandler(void);
void RE_EXTI9_5_IRQHandler(void);
#endif

/*****************************END OF FILE**************************************/


