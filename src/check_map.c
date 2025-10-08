/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:44:11 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/08 15:17:20 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Checks for any unknown characters in the map (only allows '0', '1', 'N', 'S', 'E', 'W')
static int	unknown_character(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->block_height)
	{
		j = 0;
		while (j < map->block_width)
		{
			if (ft_strchr("01NSEW", map->map[i][j]) == NULL)
			{
				print_error("Unknown character\n");
				free_map(map->map, map->block_height);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}
// Checks if there is exactly one player and no unknown characters in the map
int	check_characters(t_map *map)
{
	int	player_count;

	player_count = count_player(*map);
	// textures->collectable.count = count_characters(*map, 'C');
	// textures->player.count = count_characters(*map, 'P');
	// textures->exit.count = count_characters(*map, 'E');
	if (player_count != 1)
	{
		ft_printf("Error\nWrong number of characters\n");
		free_map(map->map, map->block_height);
		return (-1);
	}
	if (unknown_character(map) == -1)
		return (-1);
	return (1);
}

// Checks if the map is completely surrounded by walls ('1')
int	check_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->block_width)
	{
		if (map->map[0][i] != '1' || map->map[map->block_height - 1][i] != '1')
		{
			ft_printf("Error\nThe map is not surrounded by walls\n");
			free_map(map->map, map->block_height);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < map->block_height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->block_width - 1] != '1')
		{
			ft_printf("Error\nThe map is not surrounded by walls\n");
			free_map(map->map, map->block_height);
			return (-1);
		}
		i++;
	}
	return (1);
}