/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/05/12 20:20:14 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ⚪ Name of new library defined here (so we can use #include "current_ft.h")
#ifndef SO_LONG_H
# define SO_LONG_H

// ⚪ All #define can be placed only here
# define PATH "4_So_Long/test_map.txt"
# define RIGHT	6									// !! Change that before eval, so the keys are the same as requested in the subject
# define LEFT	4
# define UP		8
# define DOWN	2
# define PLAYER_POSITION			my_game.content[player.line][player.column]
# define GET_TILE(MAP, ELEMENT)		(MAP)[(ELEMENT).line][(ELEMENT).column] // remplace tous les autres - Penser a update
# define TARGET_POSITION			my_game.content[target.line][target.column]
# define EXIT_POSITION				my_game.content[exit.line][exit.column]
# define MAP_SIZE					my_game.content[my_game.max_lines][my_game.max_columns]
# define PLA "🦕"
# define COL "🌽"
# define EXI "🛴"
# define WAL "🟩"
# define EMP "⬛"
# define WALL			'1'
# define PLAYER			'P'
# define COLLECTIBLE	'C'
# define EXIT			'E'
# define EMPTY_SPACE	'0'
# define VISITAY		'V'

// ⚪ MLX42 related #define
# define TILE_SIZE 32

// ⚪ All #include only here (put #include "current_ft.h" is in each file)
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# include <MLX42/MLX42.h>			// Let's get it started with the MLX42

// ⚪ Include from other projects (put relative path to avoid issues from home computer)
// ‼️ ‼️ ‼️ Mettre les.h ici + ‼️ Compiler et ajouter la ligne "-l[libname without the lib]" au dessus de "-lgetnextline" dans tasks.json
#include "../1_Libft/libft.h"
#include "../2_ft_printf/ft_printf.h"
#include "../3_Get_Next_Line/get_next_line.h"

// ⚪ Non-MLX42 structs
typedef struct node
{
	int		line;
	int		column;
} tile;

typedef struct game
{
	int		max_lines;
	int		max_columns;
	char	**content;
} game;

// ⚪ My MLX42 structs
typedef struct mic_mac		// Struct to pass many arguments to a function that can't be called twice or can only take a limited amount of arguments
{
	mlx_t			*window;
	/* Add all the stuff to free mlx + not-mlx part (in main + all the other functions) */
	mlx_texture_t	*player_texture;
	mlx_texture_t	*collec_texture;
	mlx_texture_t	*exit_texture;
	mlx_texture_t	*ground_texture;
	mlx_texture_t	*wall_texture;
	mlx_image_t		*player_image;
	// game	my_game;								// ‼️‼️‼️ Uncomment when previous code is connected to the MLX42 part
	// anything else added here needs to be added everywhere (initialised where needed + added in the free function)

} all_mallocs;

// ⚪ Main Function
char	**so_long(int fd);

// ⚪ Helpers
tile	player_move(game my_game, tile player, tile exit);
tile	check_target(game my_game, tile player, tile target);

int		check_everything(game my_game);
int		check_walls(game my_game);
tile	is_player(game my_game);
int		is_collec(game my_game, tile player, bool in_game_loop);
tile	is_exit(game my_game);

game	duplicate_game(game my_game);
bool	is_path_valid(tile player, tile destination, game my_game_copy, int *total_collectibles);

void	free_game(game *any);
void	free_gnl_stuff(char **line, int *fd);
void	print_map(game my_game);
void	print_map_fun(game my_game);

// ⚪ MLX Helpers
void			ft_clic_exit(void *param); // model = mlx_closefunc
void			ft_key_move(mlx_key_data_t keydata, void *param);
mlx_texture_t	*ft_check_texture(all_mallocs *stuff_to_free, const char *path);
void			ft_free_exit(all_mallocs *free_this);

#endif
