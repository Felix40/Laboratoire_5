
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
	GPIO_SetBits(GPIOA, GPIO_Pin_6); //active le monitoring
    Decremente_Global();
    GPIO_ResetBits(GPIOA, GPIO_Pin_6); //active le monitoring
}

void BoucleDAttente(double nombre_microseconde_DAttente){

	double counter = 0;
	nombre_microseconde_DAttente = nombre_microseconde_DAttente * 2.5;

	for (int i = 0; i <= nombre_microseconde_DAttente; i++) {
		counter++;
	}
}

void TIM2_INIT(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 84000 - 1; // 1ms
	TIM_TimeBaseStructure.TIM_Prescaler =  0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

}

void TIM2_IRQHandler(void){
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	BoucleDAttente(300);
    }
}



