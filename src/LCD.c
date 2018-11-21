
#include "LCD.h"

/*Acces memoire*/
int volatile * const ODRD_ADDRESS = (int *) 0x40020c14;  /*Addresse pour parler au LCD*/
int volatile * const IDRC_ADDRESS = (int *) 0x40020810;  /*Addresse pour envoyer HIGH sur la matrice du keyboard*/
int volatile * const ODRA_ADDRESS = (int *) 0x40020014;  /*Addresse pour lire les donnes du keyboard*/
int volatile * const ODRE_ADDRESS = (int *) 0x40021014;  /*Addresse pour ecrire le EN*/

/*variable globale d'etat*/
bool isReset = false; /*Variable signalant si un reset a eu lieu*/

int char_counter = 0; /*counter permettant de savoir combien de lettre sont actuellement affiches*/
int numeros_array[10];/*array contenant les chiffres a afficher*/
int i = 0; /*increment globale*/


/*fonction permettant d'init les pins liees au clavier (pins IN et OUT)*/
void init_Keyboard_Pins(void){
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); /*On utilise le port A pour le LCD OUT*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;

   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); /*On utilise le port C pour le LCD IN*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|
		   GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;

   /*Settings des pins*/
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //Doit-on le mettre en open drain?
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //pulldown
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*fonction permettant d'init les pins liees au LCD (pins OUT)*/
void init_LCD_Pins(void){

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); /*On utilise le port D pour le LCD*/

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|
		  GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7| /*DB0 a DB7*/
		  GPIO_Pin_8 | GPIO_Pin_9; /*RW et RS*/

  /*Settings des pins OUT*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); /*On utilise le port E pour ENABLE*/

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

  /*Settings des pins*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

}

/*fonction d'activation du LCD (LCD pret a ecrire apres appel)*/
void Activation_LCD(void){
	/*operation 8 bits et 2 lignes*/

	Write_LCD(0x0001); /*Display clear*/

	Write_LCD(0x0038); /*Set operation 8 bits sur 2 lignes*/

    Write_LCD(0x000E); /*LCD screen on*/

    Write_LCD(0x0006); /*Set entry mode*/

}

/*fonction d'ecriture de data sur le LCD (prend la valeur du chiffre hexadecimal)*/
void Write_LCD(int nombre){

	*ODRE_ADDRESS = 0x0001;

	Delay(5);

	*ODRD_ADDRESS = nombre;

	Delay(5);

	*ODRE_ADDRESS= 0x0000;

	Delay(5);

}

/*fonction de lecture des INPUT du keyboard, mets a jour la liste des INPUTS*/
void Read_Keyboard(void){

	i = 0;  /*increment du tableau*/

    *ODRA_ADDRESS = 0x0002; /*Set la pin 0 HIGH*/

    switch (*IDRC_ADDRESS){
    case 0x0003:numeros_array[i] = 0x0001, isReset = true, Delay(500);break; /*Ecrit le signal reset*/
    case 0x0005:numeros_array[i] = 0x0230,i++,Delay(500);break; /*Ecrit 0*/
    }

    *ODRA_ADDRESS = 0x0004; /*Set la pin 1 HIGH*/
    Delay(100);

    switch(*IDRC_ADDRESS){
    case 0x0003: numeros_array[i] = 0x0239,i++,Delay(500);break; /*Ecrit 9*/
    case 0x0005: numeros_array[i] = 0x0238,i++,Delay(500);break; /*Ecrit 8*/
    case 0x0011: numeros_array[i] = 0x0237,i++,Delay(500);break; /*Ecrit 7*/

    case 0x0007: numeros_array[i] = 0x0239,i++,Delay(500), numeros_array[i] = 0x0238,i++,Delay(500);break; /*Ecrit 98*/
    case 0x0013: numeros_array[i] = 0x0239,i++,Delay(500), numeros_array[i] = 0x0237,i++,Delay(500);break; /*Ecrit 97*/
    case 0x0015: numeros_array[i] = 0x0238,i++,Delay(500), numeros_array[i] = 0x0237,i++,Delay(500);break; /*Ecrit 87*/
    }

    *ODRA_ADDRESS = 0x0008; /*Set la pin 2 HIGH*/
    Delay(100);

    switch(*IDRC_ADDRESS){
    case 0x0003: numeros_array[i] = 0x0236,i++,Delay(500);break; /*Ecrit 6*/
    case 0x0005: numeros_array[i] = 0x0235,i++,Delay(500);break; /*Ecrit 5*/
    case 0x0011: numeros_array[i] = 0x0234,i++,Delay(500);break; /*Ecrit 4*/

    case 0x0007: numeros_array[i] = 0x0236,i++,Delay(500), numeros_array[i] = 0x0235,i++,Delay(500);break; /*Ecrit 65*/
    case 0x0013: numeros_array[i] = 0x0236,i++,Delay(500), numeros_array[i] = 0x0234,i++,Delay(500);break; /*Ecrit 64*/
    case 0x0015: numeros_array[i] = 0x0235,i++,Delay(500), numeros_array[i] = 0x0234,i++,Delay(500);break; /*Ecrit 54*/
    }

    *ODRA_ADDRESS = 0x0010; /*Set la pin 3 HIGH*/
    Delay(100);

    switch(*IDRC_ADDRESS){
    case 0x0003: numeros_array[i] = 0x0233,i++,Delay(500);break; /*Ecrit 3*/
    case 0x0005: numeros_array[i] = 0x0232,i++,Delay(500);break; /*Ecrit 2*/
    case 0x0011: numeros_array[i] = 0x0231,i++,Delay(500);break; /*Ecrit 1*/

    case 0x0007: numeros_array[i] = 0x0233,i++,Delay(500), numeros_array[i] = 0x0232,i++,Delay(500);break; /*Ecrit 32*/
    case 0x0013: numeros_array[i] = 0x0233,i++,Delay(500), numeros_array[i] = 0x0231,i++,Delay(500);break; /*Ecrit 31*/
    case 0x0015: numeros_array[i] = 0x0232,i++,Delay(500), numeros_array[i] = 0x0231,i++,Delay(500);break; /*Ecrit 21*/
    }

    char_counter = char_counter+i;


}

/*fonction permettant d'ecrire SMI+initiales*/
void Ecriture_SMI(void){

	Write_LCD(0x00000253); /*Ecrit S*/

	Write_LCD(0x0000024D); /*Ecrit M*/

	Write_LCD(0x00000249); /*Ecrit I*/

	Write_LCD(0x0000025F); /*Ecrit _*/

	Write_LCD(0x00000246); /*Ecrit F*/

	Write_LCD(0x00000244);  /*Ecrit D*/

	Write_LCD(0x00000246);  /*Ecrit F*/

	Write_LCD(0x00000242);  /*Ecrit B*/

}

void Ecriture_temps(void){

	Write_LCD(0x00000246); /*Ecrit F*/

	Write_LCD(0x00000244);  /*Ecrit D*/

	Write_LCD(0x00000246);  /*Ecrit F*/

	Write_LCD(0x00000242);  /*Ecrit B*/

	Write_LCD(temps_ecoule);
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

