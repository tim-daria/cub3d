/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:32:24 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 13:49:22 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	get_rgb(char *arg, int	*r, int *g, int *b);
static bool	is_valid_num(int n);
static int	rgb_to_hex(int r, int g, int b);

bool	check_and_copy_color(char *id, char *arg, t_config *config)
{
	int	hex;
	int	r;
	int	g;
	int	b;

	if (!get_rgb(arg, &r, &g, &b))
		return (false);
	hex = rgb_to_hex(r, g, b);
	if (ft_strcmp(id, "F") == 0)
		config->floor_color = hex;
	else if (ft_strcmp(id, "C") == 0)
		config->ceiling_color = hex;
	else
		return (false);
	return (true);
}

static bool	get_rgb(char *arg, int	*r, int *g, int *b)
{
	char	**split;
	bool	result;

	result = true;
	split = ft_split(arg, ',');
	if (!split)
		return (false);
	if (!split[0] || !split[1] || !split[2] || split[3])
		result = false;
	else
	{
		*r = ft_atoi(split[0]);
		*g = ft_atoi(split[1]);
		*b = ft_atoi(split[2]);
		if (!is_valid_num(*r) || !is_valid_num(*g) || !is_valid_num(*b))
			result = false;
	}
	free_2d_arr(split);
	return (result);
}

static bool	is_valid_num(int n)
{
	if (n < 0 || n > 255)
		return (false);
	return (true);
}

static int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
