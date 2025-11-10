/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:44:11 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 13:31:35 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks for any unknown characters in the map
//(only allows ' ', '0', '1', 'N', 'S', 'E', 'W')
static bool	unknown_character(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (ft_strchr(" 01NSEW", map->map[i][j]) == NULL)
			{
				print_error("Unknown character");
				return (false);
			}
			j++;
		}
		i++;
	}
	return (false);
}

// Counts the number of player characters (N, S, E, W) in the map
static int	count_player(t_map map)
{
	int	i;
	int	j;
	int	count_player;

	i = 0;
	count_player = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (ft_strchr("NSEW", map.map[i][j]))
				count_player++;
			j++;
		}
		i++;
	}
	return (count_player);
}

// Checks if there is exactly one player and no unknown characters in the map
bool	check_characters(t_map *map)
{
	int	player_count;

	player_count = count_player(*map);
	if (player_count != 1)
	{
		print_error("Wrong number of players");
		return (false);
	}
	if (unknown_character(map))
		return (false);
	return (true);
}
