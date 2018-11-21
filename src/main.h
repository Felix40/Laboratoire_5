/*Header principale pour le laboratoire 5*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "LCD.h"
#include "UART.h"

GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;
static  __IO uint32_t TimingGlobal = 1000;
static  __IO uint32_t  temps_ecoule = 0; /*variable globale contenant le temps ecoule depuis le debut*/
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void TimingGlobal_Decrement(void);

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/