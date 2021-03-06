/*
 * Temps.h
 *
 *  Created on: 26 nov. 2018
 *      Author: Utilisateur
 */

#ifndef __TEMPS_H
#define __TEMPS_H

#include "main.h"
#include <string.h>
#include <stdio.h>

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStruct;

__IO uint32_t temps_ecoule; /*initalise le temps*/
__IO uint32_t TimingGlobal; /*initialise le timing global*/
unsigned int time_counter;

void Convertir_str(char*, unsigned int);
void Decremente_Global(void);
void TM_DELAY_1msHandler(void);
void BoucleDAttente(double);
void TIM2_INIT(void);


#endif /* TEMPS_H_ */
