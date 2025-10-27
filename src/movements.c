/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-24 15:25:31 by dtimofee          #+#    #+#             */
/*   Updated: 2025-10-24 15:25:31 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	go_up(t_game *game)
{
	double	x;
	double	y;

	x = game->p.pos_x;
	y = game->p.pos_y;
	if (y > 1 && game->map.map[(int)y - 2][(int)x] != ' ')
	{
		if (game->map.map[(int)y - 1][(int)x] == '1')
			y -= 2;
		else
			y--;
		game->p.pos_x = x;
		game->p.pos_y = y;
		game->map.map[(int)y][(int)x] = game->p.view;
	}
}

static void	go_down(t_game *game)
{
	double	x;
	double	y;

	x = game->p.pos_x;
	y = game->p.pos_y;
	if (y < game->map.height - 2 && game->map.map[(int)y + 2][(int)x] != ' ')
	{
		if (game->map.map[(int)y + 1][(int)x] == '1')
			y += 2;
		else
			y++;
		game->p.pos_x = x;
		game->p.pos_y = y;
		game->map.map[(int)y][(int)x] = game->p.view;
	}
}

static void	go_right(t_game *game)
{
	double	x;
	double	y;

	x = game->p.pos_x;
	y = game->p.pos_y;
	if (x < game->map.width - 2 && game->map.map[(int)y][(int)x + 2] != ' ')
	{
		if (game->map.map[(int)y][(int)x + 1] == '1')
			x += 2;
		else
			x++;
		game->p.pos_x = x;
		game->p.pos_y = y;
		game->map.map[(int)y][(int)x] = game->p.view;
	}
}

static void	go_left(t_game *game)
{
	double	x;
	double	y;

	x = game->p.pos_x;
	y = game->p.pos_y;
	if (x > 1 && game->map.map[(int)y][(int)x - 2] != ' ')
	{
		if (game->map.map[(int)y][(int)x - 1] == '1')
			x -= 2;
		else
			x--;
		game->p.pos_x = x;
		game->p.pos_y = y;
		game->map.map[(int)y][(int)x] = game->p.view;
	}
}

int	handle_movements(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
	{
		end_program(game);
		return (0);
	}
	else if (keysym == XK_w || keysym == XK_W)
		go_up(game);
	else if (keysym == XK_s || keysym == XK_S)
		go_down(game);
	else if (keysym == XK_d || keysym == XK_D)
		go_right(game);
	else if (keysym == XK_a || keysym == XK_A)
		go_left(game);
	draw_minimap(game);
	return (0);
}
