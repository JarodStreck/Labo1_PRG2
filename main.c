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

const unsigned int NOMBRE_ELEMENT = 512;
const unsigned int TAILLE_ELEMENT = sizeof(char);
const unsigned int TAILLE_BUFFER = NOMBRE_ELEMENT*TAILLE_ELEMENT;

const unsigned int MIN_NB_BILLE = 1000;
const unsigned int MAX_NB_BILLE = 30000;
const unsigned int MIN_NB_ETAGE = 10;
const unsigned int MAX_NB_ETAGE = 20;
const unsigned TAILLE_HISTO = 15;

bool testerSaisieNumerique(const unsigned int valeur, const char *buffer1, const
                           char *buffer2, const unsigned int min,
                           const unsigned int max);

unsigned valeurMax(unsigned **compteurs, const unsigned rangee);
unsigned longueurNumerique(unsigned n);
unsigned** allocationPlanche(unsigned nbreRangees);
void libererMemoirePlanche(unsigned **planche, unsigned nbreRangees);
unsigned* allouerHistogramme(unsigned **compteurs, const unsigned rangee, unsigned
max);
void afficherHistogramme(unsigned *histogramme, unsigned rangee, unsigned
nombreChiffre);
void afficherCompteurs(unsigned **compteurs, const unsigned rangee, unsigned
nombreChiffres);



void plancheGalton(unsigned int *tab, unsigned nombreBille, unsigned int
nombreEtage);
void afficher(const unsigned int* adr, size_t n);

int main() {
	unsigned int nombreBille = 0;
	unsigned int nombreEtage = 0;

   //Allocation de deux zone mémoire qui servira a stocké les entrées utilisateur
	char *tamponChaineEntree = (char *) calloc(NOMBRE_ELEMENT,TAILLE_ELEMENT);
	char *tamponEntierEntree = (char *) calloc(NOMBRE_ELEMENT,TAILLE_ELEMENT);

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
		if (!testerSaisieNumerique(nombreBille, tamponChaineEntree,tamponEntierEntree,
                                 MIN_NB_BILLE,MAX_NB_BILLE)) {
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

bool testerSaisieNumerique(const unsigned int valeur, const char *buffer1, const
char
*buffer2,
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

unsigned** allocationPlanche(unsigned nbreRangees) {

   unsigned **planche = (unsigned **) calloc(nbreRangees, sizeof(unsigned **));
   assert(planche != NULL);

   for (unsigned i = 0; i < nbreRangees; ++i) {
      planche[i] = (unsigned *) calloc(i + 1, sizeof(unsigned *));

      assert(planche[i] != NULL);
   }

   return planche;
}

void libererMemoirePlanche(unsigned **planche, unsigned nbreRangees) {

   assert(planche != NULL);

   for (unsigned i = 0; i < nbreRangees; ++i) {
      assert(planche[i] != NULL);
      free(planche[i]);
      planche[i] = NULL;
   }

   free(planche);
   planche = NULL;
}

unsigned valeurMax(unsigned **compteurs, const unsigned rangee) {
   unsigned max = *(*(compteurs + rangee - 1));

   for (unsigned i = 0; i < rangee; ++i) {
      if (*(*(compteurs + rangee - 1) + i) > max)
         max = *(*(compteurs + rangee - 1) + i);
   }
   return max;
}

unsigned* allouerHistogramme(unsigned **compteurs, const unsigned rangee, unsigned
max) {
   unsigned *histogramme;

   histogramme = (unsigned *) calloc(rangee, sizeof(unsigned));

   for (unsigned i = 0; i < rangee; ++i) {
      *(histogramme + i) = (unsigned) (TAILLE_HISTO * (double) (*(*(compteurs + rangee - 1) + i)) / max);
   }
   return histogramme;
}

void afficherHistogramme(unsigned *histogramme, unsigned rangee, unsigned nombreChiffre) {
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

unsigned longueurNumerique(unsigned n) {
   unsigned i = 0;

   while (n != 0) {
      n /= 10;
      i++;
   }
   return i;
}

void afficherCompteurs(unsigned **compteurs, const unsigned rangee, unsigned nombreChiffres) {


   unsigned decrement = nombreChiffres / 2;
   unsigned espace = nombreChiffres * rangee / 2 - (decrement + nombreChiffres % 2);

   for (unsigned i = 0; i < rangee; i++) {
      printf("%*s", espace, "");

      for (unsigned j = 0; j <= i; j++) {
         printf("% *u", nombreChiffres, *(*(compteurs + i) + j));
      }
      espace -= decrement + (nombreChiffres % 2 && i % 2);
      printf("\n");
   }
}