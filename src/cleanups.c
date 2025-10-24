/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:46:52 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 20:47:57 by tsemenov         ###   ########.fr       */
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
		{
			free(config->textures[i]);
			config->textures[i] = NULL;
		}
		i++;
	}
}

// Cleans up resources and terminates the program properly
void	clean_data(t_game *game)
{
	// printf("DEBUG: Starting clean_data\n");
	
	// Clean up get_next_line static buffer
	get_next_line(-1);
	
	if (game->mlx_win)
	{
		// printf("DEBUG: Destroying window\n");
		mlx_destroy_window(game->mlx_connection, game->mlx_win);
	}
	if (game->mlx_connection)
	{
		// printf("DEBUG: Destroying MLX connection\n");
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
	}
	// printf("DEBUG: About to free config textures\n");
	free_config(&game->config);
	// printf("DEBUG: Config textures freed\n");
	if (game->map.map)
	{
		// printf("DEBUG: About to free map at %p\n", game->map.map);
		free_map(game->map.map, game->map.height);
		game->map.map = NULL;
	}
}

// function that will be used on ESC
int	end_program(t_game *game)
{
	clean_data(game);
	return (0);
}