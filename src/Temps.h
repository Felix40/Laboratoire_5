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

__IO uint32_t temps_ecoule; /*initalise le temps*/
__IO uint32_t TimingGlobal; /*initialise le timing global*/

void Convertir_str(char*, unsigned int);
void Decremente_Global(void);


#endif /* TEMPS_H_ */
