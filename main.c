/*-----------------------------------------------------------------------------------
Nom de fichier : main.cpp
Auteur : G. Courbat, J. Streckeisen, A. Martins
Date de création : 26.04.2022
Description :
Remarque :
Compilateur : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
const unsigned int MIN_NB_BILLE = 1000;
const unsigned int MAX_NB_BILLE = 30000;
const unsigned int MIN_NB_ETAGE = 10;
const unsigned int MAX_NB_ETAGE = 20;

bool testerSaisieNumerique(unsigned int valeur,unsigned int min,unsigned int max);

int main() {
   unsigned int nombreBille = 0;
   unsigned int nombreEtage = 0;

   do {
      printf("Entrez le nombre de billes [1000 - 30000] : ");
      scanf("%u%[0-9]",&nombreBille);
      if(!testerSaisieNumerique(nombreBille,MIN_NB_BILLE,MAX_NB_BILLE)){
         printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
      }
      fflush(stdin);
   }while(!testerSaisieNumerique(nombreBille,MIN_NB_BILLE,MAX_NB_BILLE));

   do{
      printf("Entrez le nombre de rangees de compteurs [10-20] : ");
      scanf("%u%[0-9]",&nombreEtage);
      if(!testerSaisieNumerique(nombreEtage,MIN_NB_ETAGE,MAX_NB_ETAGE)){
         printf("Saisie incorrecte. Veuillez SVP recommencer.\n");
      }
      fflush(stdin);
   }while(!testerSaisieNumerique(nombreEtage,MIN_NB_ETAGE,MAX_NB_ETAGE));

   printf("Nombre bille : %u \n",nombreBille);
   printf("Nombre etage : %u",nombreEtage);


   return 0;
}

bool testerSaisieNumerique(const unsigned int valeur,const unsigned int min,const
unsigned int max){
   if(valeur > max || valeur < min){
      return false;
   }
   return true;
}
