/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:35:17 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/26 22:37:38 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		end_program(game);
	if (keycode == W_KEY)
		game->key_w = true;
	if (keycode == A_KEY)
		game->key_a = true;
	if (keycode == S_KEY)
		game->key_s = true;
	if (keycode == D_KEY)
		game->key_d = true;
	if (keycode == LEFT_KEY)
		game->key_left = true;
	if (keycode == RIGHT_KEY)
		game->key_right = true;
	return (0);
}

static int	on_keyrelease(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->key_w = false;
	if (keycode == A_KEY)
		game->key_a = false;
	if (keycode == S_KEY)
		game->key_s = false;
	if (keycode == D_KEY)
		game->key_d = false;
	if (keycode == LEFT_KEY)
		game->key_left = false;
	if (keycode == RIGHT_KEY)
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
	draw_screen(game); // Draw floor and ceiling
	raycast_loop(game); // Draw walls with raycasting
	// draw_minimap(game);
	mlx_put_image_to_window(game->mlx_connection, game->mlx_win, game->img, 0, 0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx_win, 2, 1L << 0, on_keypress, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, on_keyrelease, game);
	mlx_hook(game->mlx_win, 17, 0, end_program, game); // 'x' button
	mlx_loop_hook(game->mlx_connection, render_loop, game);
	mlx_loop(game->mlx_connection);
	// mlx_loop should be called separately when ready to start game loop
}