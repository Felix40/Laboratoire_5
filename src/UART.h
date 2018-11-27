/*Header principale pour le laboratoire 5*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "main.h"


USART_InitTypeDef UART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStruct;


int curseur;


void INIT_UART(void);
void Traducteur_Commandes(char, char,char);
void ajout_data_buffer(char*,char);
void lecture_data_buffer(char* buffer);


#endif /* __UART_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
