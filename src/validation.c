//  Your program must take as a first argument a scene description file with the .cub
// extension.
// ◦ The map must be composed of only 6 possible characters: 0 for an empty space,
// 1 for a wall, and N,S,E or W for the player’s start position and spawning
// orientation.
// This is a simple valid map:
// 111111
// 100101
// 101001
// 1100N1
// 111111
// ◦ The map must be closed/surrounded by walls, if not the program must return
// an error.
// ◦ Except for the map content, each type of element can be separated by one or
// more empty lines.
// ◦ Except for the map content which always has to be the last, each type of
// element can be set in any order in the file.
// ◦ Except for the map, each type of information from an element can be separated
// by one or more spaces.
// ◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
// map and are up to you to handle. You must be able to parse any kind of map,
// as long as it respects the rules of the map.

//  open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit, gettimeofday.
// • All functions of the math
// library (-lm man man 3 math).
// • gettimeofday()
// • All functions of the MinilibX
// library.

// valid file:
// they exist? open?

// NO ./textures/north.xpm
// SO ./textures/south.xpm
// WE ./textures/west.xpm
// EA ./textures/east.xpm

// F 220,100,0
// C 225,30,0

// 111111
// 100001
// 101N01
// 100001
// 111111

// .cub?

// are NO, SO, WE, EA present?
// valid file links?
// F, C present?
// color codes present? valid? (convert)

// map -> separate file:
// 0, 1, N/S/W/E/?
// closed walls?
// one player?

typedef struct s_map
{
	int		width;
	int		height;
	char	*grid;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		width;
	int		height;
	int		line_len;
}	t_texture;

typedef struct s_env
{
	int			floor_color;
	int			ceiling_color;
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	t_map		map;
	t_texture	textures[4];
} t_env;