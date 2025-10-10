/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-09 10:26:02 by dtimofee          #+#    #+#             */
/*   Updated: 2025-10-09 10:26:02 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_ENV_H
# define CUB3D_ENV_H

# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line.h"
# include "../libs/libft/ft_printf.h"

# define WIDTH 1024
# define HEIGHT 768
# define BLOCK_SIZE 64

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_player
{
	char	view;
	int		y;
	int		x;
}	t_player;

// typedef struct s_textures {
// 	t_position	player;
// 	t_position	exit;
// 	t_position	collectable;
// }	t_textures;

typedef struct s_game
{
	//t_textures	textures;
	t_map		map;
	t_player	p;
	void		*mlx_connection;
	void		*mlx_win;
	void		*img;
	// int			img_width;
	// int			img_height;
	//int			count_movements;
}	t_game;

#endif
