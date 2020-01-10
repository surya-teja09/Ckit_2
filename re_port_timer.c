/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_port_timer.h"
#include "re_port_can.h"

/*******************************************************************************
*Typedefs
*******************************************************************************/
extern TIM_HandleTypeDef htim3;

/*******************************************************************************
*Module Priavte Variable Definitions
*******************************************************************************/
uint8_t time = 0;

/*******************************************************************************
*Module Variable Definitions
*******************************************************************************/
extern int GearMode_status1,GearMode_status2,GearDir_status3,GearDir_status4;
extern unsigned long int RpmCnt;
extern uint8_t flag;
extern uint8_t msg[6];

/*******************************************************************************
*Function prototypes
*******************************************************************************/
extern void  RE_CAN_TxMsg(void);
extern int   RE_GEAR_MODE(int,int);
extern int   RE_GEAR_DIRECTION(int,int);
extern int   RE_distance_covered(void);
extern int   RE_speed(void);
extern void  RE_config_pins(void);
extern int   RE_read_temp(void);
extern void  RE_latch_status(void);
extern void  RE_latch_close(void);



/**
  * @brief Timer Initialization
  * This function configures the hardware resources for Timer peripheral
  * @param htim3: TIMER handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef * htim_base)
{
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
    if (htim_base -> Instance == TIM3)
    {
        /* Enabling Nested Interrupt vector */
        HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
}

/**
  * @brief Configure TIMER peripheral
    This function configures the TIMER peripheral
  * @param None
  * @retval None
  */
void RE_TIM3_Configure(void)
{
    /*enabling timer interrupt for every 250ms*/
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
    htim3.Instance                           = TIM3;
    htim3.Init.Prescaler                     = 499;
    htim3.Init.CounterMode                   = TIM_COUNTERMODE_UP;
    htim3.Init.Period                        = 3999;
    htim3.Init.ClockDivision                 = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload             = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }

    sClockSourceConfig.ClockSource           = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }

    sMasterConfig.MasterOutputTrigger        = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode            = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief  timer callback (ISR)
  * This function handles the timer interrupt 
  * @param  htim3 : TIMER handle structure
  * @retval None  
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
    if (htim -> Instance == TIM3)
    {
        HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
        RE_GEAR_MODE(GearMode_status1,GearMode_status2);
        RE_GEAR_DIRECTION(GearDir_status3,GearDir_status4);
        RE_speed();
        RpmCnt=0;
        RE_distance_covered();
        RE_read_temp();
        RE_latch_status();
        if (flag == 1)
        {
            time ++;
        }
        if (time == 4)
        {
            RE_latch_close();
            flag = 0;
            time = 0;
        }
        RE_CAN_TxMsg();
        HAL_NVIC_EnableIRQ(TIM3_IRQn);
    }
}

/*****************************END OF FILE**************************************/

