# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gemini-cli <support@google.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 15:00:00 by gemini-cli        #+#    #+#              #
#    Updated: 2026/02/06 18:23:17 by vnaoussi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fdf

# Directories
LIBFT_DIR   = libft/
MLX_DIR     = minilibx-linux/
INC_DIR     = includes/
SRC_DIR     = srcs/
OBJ_DIR     = obs/

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lbsd

# Sources
SRCS_FILES  = main.c utils.c utils_2.c utils_dots.c utils_colors.c \
			  maths_transformations.c ft_atoi_base.c bresenham.c debug.c \
			  key_press_events.c utils_3.c settings_maps.c
SRCS        = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS        = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Libraries
LIBFT       = $(LIBFT_DIR)libft.a
MLX         = $(MLX_DIR)libmlx.a

# Colors
DEF_COLOR   = \033[0;39m
GRAY        = \033[0;90m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m

all: $(MLX) $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)FdF compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(BLUE)libft compiled!$(DEF_COLOR)"

$(MLX):
	@if [ ! -f $(MLX) ]; then \
		echo "$(MAGENTA)Compiling MiniLibX...$(DEF_COLOR)"; \
		chmod +x $(MLX_DIR)configure; \
		make -C $(MLX_DIR) --no-print-directory > /dev/null 2>&1 || true; \
		echo "$(MAGENTA)MiniLibX compiled!$(DEF_COLOR)"; \
	fi

clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@make clean -C $(MLX_DIR) --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)Object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(CYAN)Executable and libraries cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything!$(DEF_COLOR)"

.PHONY: all clean fclean re
