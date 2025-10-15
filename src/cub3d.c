/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:39:58 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/15 22:37:32 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Main function that initializes the game and starts the MLX loop
int	main(int argc, char **argv)
{
	t_game	*game;

	if (!init_data(&game))
		return (1);
	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!start_game(&game, argv[1]))
	{
		printf("❌ Failed to initialize game\n");
		return (1);
	}
	/* Run comprehensive parsing test */
	if (!test_parsing_complete(game, argv[1]))
	{
		printf("❌ Testing failed\n");
		end_program(game);
		return (1);
	}
	printf("✅ All tests completed successfully!\n");
	printf("🎮 Game ready - MLX integration can be added next.\n\n");
	end_program(game);
	return (0);
		// data.mlx_connection = mlx_init();
		// data.mlx_win = mlx_new_window(data.mlx_connection,
		// 		BLOCK_SIZE * data.map.block_width,
		// 		BLOCK_SIZE * data.map.block_height, "cub3d");
		// if (data.mlx_win == NULL)
		// 	perror("Error");
		//draw_map(&data);
		//mlx_hook(data.mlx_win, 2, 1L << 0, handle_movements, &data);
		// mlx_hook(data.mlx_win, DestroyNotify, NoEventMask, end_program, &data);
		// mlx_loop(data.mlx_connection);
}
