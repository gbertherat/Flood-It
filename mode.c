#include "fonctions.h"

/* Mode solo */
void solo(int ligne, int colonne, int nbCouleurs){
	zone jeu;
	initZone(&jeu, ligne, colonne, nbCouleurs);

	int choix;
	int tmp;
	bool done = false;
	while(done == false && choix != 8){
		clear();
		getScore(&jeu);
		printf("\nScore: %i\n", jeu.score);
		printf("Nombre de coups: %i\n\n", jeu.nbCoups);
		printZone(&jeu, NULL);
		printf("Choisissez une couleur:\n\
			\033[0m 1) \033[0;31m■\n\
			\033[0m 2) \033[0;32m■\n\
			\033[0m 3) \033[0;33m■\n\
			\033[0m 4) \033[0;34m■\n\
			\033[0m 5) \033[0;35m■\n\
			\033[0m 6) \033[0;36m■\n\
			\033[0m 7) \033[0;37m■\n\
			\033[0m 8) Annuler\n");
		printf(">> ");
		int status = scanf("%d", &choix);
		while(status != 1){
			while((tmp = getchar()) != EOF && tmp != '\n');
			printf("Valeur invalide!\n>> ");
			status = scanf("%d", &choix);
		}

		if(choix > 0 && choix < 9 && choix ){
			if(choix != 8){
				jeu.nbCoups++;
				remplirZone(&jeu, jeu.coords[0][0], choix, 0, 0);
			} else {
				done = true;
			}
		}

		if(stateZone(&jeu) == 1){
			clear();
			printZone(&jeu, NULL);
			printf("Vous avez gagné avec %i coups!\n", jeu.nbCoups);
			done = true;
		} /*else if(jeu.nbCoups >= 22){
			clear();
			printZone(&jeu, NULL);
			printf("Vous avez perdu..\n");
			done = true;
		}*/
	}
	freeZone(&jeu);

	printf("\nAppuyez sur entrée pour continuer.\n");
	while((tmp = getchar()) != EOF && tmp != '\n');
	getchar();
	main();
}

/* Mode contre l'ordinateur */
void ordinateur(int ligne, int colonne, int nbCouleurs, int difficulte){
	zone jeu;
	initZone(&jeu, ligne, colonne, nbCouleurs);

	zone computer;
	initZone(&computer, ligne, colonne, nbCouleurs);
	computer.difficulte = difficulte;
	int * listeCoups = malloc(difficulte*sizeof(int));

	zone temp;
	initZone(&temp, ligne, colonne, nbCouleurs);

	int choix = 0;
	int tmp = 0;
	bool done = false;
	while(done == false && choix != 8){
		copyArray(&computer, &temp);
		bestSolutionN(&computer, &temp, listeCoups, 0);
		clear();
		getScore(&jeu);
		printf("\nScore: %i\n", jeu.score);
		printf("Nombre de coups: %i\n\n", jeu.nbCoups);
		printZone(&jeu, &computer);
		printf("Choisissez une couleur:\n\
			\033[0m 1) \033[0;31m■\n\
			\033[0m 2) \033[0;32m■\n\
			\033[0m 3) \033[0;33m■\n\
			\033[0m 4) \033[0;34m■\n\
			\033[0m 5) \033[0;35m■\n\
			\033[0m 6) \033[0;36m■\n\
			\033[0m 7) \033[0;37m■\n\
			\033[0m 8) Annuler\n");
		printf(">> ");
		int status = scanf("%i", &choix);
		while(status != 1){
			while((tmp = getchar()) != EOF && tmp != '\n');
			printf("Valeur invalide!\n>> ");
			status = scanf("%i", &choix);
		}

		if(choix > 0 && choix < 9 && choix != jeu.coords[0][0]){
			if(choix != 8){
				jeu.nbCoups++;
				remplirZone(&jeu, jeu.coords[0][0], choix, 0, 0);
				remplirZone(&computer, computer.coords[0][0], computer.bestCoups[0], 0, 0);
				clearList(computer.bestCoups, difficulte, 0);
				computer.score = 0;
				computer.nbCoups++;
			} else {
				done = true;
			}
		}

		if(stateZone(&jeu) == 1){
			clear();
			printZone(&jeu, &computer);
			printf("Vous avez gagné avec %i coups!\n", jeu.nbCoups);
			done = true;
		} else if(stateZone(&computer) == 1){
			clear();
			printZone(&jeu, &computer);
			printf("L'ordinateur a gagné avec %i coups.\n", computer.nbCoups);
			done = true;
		}
	}
	freeZone(&jeu);
	freeZone(&computer);
	freeZone(&temp);

	printf("\nAppuyez sur entrée pour continuer.\n");
	while((tmp = getchar()) != EOF && tmp != '\n');
	getchar();
	main();
}
