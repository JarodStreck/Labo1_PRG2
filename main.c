/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : J. Streckeisen, A. Martins, G. Courbat
 Date creation  : 26.04.2022

 Description    : Ce programme permet de simuler une planche de Galton. On compte
                  combien de billes sont arrivées dans chaque récipient, ainsi
                  que combien d'entre elles sont passées à gauche ou à droite de
                  chaque clou. Finalement, on affiche un histogramme dont la
                  taille maximum est de 15 étoiles pour représenter la
                  distribution des billes. Au début du programme, la saisie est
                  contrôlée pour pouvoir rentrer uniquement des valeurs numériques.
                  Le programme se termine en affichant les deux affichages cités
                  ci-dessus.

 Remarque(s)    : - Toutes les saisies doivent être contrôlées et l'utilisateur sera
                    invité à refaire sa saisie.
                  - Le programme contient 2 affichages : L'affichage des valeurs
                    des divers compteurs et l'affichage d'un histogramme
                    correspondant à la distribution finale des billes dans les
                    récipients finaux.

 Compilateur    : Mingw-w64 gcc 11.2.0
 -----------------------------------------------------------------------------------
*/
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

const char MESSAGE_ERREUR[] = "Saisie incorrecte. Veuillez SVP recommencer.";
const char MESSAGE_ENTREE_BILLES[] = "Entrez le nombre de billes [1000 - 30000] : ";
const char MESSAGE_ENTREE_ETAGES[] = "Entrez le nombre de rangees de compteurs "
												 "[10-20] : ";
const char CARACTERE_HISTOGRAMME = '*';
const char CARACTERE_ESPACEMENT = ' ';

const unsigned NBRE_ELEMENTS = 512;
const unsigned TAILLE_ELEMENT = sizeof(char);
const unsigned TAILLE_TAMPON = NBRE_ELEMENTS * TAILLE_ELEMENT;

const unsigned MIN_NBRE_BILLES = 1000;
const unsigned MAX_NBRE_BILLES = 30000;
const unsigned MIN_NBRE_ETAGES = 10;
const unsigned MAX_NBRE_ETAGES = 20;
const unsigned TAILLE_MAX_HISTOGRAMME = 15;


bool testerSaisieNumerique(unsigned valeurATester, const char* tamponChaine,
									const char* tamponEntier, unsigned borneMin,
									unsigned borneMax);

void saisieUtilisateur(unsigned* valeur, unsigned borneMin, unsigned borneMax,
							  const char* messageEntre, const char* messageErreur,
							  char* tamponChaine, char* tamponEntier);

unsigned valeurMax(const unsigned* planche, unsigned nbreRangees,
						 unsigned tailleTotalePlanche);

unsigned longueurNumerique(unsigned valeur);

unsigned* plancheGalton(unsigned nbreBilles, unsigned nbreEtages,
								unsigned tailleTotalePlanche);

void afficherPlanche(const unsigned* planche, unsigned nbreEtages,
							unsigned tailleColonne);

unsigned* allouerHistogramme(const unsigned* planche, unsigned nbreRangees,
									  unsigned max, unsigned tailleTotalePlanche);

void afficherHistogramme(const unsigned* histogramme, unsigned nbreRangees,
								 unsigned tailleColonne);

int main(void) {

	srand((unsigned) time(NULL));

	unsigned nbreBilles = 0;
	unsigned nbreEtages = 0;

	/*
	 * Allocation de deux zones mémoires qui servira à stocker les entrées
	 * utilisateurs
	 */
	char* tamponChaineEntree = (char*) calloc(NBRE_ELEMENTS, TAILLE_ELEMENT);
	char* tamponEntierEntree = (char*) calloc(NBRE_ELEMENTS, TAILLE_ELEMENT);

	// On vérifie que la mémoire a bien été allouée
	assert(tamponChaineEntree != NULL);
	assert(tamponEntierEntree != NULL);

	// Saisie du nombre de billes
	saisieUtilisateur(&nbreBilles, MIN_NBRE_BILLES, MAX_NBRE_BILLES,
							MESSAGE_ENTREE_BILLES, MESSAGE_ERREUR, tamponChaineEntree,
							tamponEntierEntree);

	// On met à 0 tous les bits des deux zones tampons pour les réutiliser
	memset(tamponChaineEntree, 0, TAILLE_TAMPON);
	memset(tamponEntierEntree, 0, TAILLE_TAMPON);

	// Saisie du nombre d'étages
	saisieUtilisateur(&nbreEtages, MIN_NBRE_ETAGES, MAX_NBRE_ETAGES,
							MESSAGE_ENTREE_ETAGES, MESSAGE_ERREUR, tamponChaineEntree,
							tamponEntierEntree);

	// Libération de la mémoire
	free(tamponChaineEntree);
	free(tamponEntierEntree);
	tamponChaineEntree = NULL;
	tamponEntierEntree = NULL;

	unsigned tailleTotalePlanche = (nbreEtages + 1) * nbreEtages / 2;

	// Nombre de digits + 1 caractère pour l'espace
	unsigned tailleColonne = longueurNumerique(nbreBilles) + 1;

	// Allocation, puis simulation de la planche de Galton
	unsigned* planche = plancheGalton(nbreBilles, nbreEtages, tailleTotalePlanche);
	afficherPlanche(planche, nbreEtages, tailleColonne);

	unsigned* histogramme = allouerHistogramme(planche, nbreEtages,
															 valeurMax(planche, nbreEtages,
															 tailleTotalePlanche),
															 tailleTotalePlanche);

	afficherHistogramme(histogramme, nbreEtages, tailleColonne);

	// Libération de la mémoire
	free(histogramme);
	free(planche);
	histogramme = NULL;
	planche = NULL;

	return EXIT_SUCCESS;
}

// But : Tester qu'une saisie utilisateur est bien une valeurATester numérique valide
bool testerSaisieNumerique(unsigned valeurATester, const char* tamponChaine, const
                           char* tamponEntier, unsigned borneMin,
									unsigned borneMax) {

	assert(tamponChaine != NULL);
	assert(tamponEntier != NULL);

	if (valeurATester > borneMax || valeurATester < borneMin ||
		 strcmp(tamponEntier, tamponChaine) != 0) {

		return false;
	}
	return true;
}

// But : Permet de lire une saisie utilisateur
void saisieUtilisateur(unsigned* valeur, unsigned borneMin, unsigned borneMax,
							  const char messageEntre[], const char messageErreur[],
							  char* tamponChaine, char* tamponEntier) {

	assert(tamponChaine != NULL);
	assert(tamponEntier != NULL);

	do {
		printf("%s", messageEntre);
		scanf("%s", tamponChaine);
		//Récupération de l'entier
		sscanf(tamponChaine, "%u", valeur);
		//Transformation de l'entier en string
		sprintf(tamponEntier, "%u", *valeur);

		if (!testerSaisieNumerique(*valeur, tamponChaine, tamponEntier, borneMin,
											borneMax)) {

			printf("%s\n", messageErreur);
		}
	} while (!testerSaisieNumerique(*valeur, tamponChaine, tamponEntier, borneMin,
											  borneMax));
}

// But : Récupère la plus grande valeur présente dans la dernière ligne de la planche
unsigned valeurMax(const unsigned* planche, unsigned nbreRangees,
						 unsigned tailleTotalePlanche) {

	assert(planche != NULL);

	unsigned indice = tailleTotalePlanche - nbreRangees;
	unsigned max = *(planche + indice);

	for (unsigned i = 0; i < nbreRangees; ++i) {
		if (*(planche + indice + i) > max) {
			max = *(planche + indice + i);
		}
	}

	return max;
}

// But : Récupérer le nombre de chiffres dans un nombre
unsigned longueurNumerique(unsigned valeur) {

	unsigned i = 0;

	while (valeur != 0) {
		valeur /= 10;
		i++;
	}

	return i;
}

/*
 * But : Générer une planche pour l'expérience de Galton selon son nombre de
 * 		rangées et de billes
 */
unsigned* plancheGalton(unsigned nbreBilles, unsigned nbreEtages,
								unsigned tailleTotalePlanche) {

	assert(tailleTotalePlanche > 0);

	unsigned* planche = (unsigned*) calloc(tailleTotalePlanche, sizeof(unsigned));
	assert(planche != NULL);

	*(planche) = nbreBilles;
	unsigned indice = 0;

	for (unsigned i = 0; i < nbreBilles; ++i) {

		// Calcule de l'indice/parcourt de chaque bille sur la planche de Galton
		for (unsigned j = 1; j < nbreEtages; ++j) {

			// 50% de chance de sortir un 1 ou un 0 comme incrément pour l'indice
			indice += j + (rand() & 1);
			// Incrémente le compteur à l'indice donné
			*(planche + indice) += 1;
		}
		indice = 0;
	}

	return planche;
}

void afficherPlanche(const unsigned* planche, unsigned nbreEtages,
							unsigned tailleColonne) {

	assert(planche != NULL);

	// Nombre d'espaces à retirer à chaque étage
	unsigned decrement = tailleColonne / 2;

	/*
	 * Espaces à afficher à chaque étage, le nombre d'espaces varie en fonction de
	 * la parité du nombre de billes et du nombre d'étages
	 */
	unsigned nbreEspaces = tailleColonne * nbreEtages / 2 -
		      (decrement + tailleColonne % 2) + (tailleColonne % 2 && nbreEtages % 2);
	unsigned indice = 0;

	printf("\n");
	for (unsigned i = 0; i < nbreEtages; ++i) {

		printf("%*s", nbreEspaces, "");
		indice += i;
		for (unsigned j = indice; j <= indice + i; ++j) {
			printf("%*u", tailleColonne, *(planche + j));
		}

		/*
		 * Réduit le nombre d'espaces à afficher à la prochaine ligne. L'expression
		 * booléenne permet de calculer s'il faut ou non enlever une espace
		 * supplémentaire pour les lignes impaires dans une pyramide avec des
		 * rangées de taille paire.
		 */
		nbreEspaces -= decrement + (tailleColonne % 2 && i % 2);
		printf("\n");
	}
	printf("\n");
}

/*
 * But : Création d'un tableau contenant le nombre d'étoiles par rangée dans
 *       l'histogramme
 */
unsigned* allouerHistogramme(const unsigned* planche, unsigned nbreRangees,
									  unsigned max, unsigned tailleTotalePlanche) {

	assert(planche != NULL);

	unsigned* histogramme = (unsigned*) calloc(nbreRangees, sizeof(unsigned));
	assert(histogramme != NULL);

	unsigned indice = tailleTotalePlanche - nbreRangees;

	for (unsigned i = 0; i < nbreRangees; ++i) {
		*(histogramme + i) = (unsigned) round(TAILLE_MAX_HISTOGRAMME *
														  (double) *(planche + indice + i) / max);
	}

	return histogramme;
}

void afficherHistogramme(const unsigned* histogramme, unsigned nbreRangees,
								 unsigned tailleColonne) {

	assert(histogramme != NULL);

	for (unsigned i = TAILLE_MAX_HISTOGRAMME; i > 0; --i) {
		for (unsigned j = 0; j < nbreRangees; ++j) {
			if (i <= *(histogramme + j))
				printf("%*c", tailleColonne, CARACTERE_HISTOGRAMME);
			else
				printf("%*c", tailleColonne, CARACTERE_ESPACEMENT);
		}
		printf("\n");
	}
}


