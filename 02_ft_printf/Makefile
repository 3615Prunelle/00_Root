# All notes are now in the Makefile template
NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I ../98_include
LFLAGS = -L ../99_lib -lft

SRCS = 	ft_printf_common_specifiers.c \
		ft_printf_hexa_specifiers.c \
		ft_printf.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) install

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean all

install:
	cp ft_printf.h ../98_include
	cp libftprintf.a ../99_lib

.PHONY: all clean fclean re
