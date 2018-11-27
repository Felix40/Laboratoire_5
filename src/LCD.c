
#include "LCD.h"

void init_LCD(void){
	  TM_DELAY_Init();
	  TM_HD44780_Init(16,2);

}

void Ecriture_temps(unsigned int temps){

	char buffer[5];
	Convertir_str(buffer,temps);
	TM_HD44780_Puts(6,0,buffer);

}

void RESET_LCD(void){
	//trouver fonction reset
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

