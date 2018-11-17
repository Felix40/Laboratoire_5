/*Header principale pour le laboratoire 5*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "LCD.h"

GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
