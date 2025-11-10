/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:48:51 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 14:26:01 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	perform_dda(t_game *game, t_ray *ray)
{
	// DDA algorithm: step through the grid until we hit a wall
	ray->hit = 0;
	while (ray->hit == 0)
	{
		// Jump to next map square in x or y direction
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // vertical wall (X side) - we expect to meet east or west wall
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // horizontal wall (Y side) - we expect to meet north or south wall
		}
		// Check if ray has hit a wall
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall_distance(t_ray *ray)
{
	// Calculate perpendicular distance to avoid fisheye effect
	// Subtract one delta_dist because we stepped past the wall line
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

static void	calc_wall_height(t_ray *ray)
{
	int	wall_start;
	int	wall_end;

	// Calculate height of line to draw on screen
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	// Calculate lowest and highest pixel to fill in the line
	// centering the line on the screen
	wall_start = (HEIGHT - ray->line_height) / 2;
	wall_end = wall_start + ray->line_height - 1;
	// Clamp to screen boundaries
	if (wall_start < 0)
		ray->draw_start = 0;
	else
		ray->draw_start = wall_start;
	if (wall_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	else
		ray->draw_end = wall_end;
}

static void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int			y;
	int			color;
	t_texture	*texture;

	texture = get_wall_texture(game, ray);
	calc_tex_x(texture, ray);
	calc_tex_step(texture, ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		if (ray->tex_y >= texture->height)
			ray->tex_y = texture->height - 1;
		ray->tex_pos += ray->tex_step;
		color = get_texture_pixel(texture, ray->tex_x, ray->tex_y);
		put_pixel(game, x, y, color);
		y++;
	}
}

void	dda(t_game *game, t_ray *ray, int x)
{
	perform_dda(game, ray);
	calc_wall_distance(ray);
	calc_wall_x(game, ray);
	calc_wall_height(ray);
	draw_vertical_line(game, ray, x);
}