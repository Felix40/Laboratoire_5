/*Header principale pour le laboratoire 5*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#define size 20

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "LCD.h"
#include "UART.h"
#include "tm_stm32f4_hd44780.h"
#include "tm_stm32f4_delay.h"
#include "Temps.h"
#include "LED.h"



int ptr_ecriture;
int ptr_lecture;
char buffer_commandes[size];

#endif /* __MAIN_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
