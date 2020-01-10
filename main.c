/*******************************************************************************
*Includes
*******************************************************************************/
#include "main.h"

/*******************************************************************************
*Typedefs
*******************************************************************************/

CAN_HandleTypeDef hcan1;
GPIO_InitTypeDef PinConfig;
TIM_HandleTypeDef htim3;
SPI_HandleTypeDef hspi1;

/*******************************************************************************
*Module Variable Definitions
*******************************************************************************/
int GearMode_status1,GearMode_status2,GearDir_status3,GearDir_status4;
extern volatile uint8_t latch_stat;
uint8_t msg[6];
unsigned long int RpmCnt;
int kmph;
double odo;
float low_gear_ratio = 13.9;
float high_gear_ratio = 7.25;
float gear_ratio;
uint8_t flag = 0;


/**
  * @brief  The application entry point.
  * @retval int
  */
int main()
{
    HAL_Init();

    RE_GPIO_config_pins();

    RE_CAN_Init();

    RE_CAN_Filter_Config();

    HAL_CAN_Start(&hcan1);

    RE_SPI_Init();

    if (HAL_CAN_ActivateNotification(&hcan1,CAN_IT_TX_MAILBOX_EMPTY |\
                                         CAN_IT_RX_FIFO0_MSG_PENDING |\
                                         CAN_IT_BUSOFF) != HAL_OK)
    {
        Error_Handler();
    }

    RE_TIM3_Configure();
    
    SystemClock_Config();

    if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    while(1)
    {
        GearMode_status1    = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0);
        GearMode_status2    = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1);
        GearDir_status3     = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2);
        GearDir_status4     = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3);
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage 
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType        = RCC_OSCILLATORTYPE_HSI |\
                                               RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState              = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState              = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue   = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState          = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_ClkInitStruct.ClockType             = RCC_CLOCKTYPE_HCLK |\
                                               RCC_CLOCKTYPE_SYSCLK |\
                                               RCC_CLOCKTYPE_PCLK1 |\
                                               RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource          = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider         = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider        = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider        = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }

  
    PeriphClkInitStruct.PeriphClockSelection    = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection       = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}


/*****************************END OF FILE**************************************/

