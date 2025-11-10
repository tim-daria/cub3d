/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:48:51 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:36:34 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// DDA algorithm: step through the grid until we hit a wall
// Jump to next map square in x or y direction (by delta_dist)
// set ray->side - which wall we expect to hit by moving by x or y:
// side = 0: vertical wall (X side) - we expect to meet east or west wall
// side = 1: horizontal wall (Y side) - we expect to meet north or south wall
// After every move, check if ray has hit a wall
static void	perform_dda(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

// Calc perpendicular distance to avoid fisheye effect
// Subtract one delta_dist because we stepped past the wall line
static void	calc_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

// Calc height of line to draw on screen:
// Calc lowest and highest pixel to fill in the line
// center the line on the screen
// To avoid overflow, clamp to screen boundaries
// (if we go <0 or > screen height)
static void	calc_wall_height(t_ray *ray)
{
	int	wall_start;
	int	wall_end;

	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	wall_start = (HEIGHT - ray->line_height) / 2;
	wall_end = wall_start + ray->line_height - 1;
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
