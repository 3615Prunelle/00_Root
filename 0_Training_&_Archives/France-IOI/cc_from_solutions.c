#include <stdio.h>

int main()
{
   // Caractères 0 à 127
   for (int lig = 0; lig < 16; lig = lig + 1)
   {
      for (int col = 0; col < 8; col = col + 1)
      {
         int code = 16 * col + lig;
         char caractere = (char)code;
         if (code < 32)
            caractere = ' ';
         printf("%04d %c  ", code, caractere);
      }
      printf("\n");
   }
}


/* #include <stdio.h>
#include <ctype.h>

typedef int bool;
#define true 1
#define false 0

int main()
{
	char lettre;
	scanf(" %c", &lettre); //l'espace avant %c est important, il permet d’ignorer les espaces, retours à la ligne, etc.
	printf("%s\n", islower(lettre) ? "Minuscule" : (isupper(lettre) ? "Majuscule" : "Pas une lettre"));
}
/* Opérateur ternaire :
(condition) ? valeur_si_vrai : valeur_si_faux;
*/
