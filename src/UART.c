/*Fichier principal du laboratoire 5*/

/* Includes ------------------------------------------------------------------*/
#include "UART.h"

/*Routine d'initialisation du module UART du microcontroleur*/
void INIT_UART(void){

    /*initalisation des proprietes du module*/
	UART_InitStructure.USART_BaudRate = 19200;
	UART_InitStructure.USART_WordLength = USART_WordLength_8b;
	UART_InitStructure.USART_StopBits = USART_StopBits_1;
	UART_InitStructure.USART_Parity = USART_Parity_Even;
	UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/*initalisation des GPIO*/
	//RCC_AHB1PeriphClockCmd(UART4_TX_PIN | UART4_RX_PIN, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	/*pas sure c'est quoi*/
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);

	/*Configuration de TX*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	/*Configuration de RX*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	USART_Init(UART4, &UART_InitStructure);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(UART4,ENABLE);
}


void Traducteur_Commandes(char commande, char parametre, char checksum){

	switch(commande){
	case 0x41: /*allume-eteint la led*/
		if (parametre == 0x30){
			LED_OFF();
		}
		else if(parametre == 0x31){
			LED_ON();
		}
		break;

	case 0x42:/*efface seconde ligne*/
		TM_HD44780_Clear();
		TM_HD44780_Puts(0, 0,"FDFB");
		Ecriture_temps(temps_ecoule);
		curseur = 0;
		break;

	case 0x43:/*ecrit octet*/
		if (curseur < 16){ /*pas de depassement*/
			TM_HD44780_Puts(curseur, 1, &parametre);
			TM_HD44780_Puts(curseur + 1, 1, "      ");
			TM_HD44780_Puts(0, 0,"FDFB");
			curseur++;
		}

		break;
    }
}

void ajout_data_buffer(char* buffer, char octet){

	if (ptr_ecriture > size - 1){
			ptr_ecriture = 0;
			buffer[ptr_ecriture] = octet;
			ptr_ecriture++;
			nombre_ecriture++;
		}
	else if(ptr_ecriture ==  ptr_lecture){ /*etat initale*/
		buffer[ptr_ecriture] = octet;
	    ptr_ecriture++;
	    nombre_ecriture++;
    }

	else if(ptr_ecriture != ptr_lecture){ /*on n'ecrit pas sur une lecture en cours*/
		buffer[ptr_ecriture] = octet;
	    ptr_ecriture++;
	    nombre_ecriture++;
	}

}

void lecture_data_buffer(char* buffer){

	while(nombre_lecture + 3 <= nombre_ecriture){
        char liste[3];

		for(int i = 0; i < 3; i++) {
			if(ptr_lecture > size - 1) {
				ptr_lecture = 0;
			}
			liste[i] = buffer[ptr_lecture];
			ptr_lecture ++;
			nombre_lecture++;
		}

		if((liste[0] + liste[1] + liste[2])%256 == 0){
		Traducteur_Commandes(liste[0],liste[1],liste[2]);
		}
	}
}

void UART4_IRQHandler(void){
	STM_EVAL_LEDToggle(LED5);
	/*gpio monitoring*/
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) /*effectue interrupt lorsque recoit*/
    {

       USART_ClearITPendingBit(UART4, USART_IT_RXNE);
       ajout_data_buffer( buffer_commandes , (char) USART_ReceiveData(UART4) ); /*ajoute data au tab*/
    }

    Delay(200);

}




/*autre methode possible*/
	//if (UART4->SR & USART_FLAG_IDLE) { /* We want IDLE flag only */

		//ajout_data_buffer(buffer_commandes,UART4->DR); /* Read data register */
		//ptr_ecriture++;
	//}








#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
