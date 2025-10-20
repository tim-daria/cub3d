#ifndef CUB3D_ENV_H
# define CUB3D_ENV_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
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
# define PI 3.141592653589793
enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
};

typedef struct s_config
{
	char	*textures[4];
	int		floor_color;
	int		ceiling_color;
}	t_config;

typedef struct s_player
{
	char	view;
	double	fov;
	double	angle;
	double	pos_y;
	double	pos_x;
	double	dir_y;
	double	dir_x;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_game
{
	t_config	*config;
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
