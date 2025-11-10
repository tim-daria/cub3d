/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:37:50 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 13:47:33 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_config(t_config *config)
{
	int		i;

	i = NORTH;
	while (i <= EAST)
	{
		config->textures[i] = NULL;
		i++;
	}
	config->floor_color = -1;
	config->ceiling_color = -1;
	return (true);
}

// helper function for parsing/cleanup on fail for every line in the loop
static bool	extract_config(char **line, t_config *config, int *fd)
{
	if (is_config_line(*line))
	{
		if (!parse_config_line(*line, config))
		{
			print_error("Failed to parse config line");
			free(*line);
			close(*fd);
			return (false);
		}
	}
	return (true);
}

// creates config and saves all parsed data
bool	parse_config(char *filename, t_game *game)
{
	int			fd;
	char		*line;

	init_config(&game->config);
	fd = open_file(filename);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		if (!extract_config(&line, &game->config, &fd))
			return (false);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}
