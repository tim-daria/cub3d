/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:46:52 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/15 23:04:58 by tsemenov         ###   ########.fr       */
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
		if (config->textures[i])
			free(config->textures[i]);
		i++;
	}
	free(config);
}

// Cleans up resources and terminates the program properly
void	clean_data(t_game *game)
{
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_connection, game->mlx_win);
	if (game->mlx_connection)
	{
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
	}
	if (game->config)
	{
		free_config(game->config);
		game->config = NULL;
	}
	if (game->map.map)
	{
		free_2d_arr(game->map.map);
		game->map.map = NULL;
	}
	free(game);
}

// function that will be used on ESC
int	end_program(t_game *game)
{
	clean_data(game);
	return (0);
}