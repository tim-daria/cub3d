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

// for textures and color parsing:
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
// end of textures and colors parsing

typedef struct	s_player
{
	float	move_x;
	float	move_y;
	char	*direction;
}	t_player;

typedef struct	s_game
{
	t_config	*config;
	t_player	*player;
	void		*mlx_connection;
	void		*mlx_win;
	void		*img;
}	t_game;

// typedef struct s_mlx_data {
// 	//t_textures	textures;
// 	t_map		map;
// 	void		*mlx_connection;
// 	void		*mlx_win;
// 	void		*img;
// 	int			img_width;
// 	int			img_height;
// 	//int			count_movements;
// }	t_mlx_data;

// typedef struct s_textures {
// 	t_position	player;
// 	t_position	exit;
// 	t_position	collectable;
// }	t_textures;

typedef struct s_map {
	char	**map;
	int		block_height;
	int		block_width;
}	t_map;

#endif