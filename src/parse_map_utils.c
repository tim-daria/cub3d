/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:58:54 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/26 22:11:50 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// //Searches the map for the player's starting position and
// //returns the character representing their view direction (N, S, E, or W).
// static char	find_player(t_map map)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < map.height)
// 	{
// 		x = 0;
// 		while (x < map.width)
// 		{
// 			if (map.map[y][x] == 'N' || map.map[y][x] == 'S'
// 				|| map.map[y][x] == 'E' || map.map[y][x] == 'W')
// 				break ;
// 			x++;
// 		}
// 		if (x < map.width)
// 			break ;
// 		y++;
// 	}
// 	return (map.map[y][x]);
// }

// // Finds the player's position in the map and sets the player's
// // view, x, and y coordinates in the t_player structure.
// void	find_player_pos(t_map map, t_player *p)
// {
// 	p->view = find_player(map);
// 	p->y = 0;
// 	while (p->y < map.height)
// 	{
// 		p->x = 0;
// 		while (p->x < map.width)
// 		{
// 			if (map.map[p->y][p->x] == p->view)
// 				return ;
// 			p->x++;
// 		}
// 		p->y++;
// 	}
// }

// Counts the length of a string until a newline character or
//the end of the string is encountered.
int	count_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
	{
		len++;
	}
	return (len);
}

// Calculates the height and width of the map by counting lines and
//lenght of lines in the file
void	map_height_width(int fd, t_map *map)
{
	int		max_width;
	int		line_len;
	char	*read_line;

	read_line = skip_not_map(fd);
	map->height = 0;
	max_width = 0;
	while (read_line != NULL)
	{
		line_len = count_len(read_line);
		if (line_len > max_width)
			max_width = line_len;
		map->height++;
		free(read_line);
		read_line = get_next_line(fd);
	}
	map->width = max_width;
	close(fd);
}

// Frees allocated memory for the map array
bool	free_map(char **map, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free (map[i++]);
	free (map);
	return (false);
}
