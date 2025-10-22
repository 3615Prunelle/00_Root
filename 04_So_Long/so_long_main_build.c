/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main_build.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schappuy <schappuy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 22:58:49 by sophie            #+#    #+#             */
/*   Updated: 2025/09/09 14:09:06 by schappuy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Copy paste the 3 lines below at beginning if evaluator
// complains about Valgrind output
// mlx_t *blabla = mlx_init(1000, 1000, GAME_NAME, true);
// mlx_terminate(blabla);
// exit(1);
// Fonction Build_map = Création/Remplissage de la carte et affichage de la
// fenêtre de jeu (vide) + upload/malloc image player
// display_map(&game); = Set up de l'affichage de la
// carte (real display dans mlx_loop)
// Hook = Set up de fonction qui sera appelée par mlx_loop
// Seule fonction pour interagir avec le jeu : key_actions
// mlx_close_hook = quitter le jeu via clic X
// mlx_loop(game.window); = Keep at the end - Starts to render the window
// with all requested elements, until shutdown is requested
int	main(int argc, char **argv)
{
	char	*path;
	int		fd;
	t_game	game;

	if (argc == 2)
	{
		path = argv[1];
		fd = check_input_get_fd(path);
		game = build_map(fd, path);
		display_map(&game);
		mlx_key_hook(game.window, key_actions, &game);
		mlx_close_hook(game.window, clean_and_exit, &game);
		ft_printf(MSG_01);
		mlx_loop(game.window);
		clean_and_exit(&game);
	}
	else if (argc < 2)
		ft_dprintf(2, "Error : [%s]\n", ERR_MSG_01);
	return (0);
}

int	check_input_get_fd(char *path)
{
	int		size_path;
	char	*extension;
	char	*compare;
	int		fd;

	size_path = ft_strlen(path);
	extension = ft_substr(path, (size_path - 4), size_path);
	compare = ft_strdup(".ber");
	if (ft_strncmp(extension, compare, 5) != 0)
	{
		free(extension);
		free(compare);
		simple_print_exit(ERR_MSG_02);
	}
	free(extension);
	free(compare);
	fd = open(path, O_RDWR);
	if ((!fd) || (fd < 0))
	{
		simple_print_exit(ERR_MSG_01);
	}
	return (fd);
}

// Set everything to null = éviter valeurs poubelle et
// segfaults quand passage dans free_logic_part
void	set_structs_pointers_to_null(t_game *game)
{
	game->ground_image = NULL;
	game->wall_image = NULL;
	game->playr_img = NULL;
	game->collec_img = NULL;
	game->escap_img = NULL;
	game->bonus_string1 = NULL;
	game->bonus_string2 = NULL;
	game->window = NULL;
}

// ft_strlen dans while loop = Check if all lines
//		are equal in size (= rectangular map)
// Last if = Taille minimum pour avoir autre chose que des
//		murs (not requested in subject, remove ?)
// close(fd); à la fin est important, sinon ne lira pas suite
void	get_map_size(int fd, t_game *game)
{
	size_t	length_line;
	int		line_counter;
	char	*gnl_line_return;

	line_counter = 0;
	gnl_line_return = get_next_line(fd);
	if (!gnl_line_return)
		free_gnl_return_and_exit(ERR_MSG_03, &gnl_line_return, &fd);
	length_line = ft_strlen(gnl_line_return);
	while (gnl_line_return != NULL)
	{
		free(gnl_line_return);
		gnl_line_return = get_next_line(fd);
		line_counter++;
		if ((gnl_line_return != NULL)
			&& (ft_strlen(gnl_line_return) != length_line))
			free_gnl_return_and_exit(ERR_MSG_05, &gnl_line_return, &fd);
	}
	if ((length_line < 4) || (line_counter < 3))
		free_gnl_return_and_exit(ERR_MSG_06, &gnl_line_return, &fd);
	game->max_lines = line_counter;
	game->max_columns = length_line;
	close(fd);
}

// On alloue manuellement la première colonne uniquement (lignes done by GNL)
// mlx_init = Connection to the graphical system - MLX MALLOC DONE HERE
// still reachable: 299,966 bytes in 3,312 blocks
// Investigated and normal if doesn't increase after
// Valgrind flag but normal (internal MLX42/GLFW allocation,
// can't be freed manually)
t_game	build_map(int fd, char *path)
{
	t_game	game;
	int		i;

	get_map_size(fd, &game);
	game.content = ft_calloc((game.max_lines + 1), sizeof(char *));
	if (!game.content)
		simple_print_exit(strerror(errno));
	fd = open(path, O_RDWR);
	game.content[0] = get_next_line(fd);
	i = 0;
	while (game.content[i] != NULL)
	{
		i++;
		game.content[i] = get_next_line(fd);
	}
	game.escape_pos = get_tile_position(game, ESCAPE);
	set_structs_pointers_to_null(&game);
	if (!(check_everything(&game)))
		clean_and_exit(&game);
	game.window = mlx_init(TILE_SIZE * (game.max_columns - 1),
			TILE_SIZE * game.max_lines, GAME_NAME, false);
	if (!(game.window))
		clean_and_exit(&game);
	game.playr_img = path_to_image(&game, game.window, PATH_PLAYER);
	return (game);
}
