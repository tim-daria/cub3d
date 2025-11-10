/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 22:01:04 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 15:25:35 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;

	old_dir_x = game->p.dir_x;
	game->p.dir_x = game->p.dir_x * cos(-ROT_SPEED)
		- game->p.dir_y * sin(-ROT_SPEED);
	game->p.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ game->p.dir_y * cos(-ROT_SPEED);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;

	old_dir_x = game->p.dir_x;
	game->p.dir_x = game->p.dir_x * cos(ROT_SPEED)
		- game->p.dir_y * sin(ROT_SPEED);
	game->p.dir_y = old_dir_x * sin(ROT_SPEED)
		+ game->p.dir_y * cos(ROT_SPEED);
}

int	on_mouse_move(int x, int y, t_game *game)
{
	static int	last_x;
	double		delta_x;

	(void)y;
	delta_x = x - last_x;
	if (delta_x > 0)
		rotate_right(game);
	else if (delta_x < 0)
		rotate_left(game);
	last_x = x;
	return (0);
}
