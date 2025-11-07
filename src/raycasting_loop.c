/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:34:58 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/08 00:02:32 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *ray)
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
	ray->wall_x = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->tex_step = 0;
	ray->tex_pos = 0;
}

static void	calc_ray_dir(t_game *game, t_ray *ray, int x)
{
	// camera_x goes from -1 (left) to +1 (right)
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->plane_x = -game->p.dir_y * (FOV / 100.0);
	ray->plane_y = game->p.dir_x * (FOV / 100.0);
	// Ray direction = direction + plane * camera_x
	ray->ray_dir_x = game->p.dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = game->p.dir_y + ray->plane_y * ray->camera_x;
}

static void calc_from_directions(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0) // ray goes to the left
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->p.pos_x - ray->map_x)
							* ray->delta_dist_x;
	}
	else // ray goes to the right
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->p.pos_x)
							* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0) // ray goes down
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->p.pos_y - ray->map_y)
							* ray->delta_dist_y;
	}
	else // ray goes up
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->p.pos_y)
							* ray->delta_dist_y;
	}
}

static void	calc_side_distances(t_game *game, t_ray *ray)
{
	// calc start point for the ray (where the player is)
	ray->map_x = (int)game->p.pos_x;
	ray->map_y = (int)game->p.pos_y;
	// calc the cost of moving by 1 full grid
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	// calc the cost of moving from the start to the next x- or y-line
	calc_from_directions(game, ray);
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