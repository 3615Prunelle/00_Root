/*
Le plan :
Calcule le minimum de parenthèses à virer : compte les ')' sans '(' correspondante + les '(' qui restent orphelines
Génère toutes les combinaisons : à chaque parenthèse, tu testes 2 choix (garder ou remplacer par espace)
Filtre : garde seulement celles qui sont valides ET qui enlèvent exactement le minimum
Déduplique avec solution_exists

C'est du brute force avec pruning. Dans le debugger, regarde comment find_solutions explore l'arbre binaire des choix (keep/remove à chaque position).
Le min_remove évite de générer des solutions inutiles.
Attention : strdup n'est pas dans les allowed functions, faudra peut-être l'implémenter toi-même. Remplace par un malloc + strcpy si besoin.
*/


#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int is_valid(char *s) {
	int balance = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] == '(')
			balance++;
		else if (s[i] == ')')
			balance--;
		if (balance < 0)
			return 0;
	}
	return balance == 0;
}

void print_solution(char *s) {
	for (int i = 0; s[i]; i++)
		write(1, &s[i], 1);
	write(1, "\n", 1);
}

int count_removed(char *s, char *original) {
	int count = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] == ' ' && original[i] != ' ')
			count++;
	}
	return count;
}

int solution_exists(char **solutions, int count, char *new_sol) {
	for (int i = 0; i < count; i++) {
		if (strcmp(solutions[i], new_sol) == 0)
			return 1;
	}
	return 0;
}

void find_solutions(char *s, char *original, int pos, int min_remove, char **solutions, int *sol_count) {
	if (pos == strlen(original)) {
		if (is_valid(s) && count_removed(s, original) == min_remove) {
			if (!solution_exists(solutions, *sol_count, s)) {
				solutions[*sol_count] = strdup(s);
				(*sol_count)++;
			}
		}
		return;
	}

	if (original[pos] != '(' && original[pos] != ')') {
		s[pos] = original[pos];
		find_solutions(s, original, pos + 1, min_remove, solutions, sol_count);
		return;
	}

	// Keep the parenthesis
	s[pos] = original[pos];
	find_solutions(s, original, pos + 1, min_remove, solutions, sol_count);

	// Remove it (replace with space)
	s[pos] = ' ';
	find_solutions(s, original, pos + 1, min_remove, solutions, sol_count);
}

int calculate_min_remove(char *s) {
	int balance = 0;
	int to_remove = 0;

	for (int i = 0; s[i]; i++) {
		if (s[i] == '(')
			balance++;
		else if (s[i] == ')') {
			if (balance > 0)
				balance--;
			else
				to_remove++;
		}
	}
	return to_remove + balance;
}

int main(int ac, char **av) {
	if (ac != 2)
		return 0;

	char *input = av[1];
	int len = strlen(input);
	char *temp = malloc(len + 1);
	if (!temp)
		return 1;

	int min_remove = calculate_min_remove(input);

	char **solutions = malloc(sizeof(char *) * 10000);
	if (!solutions) {
		free(temp);
		return 1;
	}

	int sol_count = 0;
	strcpy(temp, input);
	find_solutions(temp, input, 0, min_remove, solutions, &sol_count);

	for (int i = 0; i < sol_count; i++) {
		print_solution(solutions[i]);
		free(solutions[i]);
	}

	free(solutions);
	free(temp);
	return 0;
}
