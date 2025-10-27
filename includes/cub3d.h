/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:26:09 by dtimofee          #+#    #+#             */
/*   Updated: 2025/10/13 19:50:55 by tsemenov         ###   ########.fr       */
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
int			ft_strcmp(char *s1, char *s2);
// error_handlers.c:
bool		print_error(char *msg);
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
//check_characters.c:
bool	check_characters(t_map *map);
//check_walls.c:
bool	surrounded_by_walls(t_map map, t_player p);
//parse_map.c:
bool	parse_map(char *filename, t_game *game);
//parse_map_utils.c:
void	map_height_width(int fd, t_map *map);
char	*skip_not_map(int fd);
bool	free_map(char **map, int row);
void	find_player_pos(t_map map, t_player *p);
int		count_len(char *line);

int		end_program(t_game *game);
void	init_data(t_game *game);

//minimap.c:
void	draw_minimap(t_game *game);

//movements.c:
int		handle_movements(int keysym, t_game *game);
#endif
