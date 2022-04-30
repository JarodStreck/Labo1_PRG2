/*-----------------------------------------------------------------------------------
Nom de fichier : main.cpp
Auteur : G. Courbat, J. Streckeisen, A. Martins
Date de création : 26.04.2022
Description :
Remarque :
Compilateur : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define  BUFFER_SIZE  10 * sizeof(char)

const unsigned int MIN_NB_BILLE = 1000;
const unsigned int MAX_NB_BILLE = 30000;
const unsigned int MIN_NB_ETAGE = 10;
const unsigned int MAX_NB_ETAGE = 20;

bool testerSaisieNumerique(unsigned int valeur, char *buffer1, char *buffer2,
									unsigned int min, unsigned int max);
void plancheGalton(unsigned int *tab, unsigned nombreBille, unsigned int
nombreEtage);
void afficher(const unsigned int* adr, size_t n);

int main() {
	unsigned int nombreBille = 0;
	unsigned int nombreEtage = 0;



	char *buffer_string_entree = (char *) malloc(BUFFER_SIZE);
	char *buffer_entier_entree = (char *) malloc(BUFFER_SIZE);

	char test[4] = "1000";
	do {
		printf("Entrez le nombre de billes [1000 - 30000] : ");

		scanf("%s", buffer_string_entree);
		sscanf(buffer_string_entree, "%u", &nombreBille);
		sprintf(buffer_entier_entree, "%u", nombreBille);

		if (!testerSaisieNumerique(nombreBille, buffer_string_entree,
											buffer_entier_entree, MIN_NB_BILLE,
											MAX_NB_BILLE)) {
			printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
		}
	} while (!testerSaisieNumerique(nombreBille, buffer_entier_entree,
											  buffer_string_entree, MIN_NB_BILLE,
											  MAX_NB_BILLE));
	printf("Nombre bille : %u \n", nombreBille);

	memset(buffer_string_entree, 0, BUFFER_SIZE);
	memset(buffer_entier_entree, 0, BUFFER_SIZE);


	do {
		printf("Entrez le nombre de rangees de compteurs [10-20] : ");

		scanf("%s", buffer_string_entree);
		sscanf(buffer_string_entree, "%u", &nombreEtage);
		sprintf(buffer_entier_entree, "%u", nombreEtage);
		if (!testerSaisieNumerique(nombreEtage, buffer_string_entree,
											buffer_entier_entree, MIN_NB_ETAGE,
											MAX_NB_ETAGE)) {
			printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
		}
	} while (!testerSaisieNumerique(nombreEtage, buffer_string_entree,
											  buffer_entier_entree,
											  MIN_NB_ETAGE, MAX_NB_ETAGE));

	printf("Nombre etage : %u\n", nombreEtage);

	//libération de la mémoire
	free(buffer_string_entree);
	free(buffer_entier_entree);
	buffer_string_entree = NULL;
	buffer_entier_entree = NULL;

	//marquer en conversion explicite ?
	++nombreEtage;
	const size_t taille = nombreEtage * (nombreEtage - 1u) / 2u;
	unsigned int *tableau = (unsigned int *) calloc(taille,
																	sizeof(unsigned int));
	if(tableau){
		srand(time(NULL));
		plancheGalton(tableau, nombreBille, nombreEtage);
		afficher(tableau, taille);
		free(tableau);
		tableau = NULL;
	} else{
		free(tableau);
		tableau = NULL;
		printf("Erreur liee a l'allocation memoire...");
		exit(EXIT_FAILURE);
	}


	return EXIT_SUCCESS;
}

bool testerSaisieNumerique(const unsigned int valeur, char *buffer1, char *buffer2,
									const unsigned int min, const unsigned int max) {
	if (valeur > max || valeur < min || strcmp(buffer1, buffer2) != 0) {
		return false;
	}
	return true;
}

void plancheGalton(unsigned int *tab, unsigned int nombreBille,
						 unsigned int nombreEtage){

	tab[0] = nombreBille;
	size_t indice = 0u;

	for(size_t k = 0 ; k < nombreBille; ++k) {

		for (size_t l = 1; l < nombreEtage - 1u; ++l) {
			//50% de chance de sortir un 1 ou 0
			indice += l + (rand() & 1);
			tab[indice] += 1;
		}

		indice = 0u;
	}
}

void afficher(const unsigned int* adr, size_t n) {
	assert(adr != NULL);
	printf("[");
	for (size_t i = 0; i < n; ++i) {
		if (i > 0)
			printf(", ");
		printf("%d", *(adr + i));
	}
	printf("]\n");
}