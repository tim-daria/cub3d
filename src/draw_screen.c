/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:15:21 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 13:46:09 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Helper function to put a pixel in the image
void	put_pixel(t_game *game, int x, int y, int color)
{
	int	position;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	position = (y * game->line_len) + (x * (game->bits_pp / 8));
	*(int *)(game->img_addr + position) = color;
}

// Fill the top half with ceiling color and bottom half with floor color
static void	fill_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(game, x, y, game->config.ceiling_color);
			else
				put_pixel(game, x, y, game->config.floor_color);
			x++;
		}
		y++;
	}
}

// draw screen but before destroy old image if it exists to prevent memory leak
bool	draw_screen(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx_connection, game->img);
	game->img = mlx_new_image(game->mlx_connection, WIDTH, HEIGHT);
	if (!game->img)
	{
		print_error("Error: Failed to create image");
		return (false);
	}
	game->img_addr = mlx_get_data_addr(game->img, &game->bits_pp,
			&game->line_len, &game->endian);
	if (!game->img_addr)
	{
		print_error("Error: Failed to get image address");
		return (false);
	}
	fill_floor_and_ceiling(game);
	return (true);
}
