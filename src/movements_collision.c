/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_collision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsemenov <tsemenov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:18:12 by tsemenov          #+#    #+#             */
/*   Updated: 2025/11/12 00:32:34 by tsemenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Check collision circle around player
// Check 4 cardinal directions & diagonals
bool	is_too_close(t_game *game, double x, double y)
{
	if (game->map.map[(int)(y - COLLISION_RADIUS)][(int)x] == '1')
		return (true);
	if (game->map.map[(int)(y + COLLISION_RADIUS)][(int)x] == '1')
		return (true);
	if (game->map.map[(int)y][(int)(x - COLLISION_RADIUS)] == '1')
		return (true);
	if (game->map.map[(int)y][(int)(x + COLLISION_RADIUS)] == '1')
		return (true);
	if (game->map.map[(int)(y - COLLISION_RADIUS)][(int)(x - COLLISION_RADIUS)] == '1')
		return (true);
	if (game->map.map[(int)(y - COLLISION_RADIUS)][(int)(x + COLLISION_RADIUS)] == '1')
		return (true);
	if (game->map.map[(int)(y + COLLISION_RADIUS)][(int)(x - COLLISION_RADIUS)] == '1')
		return (true);
	if (game->map.map[(int)(y + COLLISION_RADIUS)][(int)(x + COLLISION_RADIUS)] == '1')
		return (true);
	return (false);
}