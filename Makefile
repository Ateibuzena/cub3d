NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -IMLX42/include -g
LDFLAGS = -LMLX42/build -lmlx42 -lglfw -lm -ldl -pthread

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) MLX42/build/libmlx42.a
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

MLX42/build/libmlx42.a:
	cmake -S MLX42 -B MLX42/build -DMLX42_BUILD_EXAMPLES=OFF
	cmake --build MLX42/build --parallel

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)
