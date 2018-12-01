/*Fichier principal du laboratoire 5*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"


int main(void)
{
  /*initalisation des variables*/
  temps_ecoule = 0;
  TimingGlobal = 1000;
  curseur = 0;
  ptr_ecriture = 0;
  ptr_lecture = 0;
  time_counter = 0;
  nombre_ecriture = 0;
  nombre_lecture = 0;

  INIT_UART();     /*initalise les pins du module UART (ainsi que le module lui-meme*/
  init_LED();      /*initalise la LED a interfacer*/
  TIM2_INIT();     /*initalise le TIM2*/
  init_Monitoring();/*initalise les GPIO de monitoring*/
  init_LCD();      /*initialise le lcd*/
  TM_HD44780_Puts(0, 0,"FDFB");

  while (1) {


	  STM_EVAL_LEDToggle(LED3);
	 Ecriture_temps(temps_ecoule);
	 lecture_data_buffer(buffer_commandes);



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
