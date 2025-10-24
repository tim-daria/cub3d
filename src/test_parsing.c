/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 22:00:00 by tsemenov          #+#    #+#             */
/*   Updated: 2025/10/21 17:23:33 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_separator(char *title)
{
	int	i;
	int	len;
	int	padding;

	len = ft_strlen(title);
	padding = (60 - len) / 2;
	
	printf("\n");
	i = 0;
	while (i < 60)
	{
		printf("=");
		i++;
	}
	printf("\n");
	
	i = 0;
	while (i < padding)
	{
		printf(" ");
		i++;
	}
	printf("%s", title);
	i = 0;
	while (i < padding)
	{
		printf(" ");
		i++;
	}
	printf("\n");
	
	i = 0;
	while (i < 60)
	{
		printf("=");
		i++;
	}
	printf("\n");
}

static void	print_config_validation(t_game *game)
{
	bool	all_valid;
	int		i;

	all_valid = true;
	
	printf("CONFIGURATION VALIDATION:\n");
	printf("-------------------------\n");
	
	/* Check textures */
	printf("Textures: ");
	i = NORTH;
	while (i <= EAST)
	{
		if (!game->config.textures[i])
		{
			all_valid = false;
			break;
		}
		i++;
	}
	printf(all_valid ? "✅ All present\n" : "❌ Missing textures\n");
	
	/* Check colors */
	printf("Colors:   ");
	if (game->config.floor_color == -1 || game->config.ceiling_color == -1)
	{
		all_valid = false;
		printf("❌ Missing colors\n");
	}
	else
		printf("✅ All present\n");
	
	/* Check map */
	printf("Map:      ");
	if (!game->map.map || game->map.height <= 0)
	{
		all_valid = false;
		printf("❌ No map data\n");
	}
	else
		printf("✅ Map loaded (%dx%d)\n", game->map.width, game->map.height);
	
	/* Check player */
	printf("Player:   ");
	if (game->p.x == -1 || game->p.y == -1 || game->p.view == '\0')
	{
		all_valid = false;
		printf("❌ Player not found\n");
	}
	else
		printf("✅ Found at (%d,%d) facing '%c'\n",
			game->p.x, game->p.y, game->p.view);	printf("\nOVERALL: %s\n", all_valid ? "✅ READY TO PLAY" : "❌ CONFIGURATION INCOMPLETE");
}

static void	print_textures(t_game *game)
{
	char	*directions[] = {"NORTH", "SOUTH", "WEST", "EAST"};
	int		i;

	print_separator("TEXTURE CONFIGURATION");
	
	i = NORTH;
	while (i <= EAST)
	{
		printf("%-6s: %s\n", directions[i], 
			game->config.textures[i] ? game->config.textures[i] : "❌ NOT SET");
		i++;
	}
	
	printf("\nTexture File Validation:\n");
	i = NORTH;
	while (i <= EAST)
	{
		if (game->config.textures[i])
		{
			int fd = open_file(game->config.textures[i]);
			if (fd >= 0)
			{
				printf("  %s: ✅ File accessible\n", directions[i]);
				close(fd);
			}
			else
				printf("  %s: ❌ File not accessible\n", directions[i]);
		}
		i++;
	}
}

static void	print_colors(t_game *game)
{
	print_separator("COLOR CONFIGURATION");
	
	if (game->config.floor_color != -1)
	{
		printf("FLOOR:   0x%06X (RGB: %3d, %3d, %3d)\n",
			game->config.floor_color,
			(game->config.floor_color >> 16) & 0xFF,
			(game->config.floor_color >> 8) & 0xFF,
			game->config.floor_color & 0xFF);
	}
	else
		printf("FLOOR:   ❌ NOT SET\n");
	
	if (game->config.ceiling_color != -1)
	{
		printf("CEILING: 0x%06X (RGB: %3d, %3d, %3d)\n",
			game->config.ceiling_color,
			(game->config.ceiling_color >> 16) & 0xFF,
			(game->config.ceiling_color >> 8) & 0xFF,
			game->config.ceiling_color & 0xFF);
	}
	else
		printf("CEILING: ❌ NOT SET\n");
}

static void	print_map_info(t_game *game)
{
	int	i;
	int	wall_count;
	int	empty_count;
	int	player_count;

	print_separator("MAP INFORMATION");
	
	if (!game->map.map)
	{
		printf("❌ No map data loaded\n");
		return;
	}
	
	printf("Dimensions: %d x %d\n", game->map.width, game->map.height);
	printf("Player:     (%d, %d) facing '%c'\n", 
		game->p.x, game->p.y, game->p.view);
	
	/* Count map elements */
	wall_count = 0;
	empty_count = 0;
	player_count = 0;
	
	i = 0;
	while (i < game->map.height)
	{
		int j = 0;
		while (game->map.map[i] && game->map.map[i][j])
		{
			if (game->map.map[i][j] == '1')
				wall_count++;
			else if (game->map.map[i][j] == '0')
				empty_count++;
			else if (ft_strchr("NSEW", game->map.map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	
	printf("Elements:   %d walls, %d spaces, %d players\n", 
		wall_count, empty_count, player_count);
}

static void	print_map_visual(t_game *game)
{
	int	i;

	print_separator("MAP VISUALIZATION");
	
	if (!game->map.map)
	{
		printf("❌ No map to display\n");
		return;
	}
	
	printf("Legend: 1=Wall, 0=Empty, N/S/E/W=Player, ' '=Space\n\n");
	
	i = 0;
	while (i < game->map.height && game->map.map[i])
	{
		printf("  %2d: [%s]\n", i, game->map.map[i]);
		i++;
	}
}

bool	test_parsing_complete(t_game *game, char *filename)
{
	if (!game)
	{
		printf("❌ ERROR: No game data to test\n");
		return (false);
	}
	
	printf("\n");
	printf("╔══════════════════════════════════════════════════════════╗\n");
	printf("║                    CUB3D PARSING TEST                    ║\n");
	printf("║                     File: %-27s ║\n", filename);
	printf("╚══════════════════════════════════════════════════════════╝\n");
	
	print_config_validation(game);
	print_textures(game);
	print_colors(game);
	print_map_info(game);
	print_map_visual(game);
	
	print_separator("TEST COMPLETE");
	printf("All parsing data displayed above.\n");
	printf("Check for ❌ markers to identify any issues.\n\n");
	
	return (true);
}