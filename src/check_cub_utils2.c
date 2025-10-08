/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:25:38 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/08 14:38:17 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	has_no_so(char *filename)
{
	char	*line;
	int		fd;
	int		no;
	int		so;

	fd = try_open(filename);
	no = 0;
	so = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			no++;
		if (ft_strncmp(line, "SO ", 3) == 0)
			so++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (no != 1 || so != 1)
		return (false);
	// check texture & parse
	return (true);
}

static bool	has_we_ea(char *filename)
{
	char	*line;
	int		fd;
	int		we;
	int		ea;

	fd = try_open(filename);
	we = 0;
	ea = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "WE ", 3) == 0)
			we++;
		if (ft_strncmp(line, "EA ", 3) == 0)
			ea++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (we != 1 || ea != 1)
		return (false);
	// parse
	return (true);
}

static bool	has_fc(char *filename)
{
	char	*line;
	int		fd;
	int		f;
	int		c;

	fd = try_open(filename);
	f = 0;
	c = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
			f++;
		if (ft_strncmp(line, "C ", 3) == 0)
			c++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (f != 1 || c != 1)
		return (false);
	// parse
	return (true);
}

bool	has_all_sides(char *filename)
{
	if (!has_no_so(filename)
		|| !has_we_ea(filename)
		|| !has_fc(filename))
	{
		print_error("Wrong config");
		return (false);
	}
	return (true);
}