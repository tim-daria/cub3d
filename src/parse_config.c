/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:46:52 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/15 22:38:51 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	save_config(char *id, char *arg, t_config *config);
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
	if (!split || !split[0] || !split[1] || split[2])
	{
		printf("DEBUG: failed in parse_config_line\n");
		if (split)
			free_2d_arr(split);
		return (false);
	}
	result = save_config(split[0], split[1], config);
	free_2d_arr(split);
	return (result);
}

static bool	save_config(char *id, char *arg, t_config *config)
{
	if (is_texture(id))
	{
		if (!is_valid_texture_file(arg))
		{
			// printf("DEBUG: failed in is_valid_texture_file\n");
			return (false);
		}
		if (!copy_texture(id, arg, config))
		{
			// printf("DEBUG: failed in copy_texture\n");
			return (false);
		}
		return (true);
	}
	if (is_color(id))
	{
		if (!check_and_copy_color(id, arg, config))
			return (false);
		return (true);
	}
	return (false);
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

	// printf("DEBUG: trying to open: '%s'\n", path);
	fd = open_file(path);
	if (fd < 0)
		return (false);
	close (fd);
	return (true);
}