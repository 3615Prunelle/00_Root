# Modifs de config pour évals :

# Créer un dossier par librairie, dans le projet actuel, et y placer :
#		La sélection de fonctions utilisées (ou tout mettre si flemme) - ATTENTION : si ft_printf, bien penser a mettre celles de libft necessaires pour ft_printf
#		Son Makefile
#		Son .h
# Updater le Makefile de chaque librairie (fonctions, bonus, règles etc si nécessaire)
# Les .h peuvent etre les laisses comme tels, pas besoin d’enlever les lignes des fonctions pas utilisees
# Dans le Makefile du projet, créer une target (par librairie) pour compiler les librairies nécessaires au projet
# ATTENTION - Faire une target (relative path de l'executable) et pas une règle pour éviter problèmes de relink
# Mettre cette target comme dépendance dans le script qui va compiler mon projet actuel
# Mettre le dossier où se trouvent les .h et .a dans les flags de compilation de mon projet actuel
# Ajouter des commandes pour que fclean nettoie aussi les sous dossiers

# Rephrasing Important : Ajouter les libs en dépendance de $(NAME) plutôt que des règles pour éviter relink
# $(MAKE) est une variable fournie automatiquement par le programme make (pas besoin de la créer) - Voir Makefile Eval de Push-Swap
# -C (= Change directory) est un flag de make, qui équivaut à :
# "Va dans ce dossier, exécute le Makefile qui est dedans, puis reviens au dossier courant”

# Notes generales MakeFile :

# NB :	Makefiles must be indented using TABs and not spaces (or make will fail)
#		On déclare en premier toutes les variables dont make aura besoin pour compiler
#		Puis on définit des règles (actions) qui utilisent ces variables et éventuellement d'autres règles
#		Puis on définit les scripts à exécuter par ces règles (qui incluent eux même des variables et des commandes)
#		Je peux donner les noms que je veux aux variables et aux règles
#		Les règles clean, fclean, re et .PHONY doivent toujours être présentes
#		Les règles sont appelées par make (I chose wich one, default is first one)
# VERY IMPORTANT : Vérifier l'ordre des flags/élements dans les commandes est très important et peut
#	générer des grosses erreurs à la compilation même si juste 2 éléments sont inversés
#	Par exemple, les objets doivent toujours précéder les -l pour que le linker voie ce qui doit être résolu.
#		$() or ${} are used to refer to a variable

NAME = philo

CC = cc

CFLAGS = -g -pthread -Wall -Wextra -Werror

# Flags de linking - No need here ?
LFLAGS =

SRCS =	philo_main.c \
		philo_routines.c \
		philo_helpers.c \
		philo_actions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
