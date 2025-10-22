/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:59:00 by sophie            #+#    #+#             */
/*   Updated: 2025/08/22 18:15:21 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Only the target reference is updated, not the player one (yet)
t_tile	target_position(t_game game, int move)
{
	t_tile	target;
	t_tile	player;

	player = get_tile_position(game, PLAYER);
	if (move == RIGHT)
	{
		target.line = player.line;
		target.column = player.column + 1;
	}
	else if (move == LEFT)
	{
		target.line = player.line;
		target.column = player.column - 1;
	}
	else if (move == UP)
	{
		target.line = player.line - 1;
		target.column = player.column;
	}
	else
	{
		target.line = player.line + 1;
		target.column = player.column;
	}
	return (target);
}

// Vérifier chaque possibilité de mouvement
// Create counter
// Update de la position du player
void	move_player_logic(t_game game, int move)
{
	static int	step_counter;
	t_tile		player;
	t_tile		target;

	player = get_tile_position(game, PLAYER);
	target = target_position(game, move);
	if (is_move_allowed(game, target))
	{
		game.content[target.line][target.column] = 'P';
		if ((player.column == game.escape_pos.column)
			&& (player.line == game.escape_pos.line))
			game.content[player.line][player.column] = 'E';
		else
			game.content[player.line][player.column] = '0';
		player.line = target.line;
		player.column = target.column;
		step_counter++;
		bonus_counter(game, step_counter);
		return ;
	}
	return ;
}

// Updated_player_pos sera -1 si P est sur la sortie
// et qu'il veut bouger dans un mur
// Si pas -1 : Déplacement de l'image en prenant en compte l'échelle du jeu
// 1 case (dans représentation non graphique) = 72 pixels (rep visuelle)
// Else{} is to update position player (sinon -1 = segfault)
void	move_player_graphic(t_game *game)
{
	t_tile	updated_player_pos;

	updated_player_pos = get_tile_position(*game, PLAYER);
	if (updated_player_pos.column != -1)
	{
		game->playr_img->instances[0].x = updated_player_pos.column * TILE_SIZE;
		game->playr_img->instances[0].y = updated_player_pos.line * TILE_SIZE;
	}
	else
	{
		game->content[game->escape_pos.line][game->escape_pos.column] = PLAYER;
	}
}

bool	is_move_allowed(t_game game, t_tile target)
{
	char	char_on_target;

	char_on_target = game.content[target.line][target.column];
	if (char_on_target == '0' || char_on_target == 'C' || char_on_target == 'E')
	{
		return (true);
	}
	return (false);
}

// While loop : If on collectible : delete collectible instance
// If : if on escape + collectibles fetched : exit game
void	delete_collectible_instance(t_game *game)
{
	size_t	i;
	int		ctibles_amount;

	i = 0;
	ctibles_amount = get_collectibles_left(*game);
	while (i < game->collec_img->count)
	{
		if (game->playr_img->instances[0].x == game->collec_img->instances[i].x
			&& game->playr_img->instances[0].y
			== game->collec_img->instances[i].y)
			game->collec_img->instances[i].enabled = false;
		i++;
	}
	if (ctibles_amount == 0)
	{
		if (game->playr_img->instances[0].x == game->escap_img->instances[0].x
			&& game->playr_img->instances[0].y
			== game->escap_img->instances[0].y)
		{
			game->escap_img->instances[0].enabled = false;
			mlx_close_window(game->window);
		}
		i++;
	}
}
