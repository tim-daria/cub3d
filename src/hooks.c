/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:35:17 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/27 16:59:51 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	on_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		end_program(game);
	if (keycode == XK_w)
		game->buttons.key_w = true;
	if (keycode == XK_a)
		game->buttons.key_a = true;
	if (keycode == XK_s)
		game->buttons.key_s = true;
	if (keycode == XK_d)
		game->buttons.key_d = true;
	if (keycode == XK_Left)
		game->buttons.key_left = true;
	if (keycode == XK_Right)
		game->buttons.key_right = true;
	return (0);
}

static int	on_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->buttons.key_w = false;
	if (keycode == XK_a)
		game->buttons.key_a = false;
	if (keycode == XK_s)
		game->buttons.key_s = false;
	if (keycode == XK_d)
		game->buttons.key_d = false;
	if (keycode == XK_Left)
		game->buttons.key_left = false;
	if (keycode == XK_Right)
		game->buttons.key_right = false;
	return (0);
}

static void	process_movements(t_game *game, t_button buttons)
{
	if (buttons.key_w)
		move_forward(game);
	if (buttons.key_a)
		move_left(game);
	if (buttons.key_s)
		move_backward(game);
	if (buttons.key_d)
		move_right(game);
	if (buttons.key_left)
		rotate_left(game);
	if (buttons.key_right)
		rotate_right(game);
}

static int	render_loop(t_game *game)
{
	int	current_width;
	int	current_height;

	mlx_get_screen_size(game->mlx_win, &current_width, &current_height);
	printf("%d - height, %d - width\n", current_height, current_width);
	fflush(0);
	if (current_height != game->win_height || current_width != game->win_width)
		recreate_screen(game, current_width, current_height);
	process_movements(game, game->buttons);
	draw_screen(game); // Draw floor and ceiling
	raycast_loop(game); // Draw walls with raycasting
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
