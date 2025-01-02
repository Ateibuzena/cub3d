CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR = /sgoinfre/students/azubieta/azubieta/Utils/MLX42
MLX42 = $(MLX42_DIR)/libmlx42.a

INCLUDES = -I$(LIBFT_DIR) -I$(MLX42_DIR)/include/MLX42
SRC_DIR = ./src

SRCS = $(SRC_DIR)/main.c \
    	#$(SRC_DIR)/parser.c \
       #$(SRC_DIR)/executor.c \
       #$(SRC_DIR)/builtins.c \
       #$(SRC_DIR)/signals.c \
       #$(SRC_DIR)/ft_strtok.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = cub3D

# Colores
CYAN   		= \033[1;36m
LILAC       = \033[1;35m
DARK_BLUE   = \033[1;34m
GREEN       = \033[1;32m
RESET       = \033[0m

# Reglas
all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	@printf "$(CYAN)[Building Main] Compiling $(NAME)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -v $(LIBFT) $(MLX42) -ldl -lglfw -pthread -lm -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(LILAC)[Compiling] $(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(DARK_BLUE)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(LILAC)[Library] Building libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

$(MLX42):
	@printf "$(LILAC)[Library] Building MLX42...\n$(RESET)"
	@$(MAKE) -C $(MLX42_DIR)
	@$(MAKE) -C $(MLX42_DIR) clean

clean:
	@printf "$(LAVENDER)[Cleaning] Removing object files cub3D\n$(RESET)"
	@rm -rf $(OBJ_DIR)/*.o

fclean: clean
	@printf "$(LAVENDER)[Cleaning] Removing $(NAME), $(LIBFT) & $(MLX42)\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX42_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
