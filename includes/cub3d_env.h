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
# define PI 3.141592653589793
# define FOV 60
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define TILE_SIZE 7
# define LIGHT_GREEN 0x003333
# define GREEN 0x00FF00
# define BLACK 0x888888
# define GRAY 0x000000

enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
};

typedef struct s_game	t_game;

typedef struct	s_texture
{
	char	*texture_path;
	void	*img_ptr;
	char	*data_addr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_config
{
	t_texture	textures[4];
	int			floor_color;
	int			ceiling_color;
	t_game		*game;
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
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
}	t_ray;

#endif
