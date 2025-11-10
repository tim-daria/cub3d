/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025/11/10 15:41:27 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//This function recursively checks if a given cell (x, y) in the map is enclosed
//by walls. It returns true if the cell is enclosed, and false otherwise.
//The function checks for out-of-bounds conditions, spaces
//(which indicate a leak), walls, and already visited cells
//to avoid infinite recursion.
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
	if (!is_enclosed(visited, map, x + 1, y - 1))
		return (false);
	if (!is_enclosed(visited, map, x - 1, y))
		return (false);
	if (!is_enclosed(visited, map, x - 1, y + 1))
		return (false);
	if (!is_enclosed(visited, map, x, y + 1))
		return (false);
	if (!is_enclosed(visited, map, x + 1, y + 1))
		return (false);
	if (!is_enclosed(visited, map, x, y - 1))
		return (false);
	if (!is_enclosed(visited, map, x - 1, y - 1))
		return (false);
	return (true);
}

//This function allocates a 2D grid of characters with the given
//height and width. It's used to keep track of visited cells
//during the is_enclosed check.
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

bool	check_all_cells(char **visited, t_map map, char view)
{
	int	y;
	int	x;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] == '0' || map.map[y][x] == view)
			{
				if (!is_enclosed(visited, map, x, y))
					return (free_map(visited, map.height));
			}
			x++;
		}
		y++;
	}
	return (true);
}

//This function checks if the entire map is surrounded by walls.
//It iterates through each cell in the map, and if a cell is a floor ('0')
//or the player's starting position, it calls is_enclosed to check if that
//cell is enclosed by walls.
bool	surrounded_by_walls(t_map map, t_player p)
{
	char	**visited;

	visited = create_grid(map.height, map.width);
	if (!visited)
		return (print_error("Malloc failed"));
	if (!check_all_cells(visited, map, p.view))
	{
		free_map(visited, map.height);
		return (print_error("The map is not surrounded by walls"));
	}
	free_map(visited, map.height);
	return (true);
}
