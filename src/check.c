/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:48:23 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/06 16:19:12 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_mapfilename(char *filename)
{
	char	*map_file;

	map_file = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (ft_strncmp(map_file, ".cub", 4) != 0)
	{
		ft_printf("Error\nWrong name of the map file\n");
		free(map_file);
		return (-1);
	}
	free(map_file);
	return (1);
}

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
				ft_printf("Error\nUnknown character\n");
				free_map(map->map, map->block_height);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}
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

