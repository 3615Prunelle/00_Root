/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_path_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:58:27 by sophie            #+#    #+#             */
/*   Updated: 2025/09/09 15:01:29 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Copie de la map pour eviter de mettre de changer quoi que
// ce que soit sur la map d'origine
// game_copy.content = NULL; car je ne peux pas return NULL
// Calloc toutes les lignes car on utilise pas GNL cette fois (sinon segfault)
t_game	duplicate_game(t_game game)
{
	t_game	game_copy;
	int		y;

	game_copy.max_columns = game.max_columns;
	game_copy.max_lines = game.max_lines;
	game_copy.content = ft_calloc(game.max_lines, sizeof(char *));
	if (!game_copy.content)
		game_copy.content = NULL;
	y = 0;
	while (y < game.max_lines)
	{
		game_copy.content[y] = ft_calloc(game.max_columns, sizeof(char));
		if (!game_copy.content[y])
			game_copy.content = NULL;
		game_copy.content[y] = ft_memcpy(game_copy.content[y], game.content[y],
				(size_t)game.max_columns);
		y++;
	}
	return (game_copy);
}

t_four_moves	moves_options_set_up(t_tile player_pos)
{
	t_four_moves	player_go;

	player_go.up.line = player_pos.line - 1;
	player_go.up.column = player_pos.column;
	player_go.left.line = player_pos.line;
	player_go.left.column = player_pos.column - 1;
	player_go.down.line = player_pos.line + 1;
	player_go.down.column = player_pos.column;
	player_go.right.line = player_pos.line;
	player_go.right.column = player_pos.column + 1;
	return (player_go);
}

bool	path_pre_checks(t_game *game_copy, t_tile *player_pos)
{
	char	tile;

	tile = (game_copy->content)[(player_pos)->line][(player_pos)->column];
	if ((player_pos->line < 0) || (player_pos->column < 0)
		|| (player_pos->line > game_copy->max_lines)
		|| (player_pos->column > game_copy->max_columns))
		return (false);
	if (tile == WALL)
		return (false);
	if (tile == CHECKED)
		return (false);
	return (true);
}

// Step 1 : Verifie que Player est dans le rectangle
// Step 2 : Vérif si player est sur la destination (= escape/collectible)
// Step 3 : Vérif si on est sur un mur
// Step 4 : Vérif si on est deja passé sur cette case
// Step 5 : Sauvegarder visite de la case (marquer un V)
bool	is_path_valid(t_tile player_pos, t_tile dest_pos, t_game game_copy,
		int tot_ctibles)
{
	static int		ctibles_counter;
	static int		escape_found;
	t_four_moves	player_go;

	if (!path_pre_checks(&game_copy, &player_pos))
		return (false);
	if ((game_copy.content)[(player_pos).line][(player_pos).column] == COLLEC)
		ctibles_counter++;
	if (player_pos.line == dest_pos.line
		&& (player_pos.column == dest_pos.column))
		escape_found = 1;
	(game_copy.content)[(player_pos).line][(player_pos).column] = CHECKED;
	if ((ctibles_counter == tot_ctibles) && (escape_found == 1))
		return (true);
	player_go = moves_options_set_up(player_pos);
	if (is_path_valid(player_go.up, dest_pos, game_copy, tot_ctibles))
		return (true);
	if (is_path_valid(player_go.left, dest_pos, game_copy, tot_ctibles))
		return (true);
	if (is_path_valid(player_go.down, dest_pos, game_copy, tot_ctibles))
		return (true);
	if (is_path_valid(player_go.right, dest_pos, game_copy, tot_ctibles))
		return (true);
	return (false);
}

// Return -1 si element not found - Utile pour debug
t_tile	get_tile_position(t_game game, char element)
{
	int		y;
	int		x;
	t_tile	element_position;

	y = 0;
	element_position.line = -1;
	element_position.column = -1;
	while (y < game.max_lines)
	{
		x = 0;
		while (x < game.max_columns)
		{
			if (game.content[y][x] == element)
			{
				element_position.line = y;
				element_position.column = x;
			}
			x++;
		}
		y++;
	}
	return (element_position);
}
