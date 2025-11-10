/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:04:59 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:23:44 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// which part of the wall block does ray hit? left - center - right
// side == 1 - hit the NO-SO wall
// side == 0 - hit the WE-EA wall
void	calc_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 1)
		ray->wall_x = game->p.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	else if (ray->side == 0)
		ray->wall_x = game->p.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	ray->wall_x -= floor(ray->wall_x);
}

// which column of pixels to use from the texture to draw a vertical line
// calc tex_x and clamp before mirroring to handle wall_x == 1.0 edge case
// then mirror SOUTH and WEST walls,
// so they appear correctly (otherwirse, thiy will be flipped on x-axis)
void	calc_tex_x(t_texture *texture, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	if (ray->tex_x >= texture->width)
		ray->tex_x = texture->width - 1;
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		ray->tex_x = texture->width - ray->tex_x - 1;
}

//calculates how much to increment texture Y per screen pixel
// calc how many texture pixels we should go per step:
// calc texture height to wall height (on the screen) ratio
// if wall is near us (high for the screen), the texture will be stretched
// onto the wall (step < 0)
// if the wall is far away, the texture will be sqeezed (step > 0)
// calc starting point (ex. if the wall is near and cut by the screen,
// we need to start from the first visible pixel)
void	calc_tex_step(t_texture *texture, t_ray *ray)
{
	ray->tex_step = 1.0 * texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->tex_step;
}

// retrieves a pixel color from texture data
// data_addr is char* but we need int*,
// so we can move through the array by 4 bytes (1 px)
// find an y line needed. Before that calc, how many pixels are in line:
// (ex. 256 bytes length, 4 bytes - an int step = 64 pixels)
// how many pixels in the file != width*height,
// because size_line usually has memory paddings
// at the end of every line, so the next line has %16 or %32 address
int	get_texture_pixel(t_texture *texture, int x, int y)
{
	int		pixel_index;
	int		*pixel_data;
	int		max_index;

	if (!texture || !texture->data_addr)
		return (0);
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel_data = (int *)texture->data_addr;
	pixel_index = y * (texture->size_line / (int) sizeof(int)) + x;
	max_index = texture->height * (texture->size_line / (int) sizeof(int));
	if (pixel_index < 0 || pixel_index >= max_index)
		return (0);
	return (pixel_data[pixel_index]);
}

// selects the correct texture (N/S/E/W) based on which wall was hit
t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->config.textures[EAST]);
		else
			return (&game->config.textures[WEST]);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->config.textures[SOUTH]);
		else
			return (&game->config.textures[NORTH]);
	}
}
