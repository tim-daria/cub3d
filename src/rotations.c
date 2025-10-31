/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:01:04 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/27 01:45:41 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;

	// game->p.angle -= ROT_SPEED;
	old_dir_x = game->p.dir_x;
	game->p.dir_x = game->p.dir_x * cos(-ROT_SPEED) - game->p.dir_y * sin(-ROT_SPEED);
	game->p.dir_y = old_dir_x * sin(-ROT_SPEED) + game->p.dir_y * cos(-ROT_SPEED);
	printf("DEBUG: player rotated to [%f, %f]\n", game->p.dir_x, game->p.dir_y);
	// printf("DEBUG: the angle is %f\n", game->p.angle);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;

	// game->p.angle += ROT_SPEED;
	old_dir_x = game->p.dir_x;
	game->p.dir_x = game->p.dir_x * cos(ROT_SPEED) - game->p.dir_y * sin(ROT_SPEED);
	game->p.dir_y = old_dir_x * sin(ROT_SPEED) + game->p.dir_y * cos(ROT_SPEED);
	printf("DEBUG: player rotated to [%f, %f]\n", game->p.dir_x, game->p.dir_y);
	// printf("DEBUG: the angle is %f\n", game->p.angle);
}