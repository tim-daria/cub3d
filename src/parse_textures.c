/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:22:26 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/07 17:02:21 by tsemenov         ###   ########.fr       */
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

// saves texture data needed for drawing walls into the config
static bool	get_xpm_data(t_config *config, t_texture *texture, char *arg)
{
	texture->texture_path = ft_strdup(arg);
	if (!texture->texture_path)
		return (false);
	texture->img_ptr = mlx_xpm_file_to_image(config->game->mlx_connection, arg,
											&texture->width, &texture->height);
	if (texture->img_ptr == NULL)
		return (false);
	texture->data_addr = mlx_get_data_addr(texture->img_ptr,
											&texture->bpp,
											&texture->size_line,
											&texture->endian);
	if (texture->data_addr == NULL)
		return (false);
	return (true);
}

bool	copy_texture(char *id, char *arg, t_config *config)
{
	if (ft_strcmp(id, "NO") == 0 && !config->textures[NORTH].texture_path)
	{
		if (!get_xpm_data(config, &config->textures[NORTH], arg))
			return (false);
	}
	if (ft_strcmp(id, "SO") == 0 && !config->textures[SOUTH].texture_path)
	{
		if (!get_xpm_data(config, &config->textures[SOUTH], arg))
			return (false);
	}
	if (ft_strcmp(id, "WE") == 0 && !config->textures[WEST].texture_path)
	{
		if (!get_xpm_data(config, &config->textures[WEST], arg))
			return (false);
	}
	if (ft_strcmp(id, "EA") == 0 && !config->textures[EAST].texture_path)
	{
		if (!get_xpm_data(config, &config->textures[EAST], arg))
			return (false);
	}
	return (true);
}