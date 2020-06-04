#ifndef fonctions_h
#define fonctions_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>

typedef struct{
	int ligne, colonne;
	int ** coords;
	int difficulte;
	int * bestCoups;
	int listeLen;
	int nbCoups;
	int score;
} zone;

void clear();

void clearList(int * liste, int n, int p);

void initZone(zone * z, int line, int col, int n);

void freeZone(zone * z);

void printZone(zone * z, zone * j);

int stateZone(zone * z);

void remplirZone(zone * z, int oldColor, int newColor, int i, int j);

void voisins(zone * z, int oldColor, int i, int j, int listeVoisins[8]);

void getScore(zone * z);

void score(zone * z, int oldColor, int i, int j);

void bestSolution(zone * base, zone * test, int * listeCoups, int index);

void bestSolutionN(zone * base, zone * test, int * listeCoups, int index);

int main(void);

void solo(int ligne, int colonne, int nbCouleurs);

void ordinateur(int ligne, int colonne, int nbCouleurs, int difficulte);

void copyArray(zone * z1, zone * z2);

#endif
