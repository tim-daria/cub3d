/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:35:17 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/10 13:47:03 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		end_program(game);
	if (keycode == XK_w)
		game->key_w = true;
	if (keycode == XK_a)
		game->key_a = true;
	if (keycode == XK_s)
		game->key_s = true;
	if (keycode == XK_d)
		game->key_d = true;
	if (keycode == XK_Left)
		game->key_left = true;
	if (keycode == XK_Right)
		game->key_right = true;
	return (0);
}

static int	on_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->key_w = false;
	if (keycode == XK_a)
		game->key_a = false;
	if (keycode == XK_s)
		game->key_s = false;
	if (keycode == XK_d)
		game->key_d = false;
	if (keycode == XK_Left)
		game->key_left = false;
	if (keycode == XK_Right)
		game->key_right = false;
	return (0);
}

static void	process_movements(t_game *game)
{
	if (game->key_w)
		move_forward(game);
	if (game->key_a)
		move_left(game);
	if (game->key_s)
		move_backward(game);
	if (game->key_d)
		move_right(game);
	if (game->key_left)
		rotate_left(game);
	if (game->key_right)
		rotate_right(game);
}

static int	render_loop(t_game *game)
{
	process_movements(game);
	draw_screen(game);
	raycast_loop(game);
	draw_minimap(game, game->map.map);
	mlx_put_image_to_window(game->mlx_connection,
		game->mlx_win, game->img, 0, 0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 1L << 0, on_keypress, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, on_keyrelease, game);
	mlx_hook(game->mlx_win, 6, 1L << 6, on_mouse_move, game);
	mlx_hook(game->mlx_win, DestroyNotify, NoEventMask, end_program, game);
	mlx_loop_hook(game->mlx_connection, render_loop, game);
	mlx_loop(game->mlx_connection);
}
