/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:26:09 by dtimofee          #+#    #+#             */
/*   Updated: 2025/11/10 13:29:41 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "cub3d_env.h"

// check_cub.c:
bool		is_valid_cub_file(char *filename);
int			open_file(char *src);
// check_cub_utils.c:
bool		has_map_last(char *filename);
bool		is_config_line(char *line);
// check_cub_utils2.c:
bool		has_all_sides(char *filename);
bool		is_map_line(char *line);
// cleanups.c:
void		free_2d_arr(char **arr);
void		free_config(t_config *config);
void		clean_data(t_game *game);
int			end_program(t_game *game);
// draw_map.c:
void		put_pixel(t_game *game, int x, int y, int color);
bool		draw_screen(t_game *game);
// error_handlers.c:
bool		print_error(char *msg);
// hooks.c:
void		setup_hooks(t_game *game);
// init_config.c:
bool		parse_config(char *filename, t_game *game);
void		free_config(t_config *config);
// init_data.c:
bool		init_data(t_game *game);
bool		start_game(t_game *game, char *arg);
// movements.c:
void		move_forward(t_game *game);
void		move_backward(t_game *game);
void		move_left(t_game *game);
void		move_right(t_game *game);
// parse_colors.c:
bool		check_and_copy_color(char *id, char *arg, t_config *config);
// parse_config.c:
bool		parse_config_line(char *line, t_config *config);
// parse_textures.c:
bool		copy_texture(char *id, char *arg, t_config *config);
int			ft_strcmp(char *s1, char *s2);
//check_characters.c:
bool		check_characters(t_map *map);
//check_walls.c:
bool		surrounded_by_walls(t_map map, t_player p);
//parse_map.c:
bool		parse_map(char *filename, t_game *game);
//parse_map_utils.c:
void		map_height_width(int fd, t_map *map);
char		*skip_not_map(int fd);
bool		free_map(char **map, int row);
void		find_player_pos(t_map map, t_player *p);
int			count_len(char *line);
// parse_player.c:
void		find_player_pos(t_map map, t_player *p);

//minimap.c:
void		draw_minimap(t_game *game, char **map);

// rotations.c:
void		rotate_left(t_game *game);
void		rotate_right(t_game *game);
int			on_mouse_move(int x, int y, t_game *game);
// raycasting.c:
void		raycast_loop(t_game *game);

bool		test_parsing_complete(t_game *game, char *filename);

#endif
