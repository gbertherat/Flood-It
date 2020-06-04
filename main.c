#include "fonctions.h"

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL));
	clear();
	int choix = 0;
	int ligne = 0;
	int colonne = 0;
	int nbCouleurs = 0;
	int tmp = 0;

	printf("-------------------------------\n");
	printf("\033[1;31mFlood-It by Bertherat Guillaume\n\033[0m");
	printf("-------------------------------\n");

	printf("\033[1;34mChoisissez une mode de jeu:\033[0m\n\
		1) Solo\n\
		2) Contre l'ordinateur\n\
		3) Quitter\n");
	printf(">> ");
	int status = scanf("%d", &choix);
	while(status != 1){
		while((tmp = getchar()) != EOF && tmp != '\n');
		printf("Valeur invalide\n>> ");
		status = scanf("%d", &choix);
	}

	if(choix == 1 || choix == 2){
		ligne = 0;
		colonne = 0;
		nbCouleurs = 0;

		while(ligne < 3 || ligne > 30){
			printf("\n Choisissez un nombre de ligne (Entre 3 et 30)\n>> ");
			status = scanf("%d", &ligne);
			while(status != 1){
				while((tmp = getchar()) != EOF && tmp != '\n');
				printf("Valeur invalide\n>> ");
				status = scanf("%d", &ligne);
			}
		}

		while(colonne < 3 || colonne > 30){
			printf("\n Choisissez un nombre de colonne (Entre 3 et 30)\n>> ");
			status = scanf("%d", &colonne);
			while(status != 1){
				while((tmp = getchar()) != EOF && tmp != '\n');
				printf("Valeur invalide\n>> ");
				status = scanf("%d", &colonne);
			}
		}

		while(nbCouleurs < 3 || nbCouleurs > 7){
			printf("\n Choisissez un nombre de couleur (Entre 3 et 7)\n>> ");
			status = scanf("%d", &nbCouleurs);
			while(status != 1){
				while((tmp = getchar()) != EOF && tmp != '\n');
				printf("Valeur invalide\n>> ");
				status = scanf("%d", &nbCouleurs);
			}
		}
	}

	switch(choix){
		case 1:{
			solo(ligne, colonne, nbCouleurs);
			break;
		}
		case 2:{
			int difficulte = 1;
			printf("\n-------------------------------\n");
			printf("Choisissez une difficulté:\n\
				1) \033[0;32mFacile\033[0m\n\
				2) \033[0;33mMoyen\n\033[0m\
				3) \033[0;31mDifficile\n\033[0m\
				4) \033[0;35mImpossible\n\033[0m\
				5) Quitter\n");
			printf(">> ");
			status = scanf("%d", &difficulte);
			while(status != 1){
				while((tmp = getchar()) != EOF && tmp != '\n');
				printf("Valeur invalide\n>> ");
				status = scanf("%d", &difficulte);
			}

			if(difficulte > 0 && difficulte < 6){
				if(difficulte == 5){
					return 0;
				} else {
					ordinateur(ligne, colonne, nbCouleurs, difficulte);
				}
			} else {
				main();
			}
			break;
		}
		case 3:{
			return 0;
		}
		default:{
			main();
		}
	}
  return 0;
}
