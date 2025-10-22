# All notes are now in the Makefile template
NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I.

SRCS =	ft_itoa.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_calloc.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
