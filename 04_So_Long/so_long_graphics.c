/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_graphics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:58:15 by sophie            #+#    #+#             */
/*   Updated: 2025/08/22 17:27:53 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Draw everything in correct order (ground then ICE then P)
// to avoid conflicts with depth
void	display_map(t_game *game)
{
	int	column;
	int	line;

	game->ground_image = path_to_image(game, game->window, PATH_GROUND);
	line = 0;
	while (line < game->max_lines)
	{
		column = 0;
		while (column < game->max_columns)
		{
			display_image(game, game->ground_image, column, line);
			column++;
		}
		line++;
	}
	game->wall_image = path_to_image(game, game->window, PATH_WALL);
	game->collec_img = path_to_image(game, game->window, PATH_COLLEC);
	game->escap_img = path_to_image(game, game->window, PATH_ESCAPE);
	add_wall_collectible_exit_images(game);
	add_player_image(game);
}

void	add_wall_collectible_exit_images(t_game *game)
{
	int	line;
	int	column;

	line = 0;
	while (line < game->max_lines)
	{
		column = 0;
		while (game->content[line][column] != '\n')
		{
			if (game->content[line][column] == '1')
				display_image(game, game->wall_image, column, line);
			else if (game->content[line][column] == 'C')
				display_image(game, game->collec_img, column, line);
			else if (game->content[line][column] == 'E')
				display_image(game, game->escap_img, column, line);
			column++;
		}
		line++;
	}
}

void	add_player_image(t_game *game)
{
	int	line;
	int	column;

	line = 0;
	while (line < game->max_lines)
	{
		column = 0;
		while (game->content[line][column] != '\n')
		{
			if (game->content[line][column] == 'P')
				display_image(game, game->playr_img, column, line);
			column++;
		}
		line++;
	}
}

// Affiche une instance de l'image. Peut être utilisé à
// chaque fois qu'on veut display l'image à un endroit différent
void	display_image(t_game *game, mlx_image_t *image, int column, int line)
{
	if (mlx_image_to_window(game->window, image, column * TILE_SIZE, line
			* TILE_SIZE) == -1)
	{
		ft_dprintf(2, "Error : [%s]\n", ERR_MSG_10);
		clean_and_exit(game);
	}
}

// Centraliser le process de chargement de textures +
// Conversion en image + Error handling + Deal with memory
// Step 1 : Set up Texture buffer (texture = Image pas encore
// affichée, mais prête à l’être)
// mlx_load_png(path) displays error message if fail, no need to do it
// Step 2 : Convert the texture to a diplayable image (= set up image buffer)
// Create a displayable image from texture data
// Free the texture as we don't need it anymore
mlx_image_t	*path_to_image(t_game *game, mlx_t *game_window, char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!(texture))
	{
		clean_and_exit(game);
	}
	image = mlx_texture_to_image(game_window, texture);
	if (!(image))
	{
		mlx_delete_texture(texture);
		clean_and_exit(game);
	}
	mlx_delete_texture(texture);
	return (image);
}
