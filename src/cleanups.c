/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:46:52 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/08 00:44:58 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// path present?
// file opens?

void	free_2d_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_config(t_config *config)
{
	int	i;

	if (!config)
		return ;
	i = NORTH;
	while (i <= EAST)
	{
		if (config->textures[i].texture_path)
		{
			free(config->textures[i].texture_path);
			config->textures[i].texture_path = NULL;
		}
		if (config->textures[i].img_ptr)
		{
			free(config->textures[i].img_ptr);
			config->textures[i].img_ptr = NULL;
		}
		i++;
	}
}

// Cleans up resources and terminates the program properly
void	clean_data(t_game *game)
{
	get_next_line(-1);
	if (game->img)
	{
		mlx_destroy_image(game->mlx_connection, game->img);
		game->img = NULL;
	}
	
	if (game->mlx_win)
	{
		mlx_destroy_window(game->mlx_connection, game->mlx_win);
		game->mlx_win = NULL;
	}
	if (game->mlx_connection)
	{
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
		game->mlx_connection = NULL;
	}
	free_config(&game->config);
	if (game->map.map)
	{
		free_map(game->map.map, game->map.height);
		game->map.map = NULL;
	}
}

// function that will be used on ESC and window close
int	end_program(t_game *game)
{
	clean_data(game);
	exit(0);
}