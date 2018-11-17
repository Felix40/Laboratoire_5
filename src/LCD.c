/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LCD.h"


/* Pourquoi ici*/
#ifdef __cplusplus
extern "C"
#endif
/*-------------*/

/*Routine d'initalisation du module SPI1 du microcontroleur*/
void Init_SPI(void){

	/*Les pins utilisees par ce module sont :
	 *PA4 = NSS (Slaver selector, pas utile puisque une memoire)
	 *PA5 = SCK (la clock, pas active jusqu'a envoie de donnees sur le bus)
	 *PA6 = MISO (Master in, slave out)
	 *PA7 = MOSI (Master out, slave in)
	 */

	/*Initalisation SCKL, Master in, Slave out, Master Out Slave In*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_6| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*Connection des pins au module SPI1*/
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	/*Initalisation du module SPI1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStructure);

    /*Routine d'initalisation liees aux interactions avec la memoire
    *Pin 6 = WP (active LOW)
    *Pin 7 = HOLD (active LOW)
    *Pin 8 = CS (active LOW)
    */

	/*Initalisation GPIOC pour usage des pins*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7 |GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIOC->BSRRL|= GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; /*Pin set HIGH*/

    SPI_Cmd(SPI1, ENABLE);

    //SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SPE | SPI_CR1_SSM | SPI_CR1_SSI;
}

/*Fonction permettant la lecture de l'information contenue dans la memoire*/
char LireMemoireEEPROM(unsigned int AdresseEEPROM, unsigned int NbreOctets, unsigned char *Destination){

	if ((AdresseEEPROM + NbreOctets)> 0x4000 || AdresseEEPROM < 0 || NbreOctets < 0){
		return 1;
	}
	char return_value = 1;

	unsigned int ADDR[2];

   	ADDR[0] = (AdresseEEPROM) & 0xFF; //msb
	ADDR[1] = ((AdresseEEPROM) >> 8) & 0xFF;//lsb

    GPIOC->BSRRH |= GPIO_Pin_8; /*Chip select LOW*/

    SPISend(0b00000011); /*READ INSTRUCTION*/

    SPISend(ADDR[1]); //envoie les 8 msb

    SPISend(ADDR[0]); //envoie les 8 lsb

    for (int i = 0; i < NbreOctets; i++){

    Destination[i] = SPISend(0b00000000); /*envoi des dummy bits pour recevoir l'information*/

    }

    GPIOC->BSRRL |= GPIO_Pin_8; /*Chip select HIGH*/

    return_value = 0;

	return return_value;
}

/*Fonction permettant l'ecriture de l'information contenue dans la memoire*/
char EcrireMemoireEEPROM(unsigned int AdresseEEPROM, unsigned int NbreOctets, unsigned char *Source){

	if ((AdresseEEPROM + NbreOctets)> 0x4000 || AdresseEEPROM < 0 || NbreOctets < 0){
		return 1;
	}

	char return_value = 1;

	unsigned int AddresseCourante;

	AddresseCourante = AdresseEEPROM;

    unsigned int ADDR[2];

 	ADDR[0] = (AddresseCourante) & 0xFF; //msb
	ADDR[1] = ((AddresseCourante) >> 8) & 0xFF;//lsb

 	 GPIOC->BSRRH |= GPIO_Pin_8; /*Chip select LOW*/

 	 SPISend(0b00000110);   /*SET WRITE ENABLE LATCH*/

     GPIOC->BSRRL |= GPIO_Pin_8; /*Chip select HIGH*/

     GPIOC->BSRRH |= GPIO_Pin_8;/*Chip select LOW*/

     SPISend(0b00000010); /*WRITE INSTRUCTION*/

     SPISend(ADDR[1]); //envoie les 8 msb

     SPISend(ADDR[0]); //envoie les 8 lsb

	 SPISend(Source[0]);

	 AddresseCourante++;

	for (int i = 1; i < NbreOctets; i++){
		 if (AddresseCourante%64 == 0){ /*Si addresse courante est sur une nouvelle page*/

			 Delay(10);

			 GPIOC->BSRRL |= GPIO_Pin_8; /*Chip select HIGH*/

			 Delay(10);

			 ADDR[0] = (AddresseCourante) & 0xFF; //msb
			 ADDR[1] = ((AddresseCourante) >> 8);//lsb

		     GPIOC->BSRRH |= GPIO_Pin_8; /*Chip select LOW*/

		 	 SPISend(0b00000110);   /*SET WRITE ENABLE LATCH*/

		     GPIOC->BSRRL |= GPIO_Pin_8; /*Chip select HIGH*/

		     GPIOC->BSRRH |= GPIO_Pin_8;/*Chip select LOW*/

		     SPISend(0b00000010); /*WRITE INSTRUCTION*/

		     SPISend(ADDR[1]); //envoie les 8 msb

		     SPISend(ADDR[0]); //envoie les 8 lsb

			 SPISend(Source[i]);

			 AddresseCourante++;
		 }
		 else{
		 SPISend(Source[i]);
		 AddresseCourante++;}
	}

	Delay(10);

    GPIOC->BSRRL |= GPIO_Pin_8; /*Chip select HIGH*/

	return_value = 0;

    return return_value; /*retourne 0 car tout est ok*/
}

/*Fonction homemade de transfert SPI (plus robuste)*/
uint8_t SPISend(uint8_t data){

SPI1->DR = data;

while (!(SPI1->SR & SPI_I2S_FLAG_TXE));

while (!(SPI1->SR & SPI_I2S_FLAG_RXNE));

while (SPI1->SR & SPI_I2S_FLAG_BSY);

return(SPI1->DR);
}
