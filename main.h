/******** Define to prevent recursive inclusion*****************************/
#ifndef MAIN_H
#define MAIN_H

/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_port_can.h"
#include "re_port_spi.h"
#include "re_port_timer.h"
#include "re_port_gpio.h"
#include "re_stm32f446_it.h"
#include "re_err_handler.h"


/*******************************************************************************
*Function prototypes
*******************************************************************************/
extern void SystemClock_Config(void);


#endif

/*****************************END OF FILE**************************************/
