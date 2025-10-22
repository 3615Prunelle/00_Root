# All notes are now in the Makefile template
# Bien penser à changer path des textures avant eval
NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I ../98_include
LFLAGS = -L ../99_lib -lmlx42 -lftprintf -lgetnextline -lglfw -lft #-lglfw goes with mlx42

SRCS = 	so_long_main_build.c \
		so_long_graphics.c \
		so_long_checkers.c \
		so_long_path_check.c \
		so_long_misc.c \
		so_long_handler_bonus.c \
		so_long_free_functions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

.PHONY: all clean fclean re
