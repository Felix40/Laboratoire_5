/*Fichier principal du laboratoire 5*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


int main(void)
{
  if (SysTick_Config(SystemCoreClock / 1000)) /*interrupt every 1ms*/
  { 
    /* Capture error */ 
    while (1);
  }
  temps_ecoule = 0x00; /*initalise le temps*/
  TimingGlobal = 1000; /*initialise le timing global*/
  init_LED();       /*initalise la LED*/
  init_LCD_Pins(); /*initalise les pins qui seront utilisees par le LCD*/
  INIT_UART();     /*initalise les pins du module UART (ainsi que le module lui-meme*/
  Activation_LCD();

  while (1)
  {
     Ecriture_temps(temps_ecoule); /*Affiche les initales+temps sur la premiere ligne (mise a jour a chaque execution de code*/
	                   //ajouter commande reception et affichage uart
     Delay(1000);
     RESET_LCD();
  }
}

void init_LED(void){

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void LED_ON(void){
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
}

void LED_OFF(void){
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
}

void RESET_LCD(void){
	Write_LCD(0x0001);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

void TimingGlobal_Decrement(void){
	if(TimingGlobal == 0x00){
		temps_ecoule = temps_ecoule; /*si une seconde ecoule en interruption, alors une seconde ajoutee*/
	    TimingGlobal = 1000;
	}                        /*on remet le TimingGlobal a 1000 pour compter une nouvelle seconde*/

     else{
		TimingGlobal--;       /*Si une seconde ne s'est pas ecoulee, alors un decremente*/
     }
}

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
