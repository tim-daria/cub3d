/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:37:50 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/06 16:29:24 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_texture(t_texture *texture)
{
	texture->texture_path = NULL;
	texture->img_ptr = NULL;
	texture->data_addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->size_line = 0;
	texture->endian = 0;
	return (true);
}

static bool	init_config(t_game *game, t_config *config)
{
	int		i;

	i = NORTH;
	while (i <= EAST)
	{
		init_texture(&config->textures[i]);
		i++;
	}
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->game = game;
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

	init_config(game, &game->config);
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