/*Fichier principal du laboratoire 5*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


int main(void)
{
  temps_ecoule = 0; /*initalise le temps*/
  TimingGlobal = 1000;

  INIT_UART();     /*initalise les pins du module UART (ainsi que le module lui-meme*/
  init_LCD();      /*initialise le lcd*/
  TM_HD44780_Puts(0, 0,"FDFB");

  while (1) {
	  Ecriture_temps(temps_ecoule);
  }
}

void LED_ON(void){
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
}

void LED_OFF(void){
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
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
