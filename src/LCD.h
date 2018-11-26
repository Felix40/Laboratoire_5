
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4_discovery.h"
#include "main.h"
#include <stdbool.h>

GPIO_InitTypeDef GPIO_InitStructure;


void init_LCD_Pins(void);
void Activation_LCD(void);
/*va avoir besoin d'un fonction desactivation lcd ici*/
void Write_LCD(int);
void Ecriture_temps(unsigned int);

/*les fonction ici ne seront pas utile pour le laboratoire 5*/
void Read_Keyboard(void);
void Ecriture_SMI(void);
void init_Keyboard_Pins(void);



#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
