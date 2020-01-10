/******** Define to prevent recursive inclusion*****************************/
#ifndef RE_SPEED_GEAR_ODO_H
#define RE_SPEED_GEAR_ODO_H

/*******************************************************************************
*Includes
*******************************************************************************/
#include "re_port_gpio.h"
#include "re_err_handler.h"

/*******************************************************************************
*Module Variable Definitions
*******************************************************************************/
extern int GearMode_status1,GearMode_status2,GearDir_status3,GearDir_status4;
extern uint8_t latch_stat;
extern uint8_t msg[6];
extern unsigned long int RpmCnt;
extern int kmph;
extern double odo;
extern float low_gear_ratio;
extern float high_gear_ratio;
extern float gear_ratio;
extern uint8_t flag;

#endif

/*****************************END OF FILE**************************************/
