/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:22:26 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:27:08 by dtimofee         ###   ########.fr       */
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

// Phase 1: Just save the texture path for validation
static bool	save_texture_path(t_texture *texture, char *arg)
{
	texture->texture_path = ft_strdup(arg);
	if (!texture->texture_path)
		return (false);
	texture->img_ptr = NULL;
	texture->data_addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bpp = 0;
	texture->size_line = 0;
	texture->endian = 0;
	return (true);
}

// Phase 2: Load actual texture data after MLX is initialized
static bool	load_xpm_data(t_config *config, t_texture *texture)
{
	if (!texture->texture_path)
		return (false);
	texture->img_ptr = mlx_xpm_file_to_image(config->game->mlx_connection,
											texture->texture_path,
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

// copies path to the texture during config parsing
bool	copy_texture(char *id, char *arg, t_config *config)
{
	if (ft_strcmp(id, "NO") == 0 && !config->textures[NORTH].texture_path)
	{
		if (!save_texture_path(&config->textures[NORTH], arg))
			return (false);
	}
	if (ft_strcmp(id, "SO") == 0 && !config->textures[SOUTH].texture_path)
	{
		if (!save_texture_path(&config->textures[SOUTH], arg))
			return (false);
	}
	if (ft_strcmp(id, "WE") == 0 && !config->textures[WEST].texture_path)
	{
		if (!save_texture_path(&config->textures[WEST], arg))
			return (false);
	}
	if (ft_strcmp(id, "EA") == 0 && !config->textures[EAST].texture_path)
	{
		if (!save_texture_path(&config->textures[EAST], arg))
			return (false);
	}
	return (true);
}

// Load all textures after MLX is initialized
bool	load_textures(t_config *config)
{
	if (!load_xpm_data(config, &config->textures[NORTH]))
		return (print_error("Error: Failed to load North texture"));
	if (!load_xpm_data(config, &config->textures[SOUTH]))
		return (print_error("Error: Failed to load South texture"));
	if (!load_xpm_data(config, &config->textures[WEST]))
		return (print_error("Error: Failed to load West texture"));
	if (!load_xpm_data(config, &config->textures[EAST]))
		return (print_error("Error: Failed to load East texture"));
	return (true);
}
