/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:58:54 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/06 18:03:53 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// void	position(t_position *texture, t_map *map, char c)
// {
// 	while (texture->y < map->block_height)
// 	{
// 		texture->x = 0;
// 		while (texture->x < map->block_width)
// 		{
// 			if (map->map[texture->y][texture->x] == c)
// 				return ;
// 			texture->x++;
// 		}
// 		texture->y++;
// 	}
// }

// Counts the number of player characters (N, S, E, W) in the map
int	count_player(t_map map)
{
	int	i;
	int	j;
	int	count_player;

	i = 0;
	count_player = 0;
	while (i < map.block_height)
	{
		j = 0;
		while (j < map.block_width)
		{
			if (ft_strchr("NSEW", map.map[i][j]))
				count_player++;
			j++;
		}
		i++;
	}
	return (count_player);
}

// Calculates the height of the map by counting lines in the file
int	map_height(int fd)
{
	int		height;
	char	*read_line;

	read_line = get_next_line(fd);
	height = 1;
	while (read_line != NULL)
	{
		free(read_line);
		read_line = get_next_line(fd);
		height++;
	}
	close(fd);
	return (height - 1);
}

// Initializes all data structure fields to default values
void	init_data(t_mlx_data *data)
{
	// data->textures.collectable.count = 0;
	// data->textures.player.count = 0;
	// data->textures.player.x = 0;
	// data->textures.player.y = 0;
	// data->textures.exit.count = 0;
	// data->textures.exit.x = 0;
	// data->textures.exit.y = 0;
	data->map.map = NULL;
	data->map.block_height = 0;
	data->map.block_width = 0;
	data->mlx_connection = NULL;
	data->mlx_win = NULL;
	data->img = NULL;
	data->img_height = 0;
	data->img_width = 0;
	//data->count_movements = 0;
}

// Frees allocated memory for the map array
void	free_map(char **map, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free (map[i++]);
	free (map);
}
