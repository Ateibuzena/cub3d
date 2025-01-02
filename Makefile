CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR = /home/azubieta/sgoinfre/azubieta/MLX42
MLX42 = $(MLX42_DIR)/libmlx42.a

INCLUDES = -I$(LIBFT_DIR) -I$(MLX42_DIR)
SRC_DIR = ./src

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/executor.c \
       $(SRC_DIR)/builtins.c \
       $(SRC_DIR)/signals.c \
       $(SRC_DIR)/ft_strtok.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = cub3D

RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
       @printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) -ldl -lglfw -pthread -lm -o $(NAME)
       @printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

$(MLX42):
	$(MAKE) -C $(MLX42_DIR)
	$(MAKE) -C $(MLX42_DIR) clean

clean:
       @printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	rm -rf $(OBJ_DIR)/*.o
       @printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
       @printf "$(RED)[Cleaning] Removing $(NAME), $(LIBFT) & $(MLX42)\n$(RESET)"
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX42_DIR) fclean
	rm -f $(NAME)
       @printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all
.PHONY: all clean fclean re bonus