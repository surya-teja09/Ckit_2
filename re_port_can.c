/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_port_can.h"


/*******************************************************************************
*Module Variable Definitions
*******************************************************************************/
extern uint8_t msg[6];
extern uint8_t flag;

/*******************************************************************************
*Typedefs
*******************************************************************************/
extern CAN_HandleTypeDef hcan1;
CAN_TxHeaderTypeDef TxHeader; 
CAN_RxHeaderTypeDef RxHeader;

/*******************************************************************************
*Function prototypes
*******************************************************************************/
extern void Error_Handler(void);
void RE_CAN_TxMsg(void);

/**
  * @brief CAN GPIO Initialization
  * This function configures the hardware resources for CAN1 peripheral
  * @param hcan1: CAN handle pointer
  * @retval None
  */
void HAL_CAN_MspInit(CAN_HandleTypeDef * hcan1)
{
    GPIO_InitTypeDef Can_InitConfig;
    if (hcan1 -> Instance == CAN1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /**CAN GPIO Configuration    
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX 
    */
    Can_InitConfig.Pin = GPIO_PIN_8;
    Can_InitConfig.Mode = GPIO_MODE_AF_PP;
    Can_InitConfig.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    Can_InitConfig.Alternate = GPIO_AF9_CAN1;
    Can_InitConfig.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &Can_InitConfig);

    Can_InitConfig.Pin = GPIO_PIN_9;
    Can_InitConfig.Mode = GPIO_MODE_AF_PP;
    Can_InitConfig.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    Can_InitConfig.Alternate = GPIO_AF9_CAN1;
    Can_InitConfig.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &Can_InitConfig);

        /* Enabling Nested Interrupt vector */
        HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 15, 0);
        HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 15, 0);

        HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
        HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
    }
}

/**
  * @brief Initialize CAN peripheral
    This function configures and initializes the CAN1 peripheral
  * @param None
  * @retval None
  */
void RE_CAN_Init()
{
    hcan1.Instance                  = CAN1; 
    hcan1.Init.Mode                 = CAN_MODE_NORMAL; 
    hcan1.Init.AutoBusOff           = DISABLE;  
    hcan1.Init.AutoRetransmission   = DISABLE; 
    hcan1.Init.AutoWakeUp           = DISABLE; 
    hcan1.Init.ReceiveFifoLocked    = DISABLE; 
    hcan1.Init.TimeTriggeredMode    = DISABLE; 
    hcan1.Init.TransmitFifoPriority = DISABLE; 

    hcan1.Init.Prescaler            = 1; 
    hcan1.Init.SyncJumpWidth        = CAN_SJW_1TQ;  
    hcan1.Init.TimeSeg1             = CAN_BS1_13TQ; 
    hcan1.Init.TimeSeg2             = CAN_BS2_2TQ;  

    if (HAL_CAN_Init(&hcan1) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
  * @brief CAN1_Filter_Config
    This function configures CAN1 filter banks
  * @param None
  * @retval None
  */
void RE_CAN_Filter_Config(void)
{
    CAN_FilterTypeDef can1_filter_init; 

    can1_filter_init.FilterActivation     = ENABLE; 
    can1_filter_init.FilterBank           = 0; 
    can1_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0; 
/**
  *@TODO: Add filter configurations if needed.
  */
    can1_filter_init.FilterIdHigh         = 0x0000; 
    can1_filter_init.FilterIdLow          = 0x0000; 
    can1_filter_init.FilterMaskIdHigh     = 0X0000; 
    can1_filter_init.FilterMaskIdLow      = 0x0000;  
    can1_filter_init.FilterMode           = CAN_FILTERMODE_IDMASK;  
    can1_filter_init.FilterScale          = CAN_FILTERSCALE_32BIT; 

    if (HAL_CAN_ConfigFilter(&hcan1,&can1_filter_init) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief Tx CAN1 message
    This function transmits CAN1 messages
  * @param None
  * @retval None
  */
void RE_CAN_TxMsg(void)
{
    uint32_t TxMailbox;

    TxHeader.DLC       = 6;
    TxHeader.ExtId     = 0x5DC;
    TxHeader.IDE       = CAN_ID_EXT;
    TxHeader.RTR       = CAN_RTR_DATA;

    if (HAL_CAN_AddTxMessage(&hcan1,&TxHeader,msg,&TxMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}



/**
  * @brief  CAN  Rx Fifo message pending callback (ISR)
  * This function handles the CAN message from Kit MCU
  * @param  hcan : CAN handle structure
  * @retval None  
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t rcvd_msg[5];

    if (HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&RxHeader,rcvd_msg) != HAL_OK)
    {
        Error_Handler();
    }
/*if received message to open the latch*/
    if (RxHeader.ExtId == 0x3ED && RxHeader.RTR == 0)
    {
        if (rcvd_msg[0] == 1)
        {
            flag = 1;
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        }
    }
}

/*****************************END OF FILE**************************************/
