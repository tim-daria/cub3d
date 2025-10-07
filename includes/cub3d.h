#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_env.h"

// check_cub.c:
bool	is_valid_cub_file(char *filename);
// check_cub_utils.c:
bool	has_map_last(char *filename);
// error_handlers.c:
void	print_error(char *msg);

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