/*******************************************************************************
*Includes
*******************************************************************************/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "re_latch.h"

/*******************************************************************************
*Module Priavte Variable Definitions
*******************************************************************************/
volatile uint8_t latch_stat;

/*******************************************************************************
*Module Variable Definitions
*******************************************************************************/
extern uint8_t msg[6];

/*******************************************************************************
*Function prototypes
*******************************************************************************/


/**
  * @brief  read status of the latch
  * @param  None
  * @retval None
  */
void RE_latch_status()
{
    latch_stat=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
    if(latch_stat == 1)
     msg[5] = 0;                 //latch is closed
    else if(latch_stat == 0)
     msg[5] = 2;                //latch is open
    else
        __NOP();
}

/**
  * @brief  closes the latch
  * @param  None
  * @retval None
  */
void RE_latch_close()
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
}

/*****************************END OF FILE**************************************/


