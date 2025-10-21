/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:02:15 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 17:23:50 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes all data structure fields to default values
bool	init_data(t_game *game)
{
	game->map.map = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->p.x = -1;
	game->p.y = -1;
	game->p.view = '\0';
	game->mlx_connection = NULL;
	game->mlx_win = NULL;
	// game->img = NULL;
	return (true);
}

static bool	setup_mlx(t_game *game)
{
	game->mlx_connection = mlx_init();
	if (!game->mlx_connection)
	{
		print_error("Failed to initialize MLX");
		return (false);
	}
	game->mlx_win = mlx_new_window(game->mlx_connection, WIDTH, HEIGHT, "Cub3D");
	if (!game->mlx_win)
	{
		print_error("Failed to create window");
		return (false);
	}
	// mlx_hook(game.mlx_win, 2, 1L << 0, handle_keypress, &game);
	// mlx_hook(game.mlx_win, 17, 0, end_program, &game);
	// mlx_loop should be called separately when ready to start game loop
	return (true);
}

// inits game, parses map & config, starts mlx window
// on fail, cleans up
bool	start_game(t_game *game, char *arg)
{
	if (!is_valid_cub_file(arg))
		return (false);
	if (!parse_config(arg, game))
	{
		clean_data(game);
		return (false);
	}
	if (!parse_map(arg, game))
	{
		clean_data(game);
		return (false);
	}
	if (!setup_mlx(game))
	{
		clean_data(game);
		return (false);
	}
	return (true);
}