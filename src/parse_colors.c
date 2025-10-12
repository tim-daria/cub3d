/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:32:24 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/12 21:50:37 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgb(char *arg, int	*r, int *g, int *b);
static int	is_valid_num(int n);
static int	rgb_to_hex(int r, int g, int b);

int	check_and_copy_color(char *id, char *arg, t_config *config)
{
	int	hex;
	int	r;
	int	g;
	int	b;

	if (!get_rgb(arg, &r, &g, &b))
		return (0);
	hex = rgb_to_hex(r, g, b);
	if (ft_strcmp(id, "F") == 0)
		config->floor_color = hex;
	else if (ft_strcmp(id, "C") == 0)
		config->ceiling_color = hex;
	else
		return (0);
	return (1);
}

static int	get_rgb(char *arg, int	*r, int *g, int *b)
{
	char	**split;
	int		result;

	result = 1;
	split = ft_split(arg, ',');
	if (!split)
		return (0);
	if (!split[0] || !split[1] || !split[2] || split[3])
		result = 0;
	else
	{
		*r = ft_atoi(split[0]);
		*g = ft_atoi(split[1]);
		*b = ft_atoi(split[2]);
		if (!is_valid_num(*r) || !is_valid_num(*g) || !is_valid_num(*b))
			result = 0;
	}
	free_2d_arr(split);
	return (result);
}

static int	is_valid_num(int n)
{
	if (n < 0 || n > 255)
		return (0);
	return (1);
}

static int	rgb_to_hex(int r, int g, int b)
{
	return ( (r << 16) | (g << 8) | b);
}
