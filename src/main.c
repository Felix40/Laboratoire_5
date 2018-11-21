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

  init_LCD_Pins(); /*initalise les pins qui seront utilisees par le LCD*/
  INIT_UART();     /*initalise les pins du module UART (ainsi que le module lui-meme*/


  while (1)
  {
     Ecriture_temps(); /*Affiche les initales+temps sur la premiere ligne (mise a jour a chaque execution de code*/
	//ajouter commande reception et affichage uart

     Delay(500);
  }
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
	if (TimingGlobal != 0){
		TimingGlobal--;       /*Si une seconde ne s'est pas ecoulee, alors un decremente*/
	}
	else
		temps_ecoule++; /*si une seconde ecoule en interruption, alors une seconde ajoutee*/
	    TimingGlobal = 1000; /*on remet le TimingGlobal a 1000 pour compter une nouvelle seconde*/
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
