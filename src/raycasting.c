/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:34:58 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 13:54:34 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_ray_dir(t_game *game, t_ray *ray, int x);
static void	calc_side_distances(t_game *game, t_ray *ray);
static void	perform_dda(t_game *game, t_ray *ray);
static void	calc_wall_distance(t_ray *ray);
static void	calc_wall_height(t_ray *ray);
static void	draw_vertical_line(t_game *game, t_ray *ray, int x);
static void	dda(t_game *game, t_ray *ray, int x);

void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->perp_wall_dist = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	raycast_loop(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray);
		calc_ray_dir(game, &ray, x);
		calc_side_distances(game, &ray);
		dda(game, &ray, x);
		x++;
	}
}

static void	calc_ray_dir(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->plane_x = -game->p.dir_y * (FOV / 100.0);
	ray->plane_y = game->p.dir_x * (FOV / 100.0);
	ray->ray_dir_x = game->p.dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = game->p.dir_y + ray->plane_y * ray->camera_x;
}

static void	calc_side_distances(t_game *game, t_ray *ray)
{
	ray->map_x = (int)game->p.pos_x;
	ray->map_y = (int)game->p.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	// calc the cost of moving from the start to the next x- or y-line
	if (ray->ray_dir_x < 0) // ray goes to the left
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->p.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else // ray goes to the right
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->p.pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0) // ray goes down
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->p.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else // ray goes up
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->p.pos_y) * ray->delta_dist_y;
	}
}

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
	// Calculate height of line to draw on screen
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	// Calculate lowest and highest pixel to fill in the line
	// centering the line on x-axis
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	y;
	int	color;

	if (ray->side == 0) // Vertical walls (East/West)
	{
		if (ray->step_x > 0)
			color = 0xFF6699; // Pink for WEST walls (ray going right)
		else
			color = 0x0099FF; // Blue for EAST walls (ray going left)
	}
	else // Horizontal walls (North/South)
	{
		if (ray->step_y > 0)
			color = 0x99FFCC; // Green for SOUTH walls (ray going down)
		else
			color = 0xFFFF99; // Yellow for NORTH walls (ray going up)
	}
	// Draw the wall line
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}

static void	dda(t_game *game, t_ray *ray, int x)
{
	perform_dda(game, ray);
	calc_wall_distance(ray);
	calc_wall_height(ray);
	draw_vertical_line(game, ray, x);
}
