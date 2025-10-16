/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:37:50 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/15 23:02:29 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_config	*init_config()
{
	t_config	*new;
	int			i;

	new = malloc(sizeof(t_config));
	if (!new)
		return (NULL);
	i = NORTH;
	while (i <= EAST)
	{
		new->textures[i] = NULL;
		i++;
	}
	new->floor_color = -1;
	new->ceiling_color = -1;
	return (new);
}

// helper function for parsing/cleanup on fail for every line in the loop
static bool	extract_config(char **line, t_config **config, int *fd)
{
	if (is_config_line(*line))
	{
		if (!parse_config_line(*line, *config))
		{
			print_error("Failed to parse config line");
			free(*line);
			if (config)
				free_config(*config);
			*config = NULL;
			close(*fd);
			return (false);
		}
	}
	return (true);
}

// creates config and saves all parsed data
bool	parse_config(char *filename, t_game *game)
{
	t_config	*config;
	int			fd;
	char		*line;

	config = init_config();
	if (!config)
		return (false);
	fd = open_file(filename);
	if (fd < 0)
	{
		free_config(config);
		return (false);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (!extract_config(&line, &config, &fd))
			return (false);
		free(line);
		line = get_next_line(fd);
	}
	game->config = config;
	close(fd);
	return (true);
}