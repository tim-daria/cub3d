#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../libs/minilibx-linux/mlx.h"
// # include "../libs/libft/includes/libft.h"
// # include "../libs/libft/includes/get_next_line.h"
// # include "../libs/libft/includes/ft_printf.h"

# define WIDTH 1024
# define HEIGHT 768
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