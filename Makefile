NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

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
		error_handlers.c \
		init_config.c \
		parse_colors.c \
		parse_textures.c \
		parse_config.c \
		init_data.c \
		test_parsing.c \


SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

OBJ_FLAG = .cache_exists

all: $(NAME)

$(MLX_DIR):
	@echo "Cloning minilibX..."
	@mkdir -p libs
	@git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR) >/dev/null 2>&1

$(MLX_LIB): $(MLX_DIR)
	@echo "Building minilibX..."
	@cd $(MLX_DIR) && ./configure >/dev/null 2>&1 && make >/dev/null 2>&1
	@echo "minilibX ready"


$(LIBFT): $(LIBFT_DIR)
	@echo "Building libft..."
	@make -C$(LIBFT_DIR) >/dev/null 2>&1
	@echo "Libft ready"

$(OBJ_DIR):
	@mkdir obj

$(OBJ_FLAG):
	@touch $(OBJ_FLAG)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_FLAG)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(NAME): $(MLX_LIB) $(LIBFT) $(OBJ_DIR) $(OBJS)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "CUB3D ready"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJ_FLAG)
	@echo "minilibX: in progress..."
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean >/dev/null 2>&1 || true; fi
	@echo "libft: in progress..."
	@make -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@echo "clean done"

fclean: clean
	@rm -f $(NAME)
	@echo "minilibX: in progress..."
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		make -C $(MLX_DIR) fclean >/dev/null 2>&1|| \
		make -C $(MLX_DIR) clean >/dev/null 2>&1 || \
		rm -f $(MLX_DIR)/%.a $(MLX_DIR)/%.o >/dev/null 2>&1|| true; \
	fi
	@echo "libft: in progress..."
	@make -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@echo "fclean done"
# 	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
