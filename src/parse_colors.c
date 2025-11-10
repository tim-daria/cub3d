/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:32:24 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:26:20 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	get_rgb(char *arg, int	*r, int *g, int *b);
static bool	is_valid_num(int n);
static int	rgb_to_hex(int r, int g, int b);
static char	*join_colors(char **split, int start);

bool	check_and_copy_color(char **split, t_config *config)
{
	int	hex;
	int	r;
	int	g;
	int	b;
	char	*color_str;

	color_str = join_colors(split, 1);
	if (!color_str)
		return (false);
	if (!get_rgb(color_str, &r, &g, &b))
	{
		free(color_str);
		return (false);
	}
	hex = rgb_to_hex(r, g, b);
	if (ft_strcmp(split[0], "F") == 0)
		config->floor_color = hex;
	else if (ft_strcmp(split[0], "C") == 0)
		config->ceiling_color = hex;
	else
		return (false);
	free(color_str);
	return (true);
}

static char	*join_colors(char **split, int start)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = start;
	while (split[i])
	{
		temp = ft_strjoin(result, split[i]);
		free(result);
		if (!temp)
			return (NULL);
		result = temp;
		i++;
	}
	return (result);
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

