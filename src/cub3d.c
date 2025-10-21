/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:39:58 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/21 17:23:29 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Main function that initializes the game and starts the MLX loop
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!init_data(&game))
		return (1);
	if (!start_game(&game, argv[1]))
	{
		printf("❌ Failed to initialize game\n");
		return (1);
	}
	
	/* Run comprehensive parsing test */
	if (!test_parsing_complete(&game, argv[1]))
	{
		printf("❌ Testing failed\n");
		end_program(&game);
		return (1);
	}
	
	printf("✅ All tests completed successfully!\n");
	printf("🎮 Game ready - MLX integration can be added next.\n\n");
	end_program(&game);
	return (0);
}
