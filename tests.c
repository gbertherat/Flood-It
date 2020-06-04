#include "fonctions.h"

int stateZoneTest(zone * z){
	for(int i = 0; i < (*z).ligne; i++){
		for(int j = 0; j < (*z).colonne; j++){
			(*z).coords[i][j] = 1;
		}
	}
	return stateZone(z) == 1;
}

/*
int main(void){
	zone jeu;
	initZone(&jeu, 6, 6);
	printf("Test stateZone: %i\n",stateZoneTest(&jeu));
	return 0;
}
*/