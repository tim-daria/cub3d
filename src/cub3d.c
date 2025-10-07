/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:39:58 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/06 22:42:02 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Cleans up resources and terminates the program properly
int	end_program(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx_connection, data->mlx_win);
	mlx_destroy_display(data->mlx_connection);
	free_map(data->map.map, data->map.block_height);
	free(data->mlx_connection);
	exit(0);
	return (0);
}

// Reads map data from file and fills the map structure
static int	fill_map(int fd, t_map *map)
{
	char	*read_line;
	int		i;

	i = 0;
	read_line = get_next_line(fd);
	if (read_line == NULL)
	{
		ft_printf("Error\nThe file with the map is empty\n");
		free_map(map->map, i);
		close(fd);
		return (-1);
	}
	map->block_width = ft_strlen(read_line) - 1;
	map->map[i++] = read_line;
	while (read_line != NULL)
	{
		read_line = get_next_line(fd);
		if (read_line == NULL)
			break ;
		map->map[i++] = read_line;
	}
	return (1);
}

// Opens a file and returns the file descriptor
static int	open_file(char *src)
{
	int	fd;

	fd = open(src, O_RDONLY);
	if (fd == -1)
		perror("Error\n");
	return (fd);
}

// Reads and validates the name of the map file, initializing the map structure
static int	read_map_file(char *src, t_map *map)
{
	int	fd;

	if (check_mapfilename(src) == -1)
		return (-1);
	fd = open_file(src);
	if (fd == -1)
		return (-1);
	map->block_height = map_height(fd);
	fd = open_file(src);
	if (fd == -1)
		return (-1);
	map->map = malloc(map->block_height * sizeof(char *));
	if (map->map == NULL)
	{
		perror("Error\n");
		close(fd);
		return (-1);
	}
	if (fill_map(fd, map) == -1)
		return (-1);
	close(fd);
	return (1);
}

// Main function that initializes the game and starts the MLX loop
int	main(int argc, char **argv)
{
	t_mlx_data	data;

	if (argc == 2)
	{
		init_data(&data);
		if (read_map_file(argv[1], &data.map) == -1
			|| check_characters(&data.map) == -1)
			return (0);
		//find_positions(&data);
		if (check_walls(&data.map) == -1)
			return (0);
		data.mlx_connection = mlx_init();
		data.mlx_win = mlx_new_window(data.mlx_connection,
				BLOCK_SIZE * data.map.block_width,
				BLOCK_SIZE * data.map.block_height, "cub3d");
		if (data.mlx_win == NULL)
			perror("Error\n");
		//draw_map(&data);
		//mlx_hook(data.mlx_win, 2, 1L << 0, handle_movements, &data);
		mlx_hook(data.mlx_win, DestroyNotify, NoEventMask, end_program, &data);
		mlx_loop(data.mlx_connection);
	}
}
