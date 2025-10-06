/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:12:47 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/06 16:30:07 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "so_long.h"

// void	find_positions(t_mlx_data *data)
// {
// 	position(&data->textures.player, &data->map, 'P');
// 	position(&data->textures.exit, &data->map, 'E');
// }

// static char	*choose_texture(char c)
// {
// 	char	*filename;

// 	if (c == '1')
// 		filename = "textures/properwall64.xpm";
// 	else if (c == 'P')
// 		filename = "textures/player_Dora_transparent.xpm";
// 	else if (c == 'C')
// 		filename = "textures/proper_collectible64.xpm";
// 	else if (c == 'E')
// 		filename = "textures/properexit64.xpm";
// 	else
// 		filename = "textures/background64.xpm";
// 	return (filename);
// }

// void	draw_map(t_mlx_data *data)
// {
// 	int		x;
// 	int		y;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	y = 0;
// 	while (i < data->map.block_height)
// 	{
// 		j = 0;
// 		x = 0;
// 		while (j < data->map.block_width)
// 		{
// 			data->img = mlx_xpm_file_to_image(data->mlx_connection,
// 					choose_texture(data->map.map[i][j]),
// 					&data->img_width, &data->img_height);
// 			mlx_put_image_to_window(data->mlx_connection, data->mlx_win,
// 				data->img, x, y);
// 			mlx_destroy_image(data->mlx_connection, data->img);
// 			x += data->img_width;
// 			j++;
// 		}
// 		i++;
// 		y += data->img_height;
// 	}
// }
