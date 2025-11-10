/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 21:02:15 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 14:59:06 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializes all data structure fields to default values
bool	init_data(t_game *game)
{
	game->map.map = NULL;
	game->map.height = 0;
	game->map.width = 0;
	game->p.view = '\0';
	game->p.angle = 0;
	game->p.pos_x = 0;
	game->p.pos_y = 0;
	game->p.dir_x = 0;
	game->p.dir_y = 0;
	game->mlx_connection = NULL;
	game->mlx_win = NULL;
	game->img = NULL;
	game->img_addr = NULL;
	game->bits_pp = 0;
	game->line_len = 0;
	game->endian = 0;
	game->key_w = false;
	game->key_a = false;
	game->key_s = false;
	game->key_d = false;
	game->key_left = false;
	game->key_right = false;
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
	return (true);
}

// inits game, parses map & config, starts mlx window
// on fail, cleans up
bool	start_game(t_game *game, char *arg)
{
	if (!is_valid_cub_file(arg))
	{
		get_next_line(-1);
		return (false);
	}
	if (!parse_config(arg, game))
		return (clean_data(game));
	if (!parse_map(arg, game))
		return (clean_data(game));
	find_player_pos(game->map, &game->p);
	if (!setup_mlx(game))
		return (clean_data(game));
	if (!load_textures(&game->config))
		return (clean_data(game));
	return (true);
}