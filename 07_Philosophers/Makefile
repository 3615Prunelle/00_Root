NAME = philo

CC = cc

CFLAGS = -g -pthread -Wall -Wextra -Werror

# Flags de linking - No need here
LFLAGS =

SRCS =	philo_main.c \
		philo_setup.c \
		philo_routines.c \
		philo_helpers.c \
		philo_actions.c \
		philo_mutex.c

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
