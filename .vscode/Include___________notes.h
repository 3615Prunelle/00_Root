// ⚪ Name of new library defined here (so we can use #include "current_project.h" header in every file)
#ifndef EXECUTABLE_H
# define EXECUTABLE_H

// ⚪ #define
# define ERROR_MESSSAGE_01	"Error\n"

/*
‼️ Si je mets des paths, mettre le chemin RELATIF depuis le dossier d'ou sera
lancée la commande. Ce chemin est différent selon si je suis :
- Sur mon PC perso
- Sur l'ordi du campus
ET selon si je :
- Fais 'make' depuis le dossier du projet (path from projet folder)
- Compile via VSCode (path from workspaceFolder)
*/

// ⚪ #include
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
//# include <string.h>
//# include <errno.h> ft_printf("Test errno : [%s]\n", strerror(errno));

// ⚪ Include from other projects (put relative path to avoid issues from home computer)
// ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json ou makefile
#include <libft.h>
#include <ft_printf.h>

// NOTE : mettre les dossiers 99 + 98 au lieu de ca ^ car ce projet dépend des .h + .a mais pas besoin du reste

// ⚪ Enums

// ⚪ Structs

// ⚪ Functions signatures - Part 1

// ⚪ Functions signatures - Part 2

// ⚪ Clean up functions

// ⚪ Test functions

#endif
