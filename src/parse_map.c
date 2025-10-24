/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:46:16 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/21 20:35:50 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Copies a map line and pads it with spaces till the max width in the map.
static char	*copy_line(char *read_line, int width)
{
	char	*return_line;
	int		i;
	int		len_input;

	i = 0;
	return_line = malloc((width + 1) * sizeof(char));
	if (!return_line)
		return (NULL);
	len_input = count_len(read_line);
	while (i < len_input)
	{
		return_line[i] = read_line[i];
		i++;
	}
	while (i < width)
		return_line[i++] = ' ';
	return_line[i] = '\0';
	return (return_line);
}

//Reads lines from a file until a line is found that is recognized as a map line.
char	*skip_not_map(int fd)
{
	char	*read_line;

	read_line = get_next_line(fd);
	while (!is_map_line(read_line))
	{
		free(read_line);
		read_line = get_next_line(fd);
	}
	return (read_line);
}

// Reads map data from file and fills the map structure
static bool	fill_map(int fd, t_map *map)
{
	char	*read_line;
	int		i;

	i = 0;
	read_line = skip_not_map(fd);
	while (read_line != NULL)
	{
		map->map[i] = copy_line(read_line, map->width);
		if (map->map[i] == NULL)
		{
			perror("Error");
			free_map(map->map, i);
			close(fd);
			return (false);
		}
		i++;
		free(read_line);
		read_line = get_next_line(fd);
		if (read_line == NULL)
			break ;
	}
	return (true);
}

// Reads the map file, initializing the map structure
static bool	read_map_file(char *src, t_map *map)
{
	int	fd;

	fd = open_file(src);
	if (fd < 0)
		return (false);
	map_height_width(fd, map);
	fd = open_file(src);
	if (fd < 0)
		return (false);
	map->map = malloc((map->height + 1) * sizeof(char *));
	if (map->map == NULL)
	{
		perror("Error");
		close(fd);
		return (false);
	}
	/* Initialize all pointers to NULL - to avoid
	garbage data AND to NULL-terminate the array */
	int k = 0;
	while (k <= map->height)
	{
		map->map[k] = NULL;
		k++;
	}
	if (!fill_map(fd, map))
		return (false);
	close(fd);
	return (true);
}

// Main parsing function - Controls the flow for parsing the map, including reading the map file,
// checking characters, walls and finding the player position.
bool	parse_map(char *filename, t_game *game)
{
	if (!read_map_file(filename, &game->map))
		return (false);
	if (!check_characters(&game->map))
		return (false);
	find_player_pos(game->map, &game->p);
	if (!surrounded_by_walls(game->map, game->p))
		return (false);  /* Let clean_data handle cleanup */
	return (true);
}
