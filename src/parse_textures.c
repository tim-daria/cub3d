/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:22:26 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 17:20:23 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

bool	copy_texture(char *id, char *arg, t_config *config)
{
	if (ft_strcmp(id, "NO") == 0 && !config->textures[NORTH])
	{
		config->textures[NORTH] = ft_strdup(arg);
		if (!config->textures[NORTH])
			return (false);
	}
	if (ft_strcmp(id, "SO") == 0 && !config->textures[SOUTH])
	{
		config->textures[SOUTH] = ft_strdup(arg);
		if (!config->textures[SOUTH])
			return (false);
	}
	if (ft_strcmp(id, "WE") == 0 && !config->textures[WEST])
	{
		config->textures[WEST] = ft_strdup(arg);
		if (!config->textures[WEST])
			return (false);
	}
	if (ft_strcmp(id, "EA") == 0 && !config->textures[EAST])
	{
		config->textures[EAST] = ft_strdup(arg);
		if (!config->textures[EAST])
			return (false);
	}
	return (true);
}