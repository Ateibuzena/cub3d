NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -IMLX42/include -I$(LIBFT_DIR) -g
LDFLAGS = -LMLX42/build -lmlx42 -lglfw -lm -ldl -pthread

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRCS := $(shell find $(LIBFT_DIR) -name '*.c' -o -name '*.h')

SRC_DIR = src
OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus

SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
BONUS_OBJS = $(BONUS_SRCS:$(SRC_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# 🎨 Colors
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
MAGENTA  = \033[0;35m
PINK = \033[38;2;255;105;180m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT) MLX42/build/libmlx42.a
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) MLX42/build/libmlx42.a -o $(NAME)
	@echo "$(YELLOW)✅ Build complete: $(NAME)$(RESET)"

$(BONUS_NAME): $(BONUS_OBJ_DIR) $(BONUS_OBJS) $(LIBFT) MLX42/build/libmlx42.a
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) $(LIBFT) MLX42/build/libmlx42.a -o $(BONUS_NAME)
	@echo "$(YELLOW)✨ Bonus build complete: $(BONUS_NAME)$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)✅ Object directories created.$(RESET)"

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)📁 Bonus object directories created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(CYAN)🔹 Compiling$(MAGENTA) $<$(CYAN) ->$(PINK) $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BONUS_OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(CYAN)🔸 Compiling BONUS$(MAGENTA) $<$(CYAN) ->$(PINK) $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	
$(LIBFT): $(LIBFT_SRCS)
	@$(MAKE) -C $(LIBFT_DIR)

MLX42/build/libmlx42.a:
	@cmake -S MLX42 -B MLX42/build -DMLX42_BUILD_EXAMPLES=OFF
	@cmake --build MLX42/build --parallel

clean:
	@echo "$(GREEN)🧹 Cleaning libft...$(RESET)"
	@make -C libft clean
	@echo "$(GREEN)🧹 Cleaning cub3d...$(RESET)"
	@echo "$(GREEN)🗑️  Deleting object files...$(RESET)"
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -rf $(BONUS_OBJ_DIR)
	@echo "$(GREEN)🧹 Cleaning MLX42 object files...$(RESET)"
	@cmake --build MLX42/build --target clean
	@echo "$(YELLOW)✅ Object cleanup complete.$(RESET)"

fclean:
	@echo "$(GREEN)🧹 Cleaning libft...$(RESET)"
	@make -C libft fclean
	@echo "$(GREEN)🧹 Cleaning cub3d...$(RESET)"
	@echo "$(GREEN)🚮 Deleting file $(NAME)...$(RESET)"
	@$(RM) -f $(NAME)
	@$(RM) -f $(BONUS_NAME)
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -rf $(BONUS_OBJ_DIR)
	@echo "$(GREEN)🧹 Deleting MLX42 build directory...$(RESET)"
	@$(RM) -rf MLX42/build
	@echo "$(YELLOW)✅ Full cleanup complete.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
