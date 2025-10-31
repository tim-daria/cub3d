#include "cub3d.h"

// Sets the player's angle and direction vector based on their view direction
static void determine_angle_and_dir_vector(t_player *p)
{
	if (p->view == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;  // North = toward row 0 (upward)
		// p->angle = 3 * PI / 2; // 270 deg
	}
	else if (p->view == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;  // South = toward higher rows (downward)
		// p->angle = PI / 2; // 90 deg
	}
	else if (p->view == 'E')
	{
		p->dir_x = 1;  // East = toward higher columns (right)
		p->dir_y = 0;
		// p->angle = PI;
	}
	else if (p->view == 'W')
	{
		p->dir_x = -1;  // West = toward lower columns (left)
		p->dir_y = 0;
		// p->angle = 0;
	}
}

//Searches the map for the player's starting position and
//returns the character representing their view direction (N, S, E, or W).
static char	find_player(t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (map.map[y][x] == 'N' || map.map[y][x] == 'S'
				|| map.map[y][x] == 'E' || map.map[y][x] == 'W')
				break ;
			x++;
		}
		if (x < map.width)
			break ;
		y++;
	}
	return (map.map[y][x]);
}

// Finds the player's position in the map and sets the player's
// view, x, and y coordinates in the t_player structure.
void	find_player_pos(t_map map, t_player *p)
{
	p->view = find_player(map);
	determine_angle_and_dir_vector(p);
	p->pos_y = 0;
	while (p->pos_y < map.height)
	{
		p->pos_x = 0;
		while (p->pos_x < map.width)
		{
			if (map.map[(int)p->pos_y][(int)p->pos_x] == p->view)
			{
				p->pos_x += 0.5;
				p->pos_y += 0.5;
				return ;
			}
			p->pos_x++;
		}
		p->pos_y++;
	}
}