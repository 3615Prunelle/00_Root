# Makefile pour Eval (l'original a été backup)
NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I ./libft -I ./ft_printf
LFLAGS = -L ./libft -L ./ft_printf -lftprintf -lft

SRCS = 	push_swap_main.c \
		push_swap_input_management.c \
		push_swap_check_and_exit.c \
		push_swap_operations.c \
		push_swap_lst_functions.c \
		push_swap_algorithms.c \
		push_swap_tools.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# Ajouté les deux libs en dépendance de $(NAME) plutôt que des règles pour éviter relink
$(NAME): $(OBJS) ./libft/libft.a ./ft_printf/libftprintf.a
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

./libft/libft.a:
	$(MAKE) -C ./libft

./ft_printf/libftprintf.a:
	$(MAKE) -C ./ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

# Ajouté des commandes pour que fclean nettoie les sous dossiers
fclean: clean
	rm -f $(NAME)
	rm -f a.out
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
