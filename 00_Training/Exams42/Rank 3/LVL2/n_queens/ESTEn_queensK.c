#include <stdio.h>
#include <stdlib.h>

// board[2] = 3 means that on column 2, queen is on line 3

int	is_safe(int *board, int line, int col) // Savoir si on peut placer une reine à (line, col).
{
	int	i = 0;

	while (i < col)							// On regarde toutes les colonnes avant col, de la meme ligne
											// Pourquoi seulement avant ? Parce qu'on remplit de gauche à droite, donc les colonnes après sont encore vides.
	{
		// Vérifs :
		if (board[i] == line || /* La reine en colonne i est-elle sur la même ligne que celle qu'on veut placer ? */
			board[i] - line == i - col || /* Diagonale descendante (↘). Si deux cases sont sur cette diagonale, la différence ligne - colonne est la même.
												Exemple : (0,0) et (2,2) → 0-0 = 0 et 2-2 = 0 ✓ même diagonale */
			board[i] - line == col - i) /* Diagonale montante (↗). Si deux cases sont sur cette diagonale, la somme ligne + colonne est la même (ou équivalent : ligne - (-colonne)).
												Exemple : (0,3) et (2,1) → 0+3 = 3 et 2+1 = 3 ✓ même diagonale */
			// Si une des 3 conditions est vraie, on retourne 0 (pas safe). Sinon on retourne 1.
			return (0);
		i++;
	}
	return (1);			// Safe to place
}

void	solve(int *board, int col, int n)
{
// board : ton échiquier actuel
// col : la colonne qu'on est en train de traiter maintenant
// n : la taille de l'échiquier
	int	i = 0;
	if (col == n)			// Solution found = placé une reine dans toutes les colonnes - Print & leave
	{
		while (i < n)
		{
			printf("%d", board[i]);
			if (i < n - 1)
				printf(" ");
			i++;
		}
		printf("\n");
		return ;
	}
	int	line = 0;
	while (line < n)			// Check ligne par ligne
	{
		// Pour la colonne actuelle col, on essaie toutes les lignes possibles (de 0 à n-1)
		if (is_safe(board, line, col))			// = est-ce que je peux placer une reine à la ligne line, colonne col ?
		{
			board[col] = line;					// Si oui : board[col] = row → je place la reine + go direct colomne suivante car
												//			ca ne sert a rien de continuer sur cette colonne si une reine y a été placée
			solve(board, col + 1, n);			// Appelle récursivement pour la colonne suivante
		}
		line++;									// Quand la récursion revient, on essaie la ligne suivante
												// Point clé : quand la récursion revient, le line++ fait qu'on essaie automatiquement une autre ligne.
												// Pas besoin de "défaire" explicitement, parce que le prochain essai va écraser la valeur dans board[col].
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	n = atoi(argv[1]);
	if (n <= 0)
		return (1);
	int	*board = calloc(n, sizeof(int));
	// board[2] = 3 means that on column 2, queen is on line 3
	// on ne peut avoir qu'une seule reine par colonne = un tableau 1D suffit.
	if (!board)
		return (1);
	// On lance la recherche en commençant par la colonne 0.
	solve(board, 0, n);
	free(board);
	return (0);
}
