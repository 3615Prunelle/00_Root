# Makefile pour Eval (l'original a été backup)
# Si soucis de compil pour l'éval, make sure que l'ordi sur lequel a été cloné mon repo ait ces libs :
# sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
# Bien penser à changer path des textures avant eval
NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I ./get_next_line -I ./ft_printf -I ./MLX42/include/MLX42 -I ./libft
LFLAGS = -L ./get_next_line -L ./ft_printf -L ./MLX42/build -L ./libft -lmlx42 -lgetnextline -lftprintf -lglfw -lft #-lglfw goes with mlx42

SRCS = 	so_long_main_build.c \
		so_long_graphics.c \
		so_long_checkers.c \
		so_long_path_check.c \
		so_long_misc.c \
		so_long_handler_bonus.c \
		so_long_free_functions.c

OBJS = $(SRCS:.c=.o)

# Toutes les libs utilisées pour ce projet
MLX42_LIB = ./MLX42/build/libmlx42.a
LIBFT_LIB = ./libft/libft.a
PRINTF_LIB = ./ft_printf/libftprintf.a
GNL_LIB = ./get_next_line/libgetnextline.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX42_LIB) $(LIBFT_LIB) $(PRINTF_LIB) $(GNL_LIB)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

# Dependency of MLX42 to create the .o, otherwise MLX header is not found during compilation
# Trick CMakeLists.txt pour éviter soucis de timestamp / relinks
%.o: %.c ./MLX42/CMakeLists.txt
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour cloner ET compiler MLX42
$(MLX42_LIB): ./MLX42
	@echo "Building MLX42..."
	@cd ./MLX42 && cmake -B build && cmake --build build -j4

# Règle pour cloner MLX42 si le dossier n'existe pas
./MLX42:
	@echo "Cloning MLX42..."
	@git clone https://github.com/codam-coding-college/MLX42.git

# CMakeLists.txt est créé automatiquement quand MLX42 est cloné
./MLX42/CMakeLists.txt: ./MLX42

$(LIBFT_LIB):
	$(MAKE) -C ./libft

$(PRINTF_LIB):
	$(MAKE) -C ./ft_printf

$(GNL_LIB):
	$(MAKE) -C ./get_next_line

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f a.out
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean
	$(MAKE) -C ./get_next_line fclean
	rm -rf ./MLX42

re: fclean all

.PHONY: all clean fclean re
