# include <stdio.h>

void debutFin(int nbAffichages)
{
   printf("début %d\n", nbAffichages);
   if (nbAffichages > 1)
   {
      debutFin(nbAffichages - 1);
      debutFin(nbAffichages - 1);
   }
   printf("fin %d\n", nbAffichages);
}

int main()
{
   debutFin(3);
   return 0;
}
