/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-10 14:12:19 by dtimofee          #+#    #+#             */
/*   Updated: 2025-10-10 14:12:19 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/cub3d.h"

// // Checks if the map is completely surrounded by walls ('1')
// int	check_walls(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while (i < map->block_width)
// 	{
// 		if (map->map[0][i] != '1' || map->map[map->block_height - 1][i] != '1')
// 		{
// 			ft_printf("Error\nThe map is not surrounded by walls\n");
// 			free_map(map->map, map->block_height);
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < map->block_height)
// 	{
// 		if (map->map[i][0] != '1' || map->map[i][map->block_width - 1] != '1')
// 		{
// 			ft_printf("Error\nThe map is not surrounded by walls\n");
// 			return (free_map(map->map, map->height));
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	return (1);
// }
