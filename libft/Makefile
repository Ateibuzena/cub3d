NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

AR = ar rcs
RM = rm -f

# 📂 Code and object directories
SRCDIR = src
OBJDIR = obj

# 🔍 Find source files in subdirectories
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADERS = libft.h

# 🎨 Colors
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
MAGENTA  = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m

# 🚀 Main compilation
all: $(NAME)

# 🔨 Create .a archive (libft.a)
$(NAME): $(OBJDIR) $(OBJS)
	@echo "$(CYAN)🔗 Creating $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✅ $(NAME) successfully created.$(RESET)"

# 📂 Create object directory
$(OBJDIR):
	@echo "$(CYAN)📂 Creating object directories...$(RESET)"
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)✅ Object directories created.$(RESET)"

# 🏗 Compile `.c` files into `.o`, keeping subdirectory structure
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔹 Compiling $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compiled: $@$(RESET)"

# 🧹 Clean object files
clean:
	@echo "$(RED)🗑️  Deleting object files...$(RESET)"
	@$(RM) -rf $(OBJDIR)
	@$(RM) $(OBJS)
	@echo "$(MAGENTA)✅ Object cleanup complete.$(RESET)"
	@if [ -f "$(OBJDIR)" ]; then \
		echo "$(RED)🚮 Deleting object directory...$(RESET)"; \
		$(RM) -rf $(OBJDIR); \
		echo "$(MAGENTA)✅ Object directory removed.$(RESET)"; \
	fi

# 🧹 Full cleanup (removes objects and .a file)
fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)🚮 Deleting file $(NAME)...$(RESET)"; \
		$(RM) $(NAME); \
		echo "$(MAGENTA)✅ $(NAME) removed.$(RESET)"; \
	fi

# 🔄 Full recompilation
re: fclean all

.PHONY: all clean fclean re

