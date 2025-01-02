CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

HISTORY_DIR = ./history
HISTORY_LIB = $(HISTORY_DIR)/history.a

INCLUDES = -I$(LIBFT_DIR) -I$(HISTORY_DIR)  # Incluye la nueva carpeta history

SRC_DIR = ./src
# Archivos fuente del proyecto principal
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/executor.c \
       $(SRC_DIR)/builtins.c \
       $(SRC_DIR)/signals.c \
       $(SRC_DIR)/ft_strtok.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = minishell