NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -IMLX42/include -I$(LIBFT_DIR) -g
LDFLAGS = -LMLX42/build -lmlx42 -lglfw -lm -ldl -pthread

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# 🎨 Colors
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
MAGENTA  = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m

all: $(NAME)
	
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

MLX42/build/libmlx42.a:
	@cmake -S MLX42 -B MLX42/build -DMLX42_BUILD_EXAMPLES=OFF
	@cmake --build MLX42/build --parallel

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT) MLX42/build/libmlx42.a
	@echo "$(CYAN)🔨 Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) MLX42/build/libmlx42.a -o $(NAME)
	@echo "$(GREEN)✅ Build complete: $(NAME)$(RESET)"

$(OBJ_DIR):
	@echo "$(CYAN)📂 Creating object directories...$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)✅ Object directories created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔹 Compiling $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compiled: $@$(RESET)"

clean:
	@echo "$(RED)🧹 Cleaning libft...$(RESET)"
	@make -C libft clean
	@echo "$(RED)🧹 Cleaning cub3d...$(RESET)"
	@echo "$(RED)🗑️  Deleting object files...$(RESET)"
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(MAGENTA)✅ Object cleanup complete.$(RESET)"

fclean:
	@echo "$(RED)🧹 Cleaning libft...$(RESET)"
	@make -C libft fclean
	@echo "$(RED)🧹 Cleaning cub3d...$(RESET)"
	@echo "$(RED)🚮 Deleting file $(NAME)...$(RESET)"
	@$(RM) -f $(NAME)
	@echo "$(MAGENTA)✅ $(NAME) removed.$(RESET)"
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(MAGENTA)✅ Object directory removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
