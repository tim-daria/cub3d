/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:25:58 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/09 20:59:23 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

bool	is_config_line(char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	return (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0
		|| ft_strncmp(trimmed, "EA ", 3) == 0
		|| ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0);
}

bool	is_map_line(char *line)
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
			continue ;
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
		if (count_len(*line) == 0)
		{
			free(*line);
			*line = get_next_line(fd);
			continue ;
		}
		if (is_map_line(*line))
			map_found = 1;
		else if (map_found && count_len(*line) == 0)
			return (print_error("Empty line in the map"));
		else if (map_found && is_config_line(*line))
			return (print_error("Map must be at the end of the file"));
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

	fd = open_file(filename);
	if (fd < 0)
		return (false);
	result = check_map_order(fd, &line);
	close(fd);
	if (line)
		free(line);
	if (!result)
		return (false);
	return (true);
}
