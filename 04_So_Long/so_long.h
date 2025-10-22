/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:07:11 by schappuy          #+#    #+#             */
/*   Updated: 2025/09/23 17:59:05 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// Use other Makefile for evals (done - Same repo)

// ⚪ #define
// Paths to update depending on computer/tool - If Eval, use other Makefile
// Bien penser à changer path des textures avant eval

/*
// Below paths for VSCode debug from root repo
# define PATH_GROUND "./4_So_Long/textures/ic_Square_Purple.png"
# define PATH_WALL "./4_So_Long/textures/ic_Square_Black.png"
# define PATH_PLAYER "./4_So_Long/textures/ic_Player_Diplo.png"
# define PATH_COLLEC "./4_So_Long/textures/ic_Collectible_Corn.png"
# define PATH_ESCAPE "./4_So_Long/textures/ic_Escape_Scooter.png"
 */

# define PATH_GROUND "./textures/ic_Square_Purple.png"
# define PATH_WALL "./textures/ic_Square_Black.png"
# define PATH_PLAYER "./textures/ic_Player_Diplo.png"
# define PATH_COLLEC "./textures/ic_Collectible_Corn.png"
# define PATH_ESCAPE "./textures/ic_Escape_Scooter.png"

# define RIGHT 6
# define LEFT 4
# define UP 8
# define DOWN 2

// Used ASCII Values otherwise Norminette gives a false positive :
// "Preprocessor statement must only contain constant defines"
# define WALL 49			// ASCII for '1'
# define PLAYER 80			// ASCII for 'P'
# define COLLEC 67			// ASCII for 'C'
# define ESCAPE 69			// ASCII for 'E'
# define EMPTY_SPACE 48		// ASCII for '0'
# define CHECKED 86			// ASCII for 'V'

# define GAME_NAME "Space Invader Diplo Corn Quest"

# define MSG_01 "Check up done - You're good to play - Have fun !\n"
# define MSG_02 "Did you just dare press the escape key? Coward.\n"

# define ERR_MSG_01 "No map, no play !"
# define ERR_MSG_02 "Map file extension must be .ber"
# define ERR_MSG_03 "Map empty or not displayable"
# define ERR_MSG_04 "No funky map allowed (Check chars / walls position) !"
# define ERR_MSG_05 "Your artistic map isn't valid, it has to be rectangular !"
# define ERR_MSG_06 "Map too small, no space to play :( "
# define ERR_MSG_07 "Something is missing (Player / Collectible / Exit)"
# define ERR_MSG_08 "Too many ... - Pick & Choose : Players / Escapes"
# define ERR_MSG_09 "Error : [Looks like some elements can't be reached !]\n"
# define ERR_MSG_10 "Something went wrong with an image display"

# define TILE_SIZE 72

// ⚪ #include
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <MLX42.h>
// mettre les repos 99/98 au lieu des include

// ⚪ Structs
typedef struct node
{
	int			line;
	int			column;
}				t_tile;

typedef struct moves
{
	t_tile		up;
	t_tile		left;
	t_tile		down;
	t_tile		right;
}				t_four_moves;

typedef struct game
{
	int			max_lines;
	int			max_columns;
	char		**content;
	t_tile		escape_pos;
	mlx_t		*window;
	mlx_image_t	*ground_image;
	mlx_image_t	*wall_image;
	mlx_image_t	*playr_img;
	mlx_image_t	*collec_img;
	mlx_image_t	*escap_img;
	mlx_image_t	*bonus_string1;
	mlx_image_t	*bonus_string2;
}				t_game;

// ⚪ Pre launch check functions
int				check_input_get_fd(char *path);
void			get_map_size(int fd, t_game *game);
void			set_structs_pointers_to_null(t_game *game);
bool			check_everything(t_game *game);
bool			are_walls_approved(t_game game);
bool			are_chars_valid(t_game game);
bool			is_path_valid(t_tile player_pos, t_tile dest_pos,
					t_game game_copy, int tot_ctibles);
bool			path_pre_checks(t_game *game_copy, t_tile *player_pos);
t_four_moves	moves_options_set_up(t_tile player_pos);
bool			is_element(t_game *game, char element);
t_game			duplicate_game(t_game game);

// ⚪ Helpers
t_tile			get_tile_position(t_game game, char element);
t_tile			target_position(t_game game, int move);
bool			is_move_allowed(t_game game, t_tile target);
void			move_player_logic(t_game game, int move);
void			move_player_graphic(t_game *game);
int				get_collectibles_left(t_game game);
void			delete_collectible_instance(t_game *game);

// ⚪ MLX Helpers
t_game			build_map(int fd, char *path);
mlx_image_t		*path_to_image(t_game *game, mlx_t *game_window, char *path);
void			display_image(t_game *game, mlx_image_t *image, int column,
					int line);
void			display_map(t_game *game);
void			add_wall_collectible_exit_images(t_game *game);
void			add_player_image(t_game *game);
void			key_actions(mlx_key_data_t keydata, void *param);
void			bonus_counter(t_game game, int step_counter);

// ⚪ Clean up functions - So sort / merge / check / set up / delete
void			simple_print_exit(char *s);
void			free_logic_part(char *message, t_game *any_game);
void			free_gnl_return_and_exit(char *error_message, char **line,
					int *fd);
void			clean_and_exit(void *param);
#endif
