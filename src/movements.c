/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:16:10 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/27 15:58:20 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_pos(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 1 || map_x > game->map.width - 1
		|| map_y < 1 || map_y > game->map.height - 1)
		return (false);
	if (game->map.map[map_y][map_x] == '1')
		return (false);
	return (true);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.dir_x * MOVE_SPEED;
	new_y = game->p.pos_y + game->p.dir_y * MOVE_SPEED;
	if (is_valid_pos(game, new_x, new_y))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
	printf("DEBUG: player moved to [%f, %f]\n", game->p.pos_x, game->p.pos_y);
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.dir_x * MOVE_SPEED;
	new_y = game->p.pos_y - game->p.dir_y * MOVE_SPEED;
	if (is_valid_pos(game, new_x, new_y))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
	}
	printf("DEBUG: player moved to [%f, %f]\n", game->p.pos_x, game->p.pos_y);
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x + game->p.dir_y * MOVE_SPEED;
	new_y = game->p.pos_y - game->p.dir_x * MOVE_SPEED;
	if (is_valid_pos(game, new_x, new_y))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
		// game->p.angle -= ROT_SPEED;
	}
	printf("DEBUG: player moved to [%f, %f]\n", game->p.pos_x, game->p.pos_y);
	// printf("DEBUG: player slightly rotated, the angle is %f\n", game->p.angle);
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->p.pos_x - game->p.dir_y * MOVE_SPEED;
	new_y = game->p.pos_y + game->p.dir_x * MOVE_SPEED;
	if (is_valid_pos(game, new_x, new_y))
	{
		game->p.pos_x = new_x;
		game->p.pos_y = new_y;
		// game->p.angle += ROT_SPEED;
	}
	printf("DEBUG: player moved to [%f, %f]\n", game->p.pos_x, game->p.pos_y);
	// printf("DEBUG: player slightly rotated, the angle is %f\n", game->p.angle);
}
