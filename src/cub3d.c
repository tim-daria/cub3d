/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:39:58 by dtimofee          #+#    #+#             */
/*   Updated: 2025/11/08 00:15:44 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_config(t_game *game)
{
	printf("Config:\nTextures:\n");
	for (int i = 0; i <= EAST; i++)
	{
		printf("Path: %s, img_ptr: %p, data_addr: %p,\nwidth: %i, height: %i, bpp: %i, size_line: %i, endian: %i\n",
			game->config.textures[i].texture_path, game->config.textures[i].img_ptr,
			game->config.textures[i].data_addr, game->config.textures[i].width,
			game->config.textures[i].height, game->config.textures[i].bpp,
			game->config.textures[i].size_line, game->config.textures[i].endian);
	}
	printf("Floor color: %i\n", game->config.floor_color);
	printf("Ceiling color: %i\n", game->config.ceiling_color);
}

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
	print_config(&game);
	setup_hooks(&game);
	end_program(&game);
	return (0);
}
