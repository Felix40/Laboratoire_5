/*Header principale pour le laboratoire 5*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "main.h"


USART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;


void INIT_UART(void);
void Traducteur_Commandes(unsigned int, unsigned int);


#endif /* __UART_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
