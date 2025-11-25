NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
BOLD = \033[1m
RESET = \033[0m

UNAME_S := $(shell uname -s)

MLX_DIR = libs/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
# got minilibx from here: https://github.com/42paris/minilibx-linux/tree/master

ifeq ($(UNAME_S), Linux)
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
	INCLUDES = -I./includes -I$(MLX_DIR) -I$(LIBFT_DIR)
else ifeq ($(UNAME_S), Darwin)
	MLX_LIB = $(MLX_DIR)/libmlx_Darwin.a
	MLX_FLAGS = -L$(MLX_DIR) -L/opt/X11/lib -L/usr/X11/include/../lib -lmlx -lXext -lX11 -lm -framework OpenGL -framework AppKit
	INCLUDES = -I./includes -I$(MLX_DIR) -I$(LIBFT_DIR) -I/opt/X11/include -I/usr/X11/include
else
	$(error Unsupported operating system: $(UNAME_S))
endif

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src/
OBJ_DIR = obj/
SRC_FILES =\
		cub3d.c \
		check_cub.c \
		check_cub_utils.c \
		check_cub_utils2.c \
		cleanups.c \
		check_characters.c \
		parse_map.c \
		parse_map_utils.c \
		check_walls.c \
		check_xpm.c \
		error_handlers.c \
		init_config.c \
		parse_colors.c \
		parse_textures.c \
		parse_config.c \
		init_data.c \
		draw_screen.c \
		parse_player.c \
		movements.c \
		movements_collision.c \
		rotations.c \
		hooks.c \
		raycasting_loop.c \
		raycasting_dda.c \
		minimap.c \
		textures.c \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

OBJ_FLAG = .cache_exists

all: $(NAME)

$(MLX_DIR):
	@echo "$(CYAN)Cloning minilibX...$(RESET)"
	@mkdir -p libs
	@git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1

$(MLX_LIB): $(MLX_DIR)
	@echo "$(YELLOW)Building minilibX...$(RESET)"
	@cd $(MLX_DIR) && ./configure >/dev/null 2>&1 && make >/dev/null 2>&1
	@echo "$(GREEN)minilibX ready$(RESET)"


$(LIBFT): $(LIBFT_DIR)
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C$(LIBFT_DIR) >/dev/null 2>&1
	@echo "$(GREEN)Libft ready$(RESET)"

$(OBJ_DIR):
	@mkdir obj

$(OBJ_FLAG):
	@touch $(OBJ_FLAG)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_FLAG)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJ_DIR) $(OBJS)
	@echo "$(YELLOW)Compiling...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(BOLD)$(GREEN)CUB3D ready ✓$(RESET)"
	@echo "$(BLUE)To run valgrind do \"make valg MAP=path_to_map\"$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJ_FLAG)
	@echo "$(CYAN)minilibX: in progress...$(RESET)"
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean >/dev/null 2>&1 || true; fi
	@echo "$(CYAN)libft: in progress...$(RESET)"
	@make -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@echo "$(GREEN)clean done$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CYAN)minilibX: in progress...$(RESET)"
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		make -C $(MLX_DIR) fclean >/dev/null 2>&1|| \
		make -C $(MLX_DIR) clean >/dev/null 2>&1 || \
		rm -f $(MLX_DIR)/%.a $(MLX_DIR)/%.o >/dev/null 2>&1|| true; \
	fi
	@echo "$(CYAN)libft: in progress...$(RESET)"
	@make -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@echo "$(GREEN)fclean done$(RESET)"

re: fclean all

MAP ?= ./maps/map.cub

valg: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(MAP)

.PHONY: all clean fclean re valg
