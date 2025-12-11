/*
L'idée : backtracking classique. Tu explores toutes les combinaisons possibles en avançant dans le tableau, tu ajoutes un élément à ton subset actuel, tu continues récursivement, et tu "reviens en arrière" pour tester d'autres chemins.
Le start évite les doublons (tu ne reviens jamais en arrière dans le tableau).
Le curr_sum est une optimisation pour éviter de calculer la somme à chaque fois.
Lance ça dans le debugger, mets des breakpoints dans find_subsets, et observe comment ça explore l'arbre des possibilités. C'est du DFS (depth-first search) sur l'espace des solutions.
*/

#include <stdlib.h>
#include <stdio.h>

void find_subsets(int *arr, int size, int target, int start, int *current, int curr_size, int curr_sum)
//						^--------^----------^--- all these values don't ever change
{
	if (curr_sum == target)
	{
		for (int i = 0; i < curr_size; i++)
		{
			printf("%d", current[i]);		// Prints ints from array (made of selection created below)
			fflush(NULL);
			if (i < curr_size - 1)			// Doesn't print last space
			{
				printf(" ");
				fflush(NULL);
			}
		}
		printf("\n");
		fflush(NULL);
	}

// La récursivité reprend au for car loop, donc se poursuit jusqu'à arriver à i < size
	for (int i = start; i < size; i++)		// Setting i as start, to check the right int in the initial array
	{
		if (curr_sum + arr[i] <= target)	// Checking sum
		{
			current[curr_size] = arr[i];	// Adding int in array bc sum not met
			find_subsets(arr, size, target, i + 1, current, curr_size + 1, curr_sum + arr[i]);		// Rec, changing only start and current size
//											  ^ start = index of array to write next number
		}
	}
}

int main(int ac, char **av) {
	if (ac < 2)
		return 0;

	int target = atoi(av[1]);
	int size = ac - 2;

	if (size == 0) {
		printf("\n");
		return 0;
	}

	int *arr = malloc(sizeof(int) * size);
	if (!arr)
		return 1;

	for (int i = 0; i < size; i++)
		arr[i] = atoi(av[i + 2]);

	int *current = malloc(sizeof(int) * size);
	if (!current) {
		free(arr);
		return 1;
	}

	find_subsets(arr, size, target, 0, current, 0, 0);

	free(arr);
	free(current);
	return 0;
}
