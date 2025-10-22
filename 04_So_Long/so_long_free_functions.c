/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_free_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sophie <sophie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:58:34 by sophie            #+#    #+#             */
/*   Updated: 2025/08/22 17:27:53 by sophie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	simple_print_exit(char *s)
{
	ft_dprintf(2, "Error : [%s]\n", s);
	exit(1);
}

// char **line etant l'adresse d'un pointeur, char *line est
// donc un pointeur, qu'on doit free puis remettre a zero
// close(*fd); Dereference le pointeur vers fd pour le fermer
// NB : Fermer un fd est important pour eviter les fd leaks
// A la fin, on force GNL avec une valeur neg pour libérer son static buffer
void	free_gnl_return_and_exit(char *error_message, char **line, int *fd)
{
	ft_dprintf(2, "Error : [%s]\n", error_message);
	free(*line);
	*line = NULL;
	close(*fd);
	get_next_line(-1);
	exit(1);
}

// Free toutes les lignes de content
void	free_logic_part(char *message, t_game *any_game)
{
	ft_dprintf(2, "%s", message);
	while (any_game->max_lines > 0)
	{
		free(any_game->content[any_game->max_lines - 1]);
		any_game->max_lines--;
	}
	if (any_game->content)
	{
		free(any_game->content);
	}
}

// Free everything MLX42 related when exit game
void	clean_and_exit(void *param)
{
	t_game	*game;

	game = param;
	if (!game)
		return ;
	if (game->ground_image)
		mlx_delete_image(game->window, game->ground_image);
	if (game->wall_image)
		mlx_delete_image(game->window, game->wall_image);
	if (game->playr_img)
		mlx_delete_image(game->window, game->playr_img);
	if (game->collec_img)
		mlx_delete_image(game->window, game->collec_img);
	if (game->escap_img)
		mlx_delete_image(game->window, game->escap_img);
	if (game->bonus_string1)
		mlx_delete_image(game->window, game->bonus_string1);
	if (game->bonus_string2)
		mlx_delete_image(game->window, game->bonus_string2);
	if (game->window)
		mlx_terminate(game->window);
	free_logic_part("", game);
	exit(1);
}
