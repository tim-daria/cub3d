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
# define FOV 66
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

# define ESC_KEY	65307
# define W_KEY		119
# define A_KEY		97
# define S_KEY		115
# define D_KEY		100
# define LEFT_KEY	65361 // for rotation
# define RIGHT_KEY	65363 // for rotation

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
	double	angle;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_game
{
	t_config	config;
	t_map		map;
	t_player	p;
	void		*mlx_connection;
	void		*mlx_win;
	void		*img;
	char		*img_addr;
	int			bits_pp;
	int			line_len;
	int			endian;
	bool		key_w;
	bool		key_a;
	bool		key_s;
	bool		key_d;
	bool		key_left;
	bool		key_right;
	// int			img_width;
	// int			img_height;
	//int			count_movements;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	plane_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

#endif