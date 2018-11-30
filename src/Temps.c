
#include "Temps.h"

void Convertir_str(char* buffer, unsigned int temps){
	sprintf(buffer,"%d",temps);
}

void Decremente_Global(void){
	if(TimingGlobal == 0){
		temps_ecoule++; /*si une seconde ecoule en interruption, alors une seconde ajoutee*/
	    TimingGlobal = 1000;
	}                        /*on remet le TimingGlobal a 1000 pour compter une nouvelle seconde*/

     else{
		TimingGlobal--;       /*Si une seconde ne s'est pas ecoulee, alors un decremente*/
     }
}


void TM_DELAY_1msHandler(void){
    Decremente_Global();
}

void BoucleDAttente(short nombre_microseconde_DAttente){

	int time_wait = nombre_microseconde_DAttente;
	while(time_wait > time_counter);
	time_counter = 0; //reset
}

void TIM2_INIT(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 100 - 1; // 1 MHz down to 10 KHz (0.1 us)
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void){
	/*gpio monitoring*/
	time_counter++;
}
