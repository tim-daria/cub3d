/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:48:23 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/09 11:01:23 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks if the map filename ends with ".cub" extension
// Daria's function
static bool	is_cub_file(char *filename)
{
	char	*map_file;
	int		len;

	if (filename == NULL)
	{
		print_error("No filename");
		return (false);
	}
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	map_file = ft_substr(filename, ft_strlen(filename) - 4, 4);
	if (ft_strncmp(map_file, ".cub", 4) != 0)
	{
		print_error("Wrong file format");
		free(map_file);
		return (false);
	}
	free(map_file);
	return (true);
}

int	try_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open file");
		return (false);
	}
	return (fd);
}

// Checks if the file is empty
static bool	is_empty(int fd)
{
	char	buffer[1];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, 1);
	if (bytes_read <= 0)
	{
		print_error("File is empty");
		return (true);
	}
	return (false);
}

// checks if we can open the file and calls all other functions for primary check
bool	is_valid_cub_file(char *filename)
{
	int	fd;

	if (!is_cub_file(filename))
		return (false);
	fd = try_open(filename);
	if (fd < 0)
		return (false);
	if (is_empty(fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	if (!has_map_last(filename))
		return (false);
	if (!has_all_sides(filename))
		return (false);
	return (true);
}
