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
#define  BUFFER_SIZE  10 * sizeof(char)
const unsigned int MIN_NB_BILLE = 1000;
const unsigned int MAX_NB_BILLE = 30000;
const unsigned int MIN_NB_ETAGE = 10;
const unsigned int MAX_NB_ETAGE = 20;

bool testerSaisieNumerique(const unsigned int valeur, char* buffer1, char* buffer2,
                           const unsigned int min, const unsigned int max);

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
                                 buffer_entier_entree,MIN_NB_BILLE,
                                 MAX_NB_BILLE)) {
         printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
      }
   } while (!testerSaisieNumerique(nombreBille,buffer_entier_entree,
                                   buffer_string_entree, MIN_NB_BILLE,
                                   MAX_NB_BILLE));
   printf("Nombre bille : %u \n", nombreBille);

   memset(buffer_string_entree,0,BUFFER_SIZE);
   memset(buffer_entier_entree,0,BUFFER_SIZE);


   do {
       printf("Entrez le nombre de rangees de compteurs [10-20] : ");

      scanf("%s", buffer_string_entree);
      sscanf(buffer_string_entree, "%u", &nombreEtage);
      sprintf(buffer_entier_entree, "%u", nombreEtage);
       if (!testerSaisieNumerique(nombreEtage,buffer_string_entree,
                                  buffer_entier_entree, MIN_NB_ETAGE,
                                  MAX_NB_ETAGE)) {
          printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
       }
    } while (!testerSaisieNumerique(nombreEtage,buffer_string_entree,
                                    buffer_entier_entree ,
                                    MIN_NB_ETAGE, MAX_NB_ETAGE));

   printf("Nombre etage : %u", nombreEtage);

   //libération de la mémoire
   free(buffer_string_entree);
   free(buffer_entier_entree);
   buffer_string_entree = NULL;
   buffer_entier_entree = NULL;
   return 0;
}

bool testerSaisieNumerique(unsigned int valeur, char *buffer1, char *buffer2,
                           const unsigned int min, const unsigned int max) {
   if (valeur > max || valeur < min || strcmp(buffer1,buffer2) != 0) {
      return false;
   }
   return true;
}
