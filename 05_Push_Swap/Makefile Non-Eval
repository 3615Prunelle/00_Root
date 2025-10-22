# All notes are now in the Makefile template

# PDF Instructions part : If your project allows you to use your libft,
# you must copy its sources and its associated Makefile into a libft folder.
# Your project’s Makefile must compile the library by using its Makefile, then compile the project.

NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I ../98_include
LFLAGS = -L ../99_lib -lftprintf -lft

SRCS = 	push_swap_main.c \
		push_swap_input_management.c \
		push_swap_check_and_exit.c \
		push_swap_operations.c \
		push_swap_lst_functions.c \
		push_swap_algorithms.c \
		push_swap_tools.c

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
