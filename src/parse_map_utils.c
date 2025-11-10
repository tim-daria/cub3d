/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:58:54 by dtimofee          #+#    #+#             */
/*   Updated: 2025/11/10 18:30:46 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Counts the length of a string until a newline character or
//the end of the string is encountered.
int	count_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
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

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
