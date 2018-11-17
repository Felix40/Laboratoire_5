
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "main.h"


SPI_InitTypeDef SPI_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;


/* Private function prototypes -----------------------------------------------*/
void Init_SPI(void);
char LireMemoireEEPROM(unsigned int, unsigned int, unsigned char *);
char EcrireMemoireEEPROM(unsigned int, unsigned int, unsigned char *);

/*Homemade fonctions send/receive*/
uint8_t SPISend(uint8_t data);

#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
