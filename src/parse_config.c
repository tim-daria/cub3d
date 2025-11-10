/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:46:52 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 14:40:01 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	save_config(char **split, t_config *config);
static bool	is_texture(char *line);
static bool	is_color(char *line);
static bool	is_valid_texture_file(char *path);

// extracts texture path or color str and saves values to the struct
bool	parse_config_line(char *line, t_config *config)
{
	char	**split;
	bool	result;
	int		len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
	{
		if (split)
			free_2d_arr(split);
		return (false);
	}
	if (is_texture(split[0]) && split[2])
	{
		free_2d_arr(split);
		return (false);
	}
	result = save_config(split, config);
	free_2d_arr(split);
	return (result);
}

static bool	save_config(char **split, t_config *config)
{
	if (is_texture(split[0]))
	{
		if (!is_valid_texture_file(split[1]))
			return (false);
		if (!copy_texture(split[0], split[1], config))
			return (false);
	}
	if (is_color(split[0]))
	{
		if (!check_and_copy_color(split, config))
			return (false);
	}
	return (true);
}

static bool	is_texture(char *line)
{
	return (ft_strcmp(line, "NO") == 0 || ft_strcmp(line, "SO") == 0
		|| ft_strcmp(line, "WE") == 0 || ft_strcmp(line, "EA") == 0);
}

static bool	is_color(char *line)
{
	return (ft_strcmp(line, "F") == 0 || ft_strcmp(line, "C") == 0);
}

static bool	is_valid_texture_file(char *path)
{
	int	fd;

	fd = open_file(path);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}