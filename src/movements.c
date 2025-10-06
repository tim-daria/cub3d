/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:16:10 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/06 16:30:15 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "so_long.h"

// static void	go_up(t_mlx_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = data->textures.player.x;
// 	y = data->textures.player.y;
// 	if (y > 0 && data->map.map[y - 1][x] != '1')
// 	{
// 		if (data->map.map[y][x] ==
// 			data->map.map[data->textures.exit.y][data->textures.exit.x])
// 			data->map.map[y][x] = 'E';
// 		else
// 			data->map.map[y][x] = '0';
// 		if (data->map.map[y - 1][x] == 'C')
// 			data->textures.collectable.count--;
// 		y--;
// 		data->map.map[y][x] = 'P';
// 		data->textures.player.y = y;
// 		data->count_movements++;
// 		ft_printf("Total player actions: %d\n", data->count_movements);
// 	}
// }

// static void	go_down(t_mlx_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = data->textures.player.x;
// 	y = data->textures.player.y;
// 	if (y < data->map.block_height - 1 && data->map.map[y + 1][x] != '1')
// 	{
// 		if (data->map.map[y][x] ==
// 			data->map.map[data->textures.exit.y][data->textures.exit.x])
// 			data->map.map[y][x] = 'E';
// 		else
// 			data->map.map[y][x] = '0';
// 		if (data->map.map[y + 1][x] == 'C')
// 			data->textures.collectable.count--;
// 		y++;
// 		data->map.map[y][x] = 'P';
// 		data->textures.player.y = y;
// 		data->count_movements++;
// 		ft_printf("Total player actions: %d\n", data->count_movements);
// 	}
// }

// static void	go_right(t_mlx_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = data->textures.player.x;
// 	y = data->textures.player.y;
// 	if (x < data->map.block_width - 1 && data->map.map[y][x + 1] != '1')
// 	{
// 		if (data->map.map[y][x]
// 			== data->map.map[data->textures.exit.y][data->textures.exit.x])
// 			data->map.map[y][x] = 'E';
// 		else
// 			data->map.map[y][x] = '0';
// 		if (data->map.map[y][x + 1] == 'C')
// 			data->textures.collectable.count--;
// 		x++;
// 		data->map.map[y][x] = 'P';
// 		data->textures.player.x = x;
// 		data->count_movements++;
// 		ft_printf("Total player actions: %d\n", data->count_movements);
// 	}
// }

// static void	go_left(t_mlx_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = data->textures.player.x;
// 	y = data->textures.player.y;
// 	if (x > 0 && data->map.map[y][x - 1] != '1')
// 	{
// 		if (data->map.map[y][x]
// 			== data->map.map[data->textures.exit.y][data->textures.exit.x])
// 			data->map.map[y][x] = 'E';
// 		else
// 			data->map.map[y][x] = '0';
// 		if (data->map.map[y][x - 1] == 'C')
// 			data->textures.collectable.count--;
// 		x--;
// 		data->map.map[y][x] = 'P';
// 		data->textures.player.x = x;
// 		data->count_movements++;
// 		ft_printf("Total player actions: %d\n", data->count_movements);
// 	}
// }

// int	handle_movements(int keysym, t_mlx_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		end_program(data);
// 		return (0);
// 	}
// 	else if (keysym == XK_w || keysym == XK_W)
// 		go_up(data);
// 	else if (keysym == XK_s || keysym == XK_S)
// 		go_down(data);
// 	else if (keysym == XK_d || keysym == XK_D)
// 		go_right(data);
// 	else if (keysym == XK_a || keysym == XK_A)
// 		go_left(data);
// 	draw_map(data);
// 	if ((data->map.map[data->textures.player.y][data->textures.player.x]
// 		== data->map.map[data->textures.exit.y][data->textures.exit.x])
// 		&& data->textures.collectable.count == 0)
// 	{
// 		ft_printf("Dora the Explorer found all the magnifying glasses!\n");
// 		end_program(data);
// 	}
// 	return (0);
// }
