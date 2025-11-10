/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:04:11 by dtimofee          #+#    #+#             */
/*   Updated: 2025/11/10 13:17:12 by dtimofee         ###   ########.fr       */
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
			put_pixel(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_rays(t_game *game, double ray_angle)
{
	int		x;
	double	ray_x;
	double	ray_y;
	int		i;

	x = 0;
	while (x < WIDTH)
	{
		i = 0;
		while (i < RAY_LENGTH)
		{
			ray_x = game->p.pos_x + (i * cos(ray_angle) / TILE_SIZE);
			ray_y = game->p.pos_y + (i * sin(ray_angle) / TILE_SIZE);
			if (ray_x < 0 || ray_y < 0 || (int)ray_y >= game->map.height
				|| (int)ray_x >= game->map.width)
				break ;
			if (game->map.map[(int)ray_y][(int)ray_x] == '1')
				break ;
			put_pixel(game, (int)(ray_x * TILE_SIZE),
				(int)(ray_y * TILE_SIZE), LIGHT_GREEN);
			i++;
		}
		ray_angle += (double)FOV * (PI / 180) / WIDTH;
		x++;
	}
}

static void	draw_rays_and_player(t_game *game)
{
	int		px;
	int		py;
	double	ray_angle;
	double	player_angle;

	player_angle = atan2(game->p.dir_y, game->p.dir_x);
	ray_angle = player_angle - ((FOV * PI / 180) / 2);
	draw_rays(game, ray_angle);
	px = (int)(game->p.pos_x * TILE_SIZE);
	py = (int)(game->p.pos_y * TILE_SIZE);
	put_pixel(game, px, py, GREEN);
}

void	draw_minimap(t_game *game, char **map)
{
	int	color;
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (map[y][x] == '1')
				color = BLACK;
			else if (map[y][x] == '0' || map[y][x] == game->p.view)
				color = GRAY;
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
	draw_rays_and_player(game);
}
