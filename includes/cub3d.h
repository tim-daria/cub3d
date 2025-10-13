#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_env.h"

// check_cub.c:
bool		is_valid_cub_file(char *filename);
// int		try_open(char *filename);
int			open_file(char *src);
// check_cub_utils.c:
bool		has_map_last(char *filename);
bool		is_config_line(char *line);
// check_cub_utils2.c:
bool		has_all_sides(char *filename);
// cleanups.c:
void		free_2d_arr(char **arr);
int			ft_strcmp(char *s1, char *s2);
// error_handlers.c:
void		print_error(char *msg);
// init_config.c:
t_config	*init_config(void);
void		free_config(t_config *config);
// parse_colors.c:
bool		check_and_copy_color(char *id, char *arg, t_config *config);
// parse_config.c:
bool		parse_config_line(char *line, t_config *config);
// parse_textures.c:
bool		copy_texture(char *id, char *arg, t_config *config);
int			ft_strcmp(char *s1, char *s2);

//void	draw_map(t_mlx_data *data);
//int		handle_movements(int keysym, t_mlx_data *data);
int		count_player(t_map map);
int		map_height(int fd);
// int		end_program(t_mlx_data *data);
// void	init_data(t_mlx_data *data);
void	free_map(char **map, int row);
int		check_characters(t_map *map);
int		check_mapfilename(char *filename);
int		check_walls(t_map *map);


#endif