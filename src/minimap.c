/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-21 19:04:11 by dtimofee          #+#    #+#             */
/*   Updated: 2025-10-21 19:04:11 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx_connection, game->mlx_win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	color;
	int	x;
	int	y;
	int	px;
	int	py;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.map[y][x] == '1')
				color = 0x888888;
			else if (game->map.map[y][x] == '0')
				color = 0x000000;
			else
			{
				x++;
				continue ;
			}
			draw_square(game, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	px = (int)game->p.pos_x * TILE_SIZE;
	py = (int)game->p.pos_y * TILE_SIZE;
	//draw_p_dot(game->mlx_connection, game->mlx_win, px, py);
	mlx_pixel_put(game->mlx_connection, game->mlx_win, px, py, 0x00FF00);
}
