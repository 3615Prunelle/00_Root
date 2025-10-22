/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_handler_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:58:15 by sophie            #+#    #+#             */
/*   Updated: 2025/08/22 17:15:41 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Je passe l'adresse de game dans la fonction appelante car je dois
// respecter le "void param" que mlx_key_hook me demande
// Variable move est utilisée dans la fonction target_position
// A chaque touche pressée, on check le nombre de collectibles restants
void	key_actions(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		move;

	game = param;
	move = 0;
	if (!game || !game->playr_img || game->playr_img->count < 1)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf(MSG_02);
		clean_and_exit(game);
	}
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		move = RIGHT;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		move = LEFT;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		move = UP;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		move = DOWN;
	if (!move)
		return ;
	move_player_logic(*game, move);
	move_player_graphic(game);
	delete_collectible_instance(game);
}

void	bonus_counter(t_game game, int step_counter)
{
	static mlx_image_t	*bonus_string1;
	static mlx_image_t	*bonus_string2;
	char				*string_to_display;
	char				*number_to_diplay;

	if (bonus_string1)
		mlx_delete_image(game.window, bonus_string1);
	if (bonus_string2)
		mlx_delete_image(game.window, bonus_string2);
	string_to_display = "Step counter";
	bonus_string1 = mlx_put_string(game.window, string_to_display, 50, 15);
	number_to_diplay = ft_itoa(step_counter);
	bonus_string2 = mlx_put_string(game.window, number_to_diplay, 100, 35);
	free(number_to_diplay);
}
