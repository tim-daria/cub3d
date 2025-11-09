/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:04:59 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/09 15:50:32 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// which part of the wall block does ray hit? left - center - right
void	calc_wall_x(t_game *game, t_ray *ray)
{
	if (ray->side == 1)
		ray->wall_x = game->p.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	else if (ray->side == 0)
		ray->wall_x = game->p.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	ray->wall_x -= floor(ray->wall_x);
}

// which column of pixels to use from the texture to draw a vertical line
void	calc_tex_x(t_texture *texture, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * (double)texture->width);
	// Clamp before mirroring to handle wall_x == 1.0 edge case
	if (ray->tex_x >= texture->width)
		ray->tex_x = texture->width - 1;
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	// mirror SOUTH and WEST walls, so they appear correctly (otherwirse, thiy will be flipped on x-axis)
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		ray->tex_x = texture->width - ray->tex_x - 1;
}

//calculates how much to increment texture Y per screen pixel
void	calc_tex_step(t_texture *texture, t_ray *ray)
{
	ray->tex_step = 1.0 * texture->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->tex_step;
}
// retrieves a pixel color from texture data
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
	pixel_index = y * (texture->size_line / (int)sizeof(int)) + x;
	max_index = texture->height * (texture->size_line / (int)sizeof(int));
	if (pixel_index < 0 || pixel_index >= max_index)
		return (0);	
	return (pixel_data[pixel_index]);
}

// selects the correct texture (N/S/E/W) based on which wall was hit
t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0) // east or west
	{
		if (ray->ray_dir_x > 0) // moving right
			return (&game->config.textures[EAST]);
		else
			return (&game->config.textures[WEST]);
	}
	else // north or south
	{
		if (ray->ray_dir_y > 0) // moving down
			return (&game->config.textures[SOUTH]);
		else
			return (&game->config.textures[NORTH]);
	}
}