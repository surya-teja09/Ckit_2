/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_speed_gear_odo.h"

/**
  * @brief  GPIO callback (ISR)
  * This function handles the GPIO callback on interrupts
  * @param  GPIO_Pin : GPIO pin number
  * @retval None  
  */
void RE_HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_7)
        RpmCnt++;

    #if 0
    else if (GPIO_Pin == GPIO_PIN_0)
    {
        s1 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0); 
        s1 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0); 
    }

    else if (GPIO_Pin == GPIO_PIN_1) 
    {
        s2 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1);
        s2 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1);
    }

    else if (GPIO_Pin == GPIO_PIN_2) 
    {
        s3 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2);
        s3 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2);
    }

    else if (GPIO_Pin == GPIO_PIN_3) 
    {
        s4 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3);
        s4 = HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3);
    }	
    #endif
    else
        __NOP();
}

/**
  * @brief  Gear Mode
  * This function transmits gear mode through CAN 
  * @param  int a,int b : status of gear mode
  * @retval Gear Mode  
  */
int RE_GEAR_MODE(int a,int b)
{
    if (a==0 && b==1)    //gear low mode
    {
        gear_ratio = low_gear_ratio;
        return msg[1] = 1; 
    }
    else if (a==1 && b==0) //gear auto
    {
        gear_ratio = high_gear_ratio;
        return msg[1] = 2;
    }
    else if (a==1 && b==1) //gear high 
    {
        gear_ratio = high_gear_ratio;
        return msg[1] = 3;
    }
    else 
        return msg[1] = 0;
}

/**
  * @brief  Gear Direction
  * This function transmits gear Direction through CAN 
  * @param  int a,int b : status of gear direction
  * @retval Gear Direction  
  */
int RE_GEAR_DIRECTION(int a,int b)
{
    if (a==0 && b==1)   //gear neutral`
        return msg[2] = 1; 
    else if (a==1 && b==0) //gear reverse
        return msg[2] = 2;
    else if (a==1 && b==1) //gear drive 
        return msg[2] = 3;
    else 
        return msg[2] = 0;
}
/**
  * @brief  Speed
  * This function calculates speed of motor and tranmsits it through CAN
  * @param  none
  * @retval Speed of motor
  */
int RE_speed(void)
{
kmph = RpmCnt*15*50/653/gear_ratio*4;
return msg[3] = kmph;
}

/**
  * @brief  Distance Covered
  * This function calculates distance covered by motor and tranmsits through CAN
  * @param  none
  * @retval Distance travelled 
  */
int RE_distance_covered(void)
{
odo += (double) kmph/3600/4;
if (odo >= 1) 
{
    msg[4] = (int) odo;
    odo = 0;
}
else 
{
    msg[4] = 0;
}
return msg[4];
}

/*****************************END OF FILE**************************************/

