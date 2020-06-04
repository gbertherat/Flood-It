#include "fonctions.h"

/*
 * Permet de vider la console en fonction de l'OS utilisé
 *
 */
void clear(){
	#ifdef _WIN32
	system("cls");
	#elif _WIN64
	system("clear");
	#elif __linux__
	system("clear");
	#endif
}

/*
 * Permet de reinitialiser une liste
 * Entree: liste - La liste a reinitialiser
 * Entree: n - La taille de la liste
 * Entree: p - Par quoi remplir la liste
 */
void clearList(int * liste, int n, int p){
	for(int i = 0; i < n; i++){
		liste[i] = p;
	}
}

/*
 * Permet de copier une zone de jeu
 * Entrée: z1 - La zone à copier
 * Entrée: z2 - La zone qui copie
 */
void copyArray(zone * z1, zone * z2){
	for(int i = 0; i < z1 -> ligne; i++){
		for(int j = 0; j < z1 -> colonne; j++){
			z2 -> coords[i][j] = z1 -> coords[i][j];
		}
	}
	return;
}

/*
 * La fonction initZone permet d'initialiser une zone de
 * jeu.
 * Entree: z -  La zone a initialiser
 * Entree: line - Nombre de lignes de la zone
 * Entree: col - Nombre de colonnes de la zone
 * Entree: n - Nombre de couleurs
 */
void initZone(zone * z, int line, int col, int n){
	z -> ligne = line;
	z -> colonne = col;
	z -> bestCoups = malloc(50*sizeof(int));
	z -> listeLen = 50;
	z -> nbCoups = 0;
	z -> score = 0;
	z -> coords = (int**) malloc(line * sizeof(int*));
	for(int i = 0; i < line; i++){
		z -> coords[i] = (int*) malloc(col * sizeof(int));
		for(int j = 0; j < col; j++){
			z -> coords[i][j] = rand()%n+1;
		}
	}
}

/*
 * Permet de libérer l'espace mémoire prise par
 * une zone de jeu
 * Entrée: z - La zone à libérer
 */
void freeZone(zone * z){
	free(z->bestCoups);
	for(int i = 0; i < z -> ligne; i++){
		free(z->coords[i]);
	}
	free(z->coords);
}

/*
 * La fonction printZone permet d'afficher une zone de
 * jeu dans la console.
 * Entree: z - La premiere zone a afficher
 * Entree: w - La deuxieme zone a afficher (ou NULL)
 */
void printZone(zone * z, zone * w){
	const char *c[8] = {"\033[0m","\033[0;31m██","\033[0;32m██","\033[0;33m██","\033[0;34m██","\033[0;35m██","\033[0;36m██", "\033[0;37m██"};
	printf("Ton monde");
	if(w != NULL){
		for(int i = 0; i < z->colonne/4; i++){
			printf("\t");
		}
		printf("Le monde de l'ordinateur");
	}
	printf("\n");

	for(int i = 0; i < z->ligne; i++){
		for(int j = 0; j < z->colonne; j++){
			printf("%s", c[z->coords[i][j]]);
		}
		if(w != NULL){
			printf("\t");
			for(int j = 0; j < w->colonne; j++){
				printf("%s", c[w->coords[i][j]]);
			}
		}
		printf("\n");
	}
	printf("%s\n",c[0]);
}

/*
 * La fonction stateZone permet de retourner l'etat de la
 * zone de jeu.
 * Entree: z - La zone a verifier.
 * Sortie: 1 si toutes les cases sont identiques, 0 sinon.
 */
int stateZone(zone * z){
	for(int i = 0; i < z -> ligne; i++){
		for(int j = 0; j < z -> colonne; j++){
			if(z->coords[i][j] != z->coords[0][0]){
				return 0;
			}
		}
	}
	return 1;
}

/*
 * Permet de remplir une zone
 * Entrée: z - La zone à remplir
 * Entrée: oldColor - La couleur en 0,0
 * Entrée: newColor - La couleur à remplir
 * Entrées: i & j - Les coordonnées de la case à changer
 */
void remplirZone(zone * z, int oldColor, int newColor, int i, int j){
	if(i >= 0 && j >= 0 && i < z->ligne && j < z->colonne){
		if(z->coords[i][j] == oldColor && oldColor != newColor){
			z->coords[i][j] = newColor;
			remplirZone(z, oldColor, newColor, i, j+1);
			remplirZone(z, oldColor, newColor, i, j-1);
			remplirZone(z, oldColor, newColor, i+1, j);
			remplirZone(z, oldColor, newColor, i-1, j);
		}
	}
}

/*
 * Permet de récupérer les voisins de la zone principale
 * Entrée: z - La zone de jeu
 * Entrée: oldColor - Couleur en 0,0
 * Entrées: i & j - Les coordonnées de la case traitée
 * Entrée: listeVoisisn - Liste des voisins de la zone
 * principale
 */
void voisins(zone * z, int oldColor, int i, int j, int listeVoisins[8]){
	if(i >= 0 && j >= 0 && i < z->ligne && j < z->colonne){
		if(z->coords[i][j] == oldColor){
			z->coords[i][j] = 8;
			voisins(z, oldColor, i, j+1, listeVoisins);
			voisins(z, oldColor, i, j-1, listeVoisins);
			voisins(z, oldColor, i+1, j, listeVoisins);
			voisins(z, oldColor, i-1, j, listeVoisins);
		} else {
			listeVoisins[z->coords[i][j]]++;
		}
	}
}

// SCORE
/*
 * Permet de récupérer le score et de remettre la zone à
 * son état normal
 * Entrée: z - La zone à traiter
 */
void getScore(zone * z){
	z -> score = 0;
	int oldColor = z->coords[0][0];
	score(z, oldColor, 0, 0);
	remplirZone(z, z->coords[0][0], oldColor, 0, 0);
}

/*
 * Permet de calculer le score d'une zone (= sa surface)
 * Entrée: z - La zone à traiter
 * Entrée: oldColor - La couleur en 0,0
 * Entrées: i & j - Les coordonnées de la case actuelle
 */
void score(zone * z, int oldColor, int i, int j){
	if(i >= 0 && j >= 0 && i < z->ligne && j < z->colonne){
		if(z->coords[i][j] == oldColor){
			z->coords[i][j] = 8;
			z->score++;
			score(z, oldColor, i, j+1);
			score(z, oldColor, i, j-1);
			score(z, oldColor, i+1, j);
			score(z, oldColor, i-1, j);
		}
	}
}

/*
 * Permet de calculer la meilleure solution (= suite de
 * coups) pour une zone donnée
 * Entrée: base - La zone à calculer
 * Entrée: test - Une copie de la zone à calculer
 * Entrée: listeCoups - La liste de coups à réaliser
 * Entrée: index - La position dans la liste de coups
 */
void bestSolution(zone * base, zone * test, int * listeCoups, int index){
//	printf("Listelen : %i, index : %i\n", base->listeLen, index);
	// RECUPERATION DES VOISINS //
	int nbVoisins = 0;
	int listeVoisins[8] = {0,0,0,0,0,0,0,0};
	int oldColor = test->coords[0][0];
	voisins(test, oldColor, 0, 0, listeVoisins);
	remplirZone(test, test->coords[0][0], oldColor, 0, 0);

	for(int i = 1; i < 8; i++){
		if(listeVoisins[i] > 0){
			nbVoisins++;
			//printf("%i / ", i);
		}
	}

	// TRAITEMENT //
	int max = listeVoisins[0];
	int indiceMax = 0; // La couleur du voisin
	for(int i = 1; i < 8; i++){
		for(int j = 1; j < 8; j++){
			if(listeVoisins[j] > max){ // On récupère le voisin le plus présent
				max = listeVoisins[j];
				indiceMax = j;
			}
		}
		listeVoisins[indiceMax] = 0;
		max = 0;
		if(indiceMax > 0){
			// Création d'un monde temp
			zone temp;
			initZone(&temp, base->ligne, base->colonne, 7);
			copyArray(test, &temp);

			remplirZone(&temp, temp.coords[0][0], indiceMax, 0, 0);
			listeCoups[index] = indiceMax;
			index++;

			if(stateZone(&temp) != 1
			&& base->listeLen >= nbVoisins + index){
				// Appel récursif
				bestSolution(base, &temp, listeCoups, index);
			} else {
				if(base->listeLen >= index + nbVoisins){
					base->listeLen = index;
					for(int k = 0; k < index; k++){
						base->bestCoups[k] = listeCoups[k];
					}
					printf("\n");
				}
			}
			index--;
			listeCoups[index] = 0;
			freeZone(&temp);
		}
	}
}

/*
 * Permet de calculer la meilleure solution (= suite de
 * coups) pour une zone donnée et selon la difficulté du jeu
 * Entrée: base - La zone à calculer
 * Entrée: test - Une copie de la zone à calculer
 * Entrée: listeCoups - La liste de coups à réaliser
 * Entrée: index - La position dans la liste de coups
 */
void bestSolutionN(zone * base, zone * test, int * listeCoups, int index){
	int listeVoisins[8] = {0,0,0,0,0,0,0,0};
	int oldColor = test->coords[0][0];
	voisins(test, oldColor, 0, 0, listeVoisins);
	remplirZone(test, test->coords[0][0], oldColor, 0, 0);

	int max = listeVoisins[0];
	int indiceMax = 0;
	for(int i = 1; i < 8; i++){
		for(int j = 1; j < 8; j++){
			if(listeVoisins[j] > max){
				max = listeVoisins[j];
				indiceMax = j;
			}
		}

		max = 0;
		listeVoisins[indiceMax] = 0;
		if(indiceMax > 0){
			zone temp;
			initZone(&temp, base->ligne, base->colonne, 7);
			copyArray(test, &temp);

			remplirZone(&temp, temp.coords[0][0], indiceMax, 0, 0);
			listeCoups[index] = indiceMax;
			index++;

			getScore(&temp);

			if(stateZone(&temp) != 1
			&& index < base->difficulte){
				bestSolutionN(base, &temp, listeCoups, index);
			} else {
				if(base->score < temp.score){
					base->score = temp.score;
					for(int k = 0; k < index; k++){
						base->bestCoups[k] = listeCoups[k];
					}
				}
			}
			index--;
			listeCoups[index] = 0;
			freeZone(&temp);
		}
	}
}
