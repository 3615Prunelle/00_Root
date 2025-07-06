#include "so_long.h"

/* Notes random
🔵 Si on veut qu'une struct soit MAJ en dehors d'une fonction, il faut obligatoirement passer un pointeur de
🔵 		cette struct (et vérifier que le pointeur est passé dans tous les fonctions appelantes en amont)
🟡 Callbsack function = Use the amount of parameters mentionned in the .h - If need more, use struct
🟢 Hooks allow you to add your own functions to the main loop execution of the program, aka these functions get executed every frame.
🟡 image->instances[0].x/y = Déplacer une image
🟣 mlx_image_t *img = mlx_new_image(mlx, 32, 32);		= Créer une image à partir de zéro
🟣 mlx_image_t *img = mlx_texture_to_image(mlx, tex);	= Créer une image à partir d’une texture existante
🔵 Ne jamais free() ce que MLX a donné
🔵 mlx_terminate() s’occupe de free tout ce qui vient de MLX
🟠 MLX42 ne supporte qu’un seul mlx_key_hook() à la fois. ✅ Solution : tout gérer dans une seule fonction de hook.
🟠 mlx_key_hook() déclenche une action quand une touche est pressée ou relâchée.
🟠 mlx_key_hook() appelle ma fonction key_actions (faite sur la base d'une callback function : mlx_keyfun) chaque fois qu’une touche est pressée.
‼️ MLX42 NB : 2 forbidden functions mlx_put_pixel  and mlx_resize_image

ft_printf("Error\n>> Please invite Diplo to the game !\n");
ft_printf("Error\n>> No friends allowed! Sorry-not-sorry\n");
ft_printf("Error\n>> Corn-Quest cancelled - No way to escape.\n");
ft_printf("Error\n>> Corn-Quest cancelled - Too many escapes.\n");
ft_printf("Error\n>> Corn-Quest cancelled - Nothing to collect !\n\n");

TO DO : Dans check everything, garder copie de game, et transformer les fonctions de vérif is_ en booleens
Ensuite, récupérer les tiles dans my_game qui sera utilisé pour le jeu (avec element_position - get_tile_position)
is_ = bool
get_ = récupérer un élément ou une position
‼️ Start with line 121
*/

int		main(int	argc, char **argv)
{
	char *path = PATH_MAP;									// changer pour argv[1] when done

	game	my_game;
	my_game = build_map(path);								// Création/Remplissage de la carte et affichage de la fenêtre de jeu (vide)

	if (!(check_everything(my_game)))						// Attention, on passe my_game donc une copie sera faite = aucune info ne reste
	{
		free_game_content_and_exit("Try again !\n", &my_game);				// ‼️‼️‼️ Check if memory leaks
		exit(1);
	}

	display_map(&my_game);												// Set up de l'affichage de la carte (real display dans mlx_loop)

	// Hook = Set up de fonction qui sera appelée par mlx_loop
	mlx_key_hook(my_game.window, key_actions, &my_game);					// Seule fonction pour interagir avec le jeu : key_actions
// ------------------------------------------------------------------------- Quit in a clean way when clic on cross. Check if MEM LEAKS ‼️
	mlx_close_hook(my_game.window, clean_and_exit, &my_game);

	mlx_loop(my_game.window);		// ‼️Keep at the end - Starts to render to window with all requested elements, until shutdown is requested

// ----------------------------------------------------------------------------------------------------------------------------------- Clean up ✅
	//clean_and_exit(stuff_to_free);			// In case ESC pressed or if everything goes correctly and the exit is naturally happening when all collectibles are reached ?
	free_game_content_and_exit("Pass in free_game_content_and_exit function\n", &my_game);
	return(0);
}

// ------------------------------------------------------- Game checklist - Create the required structure to store all the necessary information ✅
game	build_map(char *path)
{
	game		my_game;											// Solution badass pour passer toutes les infos en meme temps (FAB 4 PRESIDENT)
	char		*line_by_line;										// map[0] me donnait des segfaults donc je procede avec char *
	size_t		length_line;
// ---------------------------------------------------------------------------------------------------------- Edit from .txt to .ber & run tests ‼️
	int size_path = ft_strlen(path);
	char *extension = ft_substr(path, (size_path - 4), size_path);	// 🆓 Calloc done pour *extension

	if (ft_strncmp (extension, ft_strdup(".ber"), 5) != 0)			// ‼️ Malloc done on strdup mais return non stocké dans une variable - No need to free ?
		exit (1);

	free(extension);												// ✅ Free

	int	fd;
	fd = open(path, O_RDWR);

	if((!fd) || (fd < 0))
	{
		ft_printf ("Error\n>> Map missing OLALA NICHT GUT\n\n");
		exit (1);
	}
// ----------------------------------------------------------------------------------------- Deal with the map itself first / Get the size of it ✅
	line_by_line = get_next_line(fd);					// 🆓 GNL aloue la memoire a line_by_line
	if (!line_by_line)
	{
		free_gnl_stuff("Error\n>> Map empty or not displayable oO\n", &line_by_line, &fd);	// ✅ Free
	}
	length_line = ft_strlen(line_by_line);
	int line_counter = 0;
	while (line_by_line != NULL)
	{
		free(line_by_line);								// ✅ Free
		line_by_line = get_next_line(fd);				// 🆓 GNL aloue la memoire a line_by_line ✅ FREE right above
		line_counter++;
// ------------------------------------------------------------------------------------ Check if all lines are equal in size (= rectangular map) ✅
		if (((line_by_line != NULL)) && (ft_strlen(line_by_line) != length_line))
		{
			free_gnl_stuff("Error\n>> Sorry, your funky map isn't valid, please make it rectangular !\n", &line_by_line, &fd);	// ✅ Free
		}
	}
	if ((length_line < 4) || (line_counter < 3))	// Taille minimum pour avoir autre chose que des murs
	{
		free_gnl_stuff("Error\n>> Map too small, no space to play :(\n", &line_by_line, &fd);									// ✅ Free
	}
	close(fd);										// Sinon ne lira pas suite
// ---------------------------------------------------------------------------------------------------------------------- Alloc memory & fill it ✅
	my_game.content = ft_calloc((line_counter + 1), sizeof(char *));	// On alloue les lignes uniquement (colonnes done by GNL) ✅ FREE : In the last loop
	if (!my_game.content)
		exit(1);
	fd = open(PATH_MAP, O_RDWR);
	my_game.content[0] = get_next_line(fd);
	int i = 0;
	while (my_game.content[i] != NULL)
	{
		i++;
		my_game.content[i] = get_next_line(fd);							// Memoire allouee pour chaque ligne ✅ FREE in the loop at the end of the function
	}

	my_game.max_lines = line_counter;
	my_game.max_columns = length_line;

	my_game.escape_position = get_tile_position(my_game, ESCAPE);

	mlx_t	*game_window;
	if(!(game_window = mlx_init(TILE_SIZE*(my_game.max_columns-1), TILE_SIZE*my_game.max_lines, "Space Invader Diplo Corn Quest", false)))	// Connection to the graphical system - MLX MALLOC DONE HERE ‼️
	{
		free_game_content_and_exit("Error in the window allocation\n", &my_game);
		exit(1);
	}
// ‼️‼️‼️ Malloc on game_window - Set up mic_mac "stuff to free" struct or use game struct ?
	my_game.window = game_window;

	my_game.player_image = path_to_image(&my_game, my_game.window, PATH_PLAYER);
// ‼️‼️‼️ Malloc on player_image - Set up mic_mac "stuff to free" struct or use game struct ?

	return (my_game);
}
