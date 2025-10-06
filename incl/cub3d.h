/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:43:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/06 18:00:59 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

//# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include "Libft/libft.h"
# include <unistd.h>

# define BLOCK_SIZE 64

typedef struct s_map {
	char	**map;
	int		block_height;
	int		block_width;
}	t_map;

// typedef struct s_textures {
// 	t_position	player;
// 	t_position	exit;
// 	t_position	collectable;
// }	t_textures;

typedef struct s_mlx_data {
	//t_textures	textures;
	t_map		map;
	void		*mlx_connection;
	void		*mlx_win;
	void		*img;
	int			img_width;
	int			img_height;
	//int			count_movements;
}	t_mlx_data;

//void	draw_map(t_mlx_data *data);
//int		handle_movements(int keysym, t_mlx_data *data);
int		count_player(t_map map);
int		map_height(int fd);
int		end_program(t_mlx_data *data);
void	init_data(t_mlx_data *data);
void	free_map(char **map, int row);
int		check_characters(t_map *map);
int		check_mapfilename(char *filename);
int		check_walls(t_map *map);

#endif
