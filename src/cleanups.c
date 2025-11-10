/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:46:52 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:24:50 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (config->textures[i].img_ptr)
		{
			mlx_destroy_image(config->game->mlx_connection, config->textures[i].img_ptr);
			config->textures[i].img_ptr = NULL;
		}
		if (config->textures[i].texture_path)
		{
			free(config->textures[i].texture_path);
			config->textures[i].texture_path = NULL;
		}
		i++;
	}
}

// Cleans up resources and terminates the program properly
bool	clean_data(t_game *game)
{
	get_next_line(-1);
	free_config(&game->config);
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
	if (game->map.map)
	{
		free_map(game->map.map, game->map.height);
		game->map.map = NULL;
	}
	return (false);
}

// function that will be used on ESC and window close
int	end_program(t_game *game)
{
	clean_data(game);
	exit(0);
}
