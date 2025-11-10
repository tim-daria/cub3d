/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:25:38 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:24:31 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_side(char *filename, char *id, int len)
{
	char	*line;
	char	*trimmed;
	int		fd;
	int		count;

	fd = open_file(filename);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = skip_spaces(line);
		if (ft_strncmp(trimmed, id, len - 1) == 0
			&& (trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t'))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (count);
}

static bool	check_sides(char *filename)
{
	if (count_side(filename, "NO ", 3) != 1)
		return (false);
	if (count_side(filename, "SO ", 3) != 1)
		return (false);
	if (count_side(filename, "WE ", 3) != 1)
		return (false);
	if (count_side(filename, "EA ", 3) != 1)
		return (false);
	if (count_side(filename, "F ", 2) != 1)
		return (false);
	if (count_side(filename, "C ", 2) != 1)
		return (false);
	return (true);
}

// checks if all side identifiers are present
bool	has_all_sides(char *filename)
{
	if (!check_sides(filename))
	{
		print_error("Wrong config");
		return (false);
	}
	return (true);
}
