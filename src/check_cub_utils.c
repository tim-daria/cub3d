/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:25:58 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/07 22:07:20 by tsemenov         ###   ########.fr       */
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

// checks if the map is in the end of the file
bool	has_map_last(char *filename)
{
	int		fd;
	int		map_found;
	int		map_not_last;
	char	*line;
	int	len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open file");
		return (false);
	}
	map_found = 0;
	map_not_last = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("DEBUG: reading line: %s", line);
		if (line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd); 
			continue;
		}
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (line[0] == '\0')
		{
			free(line);
			line = get_next_line(fd); 
			continue;
		}
		if (is_map_line(line))
			map_found = 1;
		else if (map_found && is_config_line(line))
		{
			map_not_last = 1;
			free(line);
			line = NULL;
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (map_not_last)
	{
		print_error("Map must be at the end of the file");
		return (false);
	}
	return (true);
}