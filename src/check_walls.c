/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_correct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-13 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025-10-13 10:38:57 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_enclosed(char **visited, t_map map, int x, int y)
{
	if (x < 0 || x >= map.width || y < 0 || y >= map.height)
		return (false);
	if (map.map[y][x] == ' ')
		return (false);
	if (map.map[y][x] == '1' || visited[y][x] == 'V')
		return (true);
	visited[y][x] = 'V';
	if (!is_enclosed(visited, map, x + 1, y))
		return (false);
	if (!is_enclosed(visited, map, x - 1, y))
		return (false);
	if (!is_enclosed(visited, map, x, y + 1))
		return (false);
	if (!is_enclosed(visited, map, x, y - 1))
		return (false);
	return (true);
}

static char	**create_grid(int height, int width)
{
	char	**visited;
	int		i;

	visited = malloc(height * sizeof(char *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc((size_t)width, sizeof(char));
		if (!visited[i])
		{
			free_map(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

bool	surrounded_by_walls(t_map map, t_player p)
{
	char	**visited;
	int		y;
	int		x;

	visited = create_grid(map.height, map.width);
	if (!visited)
		return (print_error("Malloc failed"));
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] == '0' || map.map[y][x] == p.view)
			{
				if (!is_enclosed(visited, map, x, y))
					return (print_error("The map is not surrounded by walls"));
			}
			x++;
		}
		y++;
	}
	return (true);
}
