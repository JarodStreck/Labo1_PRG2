/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : J. Streckeisen, A. Martins, G. Courbat
 Date creation  : 26.04.2022

 Description    : Ce programme permet de simuler une planche de Galton. C'est à dire
 						comptabiliser

 Remarque(s)    : <� compl�ter>

 Compilateur    : Mingw-w64 gcc 11.2.0
 -----------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

const unsigned int NOMBRE_ELEMENT = 512;
const unsigned int TAILLE_ELEMENT = sizeof(char);
const unsigned int TAILLE_BUFFER = NOMBRE_ELEMENT * TAILLE_ELEMENT;

const unsigned int MIN_NB_BILLE = 1000;
const unsigned int MAX_NB_BILLE = 30000;
const unsigned int MIN_NB_ETAGE = 10;
const unsigned int MAX_NB_ETAGE = 20;
const unsigned TAILLE_HISTO = 15;

bool testerSaisieNumerique(const unsigned int valeur, const char *buffer1, const
char *buffer2, const unsigned int min, const unsigned int max);

unsigned valeurMax(const unsigned *tab, const unsigned rangee, size_t taille);

unsigned longueurNumerique(unsigned valeur);

unsigned *allouerHistogramme(const unsigned *tableau, unsigned rangee,
unsigned max, size_t taille);

void afficherHistogramme(const unsigned *histogramme, unsigned rangee,
								 unsigned nombreChiffre);


unsigned int *plancheGalton(unsigned nombreBille, unsigned int
nombreEtage, const size_t taille);

void afficherPlanche(const unsigned *tab, unsigned nombreEtage,
							unsigned tailleChiffre);


int main() {
	unsigned int nombreBille = 0;
	unsigned int nombreEtage = 0;

	//Allocation de deux zones mémoires qui servira a stocker les entrées utilisateurs
	char *tamponChaineEntree = (char *) calloc(NOMBRE_ELEMENT, TAILLE_ELEMENT);
	char *tamponEntierEntree = (char *) calloc(NOMBRE_ELEMENT, TAILLE_ELEMENT);

	//On vérifie que la mémoire a bien été allouée
	assert(tamponChaineEntree != NULL);
	assert(tamponEntierEntree != NULL);
	//On test que l'entrée utilisateur soit correct
	do {
		printf("Entrez le nombre de billes [1000 - 30000] : ");
		//On enregistre l'entré utilisateur en tant que string dans une zone tampon,
		// on extrait ensuite un entier et on le convertis en string et on le met dans
		// la seconde zone tampon.
		scanf("%s", tamponChaineEntree);
		sscanf(tamponChaineEntree, "%u", &nombreBille);
		sprintf(tamponEntierEntree, "%u", nombreBille);
		//On vérifie que l'entré est correct
		if (!testerSaisieNumerique(nombreBille, tamponChaineEntree, tamponEntierEntree,
											MIN_NB_BILLE, MAX_NB_BILLE)) {
			printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
		}
	} while (!testerSaisieNumerique(nombreBille, tamponEntierEntree,
											  tamponChaineEntree, MIN_NB_BILLE,
											  MAX_NB_BILLE));
	//On met à 0 tous les bits des deux zones tampons pour les réutiliser
	memset(tamponChaineEntree, 0, TAILLE_BUFFER);
	memset(tamponEntierEntree, 0, TAILLE_BUFFER);

	do {
		printf("Entrez le nombre de rangees de compteurs [10-20] : ");

		scanf("%s", tamponChaineEntree);
		sscanf(tamponChaineEntree, "%u", &nombreEtage);
		sprintf(tamponEntierEntree, "%u", nombreEtage);
		if (!testerSaisieNumerique(nombreEtage, tamponChaineEntree,
											tamponEntierEntree, MIN_NB_ETAGE,
											MAX_NB_ETAGE)) {
			printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
		}
	} while (!testerSaisieNumerique(nombreEtage, tamponChaineEntree,
											  tamponEntierEntree,
											  MIN_NB_ETAGE, MAX_NB_ETAGE));


	//libération de la mémoire
	free(tamponChaineEntree);
	free(tamponEntierEntree);

	tamponChaineEntree = NULL;
	tamponEntierEntree = NULL;


	const size_t taille = (nombreEtage + 1) * nombreEtage / 2;


	srand(time(NULL));

	unsigned int *planche = plancheGalton(nombreBille, nombreEtage, taille);
	printf("\n");

	afficherPlanche(planche, nombreEtage, longueurNumerique(nombreBille) + 1);
	//printf("%u\n", valeurMax(tableau,nombreEtage,taille));
	unsigned int *histogramme =
		allouerHistogramme(planche, nombreEtage,
								 valeurMax(planche,nombreEtage, taille), taille);
	afficherHistogramme(histogramme, nombreEtage, longueurNumerique(nombreBille)
																 + 1);
	free(histogramme);
	histogramme = NULL;
	free(planche);
	planche = NULL;


	return EXIT_SUCCESS;
}

bool testerSaisieNumerique(const unsigned int valeur, const char *buffer1, const
char *buffer2, const unsigned int min, const unsigned int max) {
	if (valeur > max || valeur < min || strcmp(buffer1, buffer2) != 0) {
		return false;
	}
	return true;
}

unsigned int* plancheGalton(unsigned int nombreBille,
						 unsigned int nombreEtage, const size_t taille) {

	assert(taille > 0);
	unsigned int *planche = (unsigned int *) calloc(taille,
																	sizeof(unsigned int));
	if(planche) {
		planche[0] = nombreBille;
		size_t indice = 0;

		for (size_t k = 0; k < nombreBille; ++k) {
			for (size_t l = 1; l < nombreEtage; ++l) {
				//50% de chance de sortir un 1 ou 0
				indice += l + (rand() & 1);
				planche[indice] += 1;
			}
			indice = 0;
		}

		return planche;
	} else{

		return NULL;
	}
}

void afficherPlanche(const unsigned *tab, const unsigned nombreEtage, const
unsigned tailleChiffre) {

	unsigned int decrement = tailleChiffre / 2;
	unsigned int espace =
		tailleChiffre * nombreEtage / 2 - (decrement + tailleChiffre % 2);
	unsigned int indice = 0;

	for (size_t k = 0; k < nombreEtage; ++k) {
		printf("%*s", espace, "");
		indice += k;

		for (size_t l = indice; l <= indice + k; ++l) {
			printf("%*u", tailleChiffre, *(tab + l));
		}

		espace -= decrement + (tailleChiffre % 2 && k % 2);
		printf("\n");
	}
}


unsigned valeurMax(const unsigned *tab, const unsigned rangee, const size_t taille) {
	unsigned indice = taille - rangee;
	unsigned max = *(tab + indice);

	for (size_t k = 0; k < rangee; ++k) {
		if (*(tab + indice + k) > max) {
			max = *(tab + indice + k);
		}
	}
	return max;
}


unsigned *allouerHistogramme(const unsigned *tableau, const unsigned rangee,
const unsigned max, const size_t taille) {

	unsigned *histogramme = (unsigned *) calloc(rangee, sizeof(unsigned));
	//if(histo)....
	unsigned indice = taille - rangee;
	for (unsigned i = 0; i < rangee; ++i) {
		*(histogramme + i) = (unsigned) (TAILLE_HISTO *
													(double) *(tableau + indice + i) / max);
	}
	return histogramme;
}

void afficherHistogramme(const unsigned *histogramme, const unsigned rangee,
								const unsigned nombreChiffre) {
	for (unsigned i = TAILLE_HISTO; i > 0; --i) {
		for (unsigned j = 0; j < rangee; ++j) {
			if (i <= *(histogramme + j))
				printf("%*c", nombreChiffre, '*');
			else
				printf("%*c", nombreChiffre, ' ');
		}
		printf("\n");
	}
}

unsigned longueurNumerique(unsigned valeur) {
	unsigned i = 0;

	while (valeur != 0) {
		valeur /= 10;
		i++;
	}
	return i;
}
