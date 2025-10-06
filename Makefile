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


SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

OBJ_FLAG = .cache_exists

all: $(NAME)

$(MLX_LIB): $(MLX_DIR)
	@echo "Building minilibX..."
	@cd $(MLX_DIR) && ./configure && make


$(LIBFT): $(LIBFT_DIR)
	@echo "Building libft..."
	@make -C$(LIBFT_DIR)
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
	@echo "FdF ready"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OBJ_FLAG)
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean 2>/dev/null || true; fi
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@if [ -f $(MLX_DIR)/Makefile ]; then \
		make -C $(MLX_DIR) fclean 2>/dev/null || \
		make -C $(MLX_DIR) clean 2>/dev/null || \
		rm -f $(MLX_DIR)/%.a $(MLX_DIR)/%.o 2>/dev/null || true; \
	fi
	@make -C $(LIBFT_DIR) fclean

re: fclean all

debug:
	@echo "Detected OS: $(UNAME_S)"
	@echo "Detected Architecture: $(UNAME_M)"
	@echo "Using MinilibX directory: $(MLX_DIR)"

.PHONY: all clean fclean re debug