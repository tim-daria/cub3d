/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:25:58 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/08 14:35:51 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_config_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "F ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0);
}

static bool	is_map_line(char *line)
{
	int		i;
	bool	has_content;

	i = 0;
	has_content = false;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ')
		{
			i++;
			continue;
		}
		if (ft_strchr("01NSEW", line[i]) != NULL)
		{
			has_content = true;
			i++;
		}
		else
			return (false);
	}
	return (has_content);
}

// helper function that does the actual map order check
static bool	check_map_order(int fd, char **line)
{
	int		map_found;

	map_found = 0;
	*line = get_next_line(fd);
	while (*line != NULL)
	{
		// printf("DEBUG: reading line: %s", line);
		if ((*line)[0] <= 32)
		{
			free(*line);
			*line = get_next_line(fd); 
			continue;
		}
		if (is_map_line(*line))
			map_found = 1;
		else if (map_found && is_config_line(*line))
		{
			free(*line);
			*line = NULL;
			return (false);
		}
		free(*line);
		*line = get_next_line(fd);
	}
	return (true);
}

// checks if the map is in the end of the file
bool	has_map_last(char *filename)
{
	int		fd;
	bool	result;
	char	*line;

	fd = try_open(filename);
	result = check_map_order(fd, &line);
	close(fd);
	if (line)
		free(line);
	if (!result)
	{
		print_error("Map must be at the end of the file");
		return (false);
	}
	return (true);
}