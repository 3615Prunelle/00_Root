NAME_SERVER = server
NAME_CLIENT = client

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I ./ft_printf -I ./libft
LFLAGS = -L ./ft_printf -lftprintf -L ./libft -lft

SRC_SERVER = 	minitalk_server.c \

SRC_CLIENT = 	minitalk_client.c \

OBJS_SERVER = $(SRC_SERVER:.c=.o)

OBJS_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) ./libft/libft.a ./ft_printf/libftprintf.a
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER) $(LFLAGS)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LFLAGS)

./libft/libft.a:
	$(MAKE) -C ./libft

./ft_printf/libftprintf.a:
	$(MAKE) -C ./ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
