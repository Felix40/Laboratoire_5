
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
