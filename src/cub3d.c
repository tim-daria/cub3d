/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:39:58 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/13 19:55:43 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Cleans up resources and terminates the program properly
// int	end_program(t_mlx_data *data)
// {
// 	mlx_destroy_window(data->mlx_connection, data->mlx_win);
// 	mlx_destroy_display(data->mlx_connection);
// 	free_map(data->map.map, data->map.block_height);
// 	free(data->mlx_connection);
// 	exit(0);
// 	return (0);
// }

// Initializes all data structure fields to default values
void	init_data(t_game *game)
{
	// data->textures.collectable.count = 0;
	// data->textures.player.count = 0;
	// data->textures.player.x = 0;
	// data->textures.player.y = 0;
	// data->textures.exit.count = 0;
	// data->textures.exit.x = 0;
	// data->textures.exit.y = 0;
	game->map.map = NULL;
	game->map.height = 0;
	game->map.width = 0;
	// game->p.x = -1;
	// game->p.y = -1;
	// game->p.view = '\0';
	// game->mlx_connection = NULL;
	// game->mlx_win = NULL;
	// game->img = NULL;
	// data->img_height = 0;
	// data->img_width = 0;
	//data->count_movements = 0;
}

// Main function that initializes the game and starts the MLX loop
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	if (!is_valid_cub_file(argv[1]))
		return (1);
	init_data(&game);
	if (!parse_map(argv[1], &game))
		return (1);
		// data.mlx_connection = mlx_init();
		// data.mlx_win = mlx_new_window(data.mlx_connection,
		// 		BLOCK_SIZE * data.map.block_width,
		// 		BLOCK_SIZE * data.map.block_height, "cub3d");
		// if (data.mlx_win == NULL)
		// 	perror("Error\n");
		//draw_map(&data);
		//mlx_hook(data.mlx_win, 2, 1L << 0, handle_movements, &data);
		// mlx_hook(data.mlx_win, DestroyNotify, NoEventMask, end_program, &data);
		// mlx_loop(data.mlx_connection);
}
