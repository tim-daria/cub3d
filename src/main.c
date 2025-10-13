// #include "cub3d.h"

static void	print_config(t_config *config)
{
    printf("\n=== CONFIG PARSED ===\n");
    
    /* Print textures */
    printf("Textures:\n");
    printf("  NORTH: %s\n", config->textures[NORTH] ? config->textures[NORTH] : "NULL");
    printf("  SOUTH: %s\n", config->textures[SOUTH] ? config->textures[SOUTH] : "NULL");
    printf("  WEST:  %s\n", config->textures[WEST] ? config->textures[WEST] : "NULL");
    printf("  EAST:  %s\n", config->textures[EAST] ? config->textures[EAST] : "NULL");
    
    /* Print colors */
    printf("Colors:\n");
    if (config->floor_color != -1)
        printf("  FLOOR:   0x%06X (R:%d G:%d B:%d)\n", 
            config->floor_color,
            (config->floor_color >> 16) & 0xFF,
            (config->floor_color >> 8) & 0xFF,
            config->floor_color & 0xFF);
    else
        printf("  FLOOR:   Not set\n");
        
    if (config->ceiling_color != -1)
        printf("  CEILING: 0x%06X (R:%d G:%d B:%d)\n", 
            config->ceiling_color,
            (config->ceiling_color >> 16) & 0xFF,
            (config->ceiling_color >> 8) & 0xFF,
            config->ceiling_color & 0xFF);
    else
        printf("  CEILING: Not set\n");
    
    printf("==================\n");
}

static int	test_config_parsing(char *filename)
{
	t_config	*config;
	int			fd;
	char		*line;

	config = init_config();
	if (!config)
	{
		print_error("init failed");
		return (0);
	}
	fd = open_file(filename);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_config_line(line))
		{
			if (parse_config_line(line, config))
				printf("Success\n");
			else
				printf("Fail\n");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	print_config(config);
	free_config(config);
	return (1);
}

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	// (void)argv;

// 	// printf("Cub3D starting...\n");
// 	if (!is_valid_cub_file(argv[1]))
// 		return (1);
// 	return (0);
// }
