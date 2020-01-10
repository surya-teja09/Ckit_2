/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_temp_sensor.h"

/*******************************************************************************
*Module Variable Definitions
*******************************************************************************/
uint8_t data[2];
uint16_t temp,temp1;
float celsius;
extern uint8_t msg[6];

/*******************************************************************************
*Typedefs
*******************************************************************************/

extern SPI_HandleTypeDef hspi1;

/*******************************************************************************
*Function prototypes
*******************************************************************************/
int RE_read_temp(void);
extern void Error_Handler(void);

/**
  * @brief  read temperature for the temperature sensor
  * @param  None
  * @retval tempertaure of motor  
  */
int RE_read_temp(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);
    if (HAL_SPI_Receive(&hspi1,data,2,10) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);
    temp = (data[0] << 8) | (data[1]);
    if (temp & 0x4)
        while(1);
    temp1       = (temp >> 3);
    celsius     = (temp*0.25);
    celsius     = celsius/10;
    msg[0]      = celsius;
    return msg[0];
}

/*****************************END OF FILE**************************************/


