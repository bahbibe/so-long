# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 23:38:57 by bahbibe           #+#    #+#              #
#    Updated: 2022/12/31 00:17:53 by bahbibe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Off		=\033[0m
Black	=\033[0;30m
Red		=\033[0;31m
Green	=\033[0;32m
Yellow	=\033[0;33m
Blue	=\033[0;34m
Purple	=\033[0;35m
Cyan	=\033[0;36m
White	=\033[0;37m

.DEFAULT_GOAL	:= all

CC		=	cc
NAME	=	so_long
FLAGS	=	-Wall -Wextra -Werror

SRCS	=	src/error_checkers.c \
			src/animations.c \
			src/ghosts.c \
			src/ghost_move.c \
			src/ghost_anim.c \
			src/helpers.c \
			src/init.c\
			src/map_checkers.c \
			src/path_checker.c \
			src/textures.c \
			main.c

LIBS		=	libft gnl

INCLUDES	=	$(LIBS:%=includes/%.a)

ifeq ($(shell uname),Linux)
MLX_DIR		=	minilibx-linux
MLX_LIB		=	$(MLX_DIR)/libmlx.a
MLX_INC		=	-I $(MLX_DIR)
MLX			=	-L$(MLX_DIR) -lmlx -lXext -lX11 -lm
$(MLX_LIB):
	@make -C $(MLX_DIR) > /dev/null
	@printf '\r$ $(Purple) Built MiniLibX ✅ $(Off)\n'
else
MLX			=	-lmlx -framework OpenGL -framework AppKit
endif

UNIT_SRCS	=	tests/test_ghosts.c \
			src/ghosts.c \
			src/ghost_move.c \
			src/error_checkers.c \
			src/map_checkers.c \
			src/path_checker.c \
			src/helpers.c

all: $(LIBS) $(NAME)
	@:
$(NAME): $(SRCS) includes/so_long.h $(MLX_LIB)
	@$(CC) -I includes $(MLX_INC) $(FLAGS) $(SRCS) $(INCLUDES) $(MLX) -o $(NAME)
	@printf '\r$ $(Purple) Created so_long ✅ $(Off)\n'
	
libs: $(LIBS)
$(LIBS):
	@make -C includes/$@
	@cp includes/$@/$@.a includes
clean:
	@make -C includes/libft clean
	@make -C includes/gnl clean
	@printf '\r$ $(Cyan) Cleaning ✅ $(Off)\n'
fclean: clean
	@make -C includes/libft fclean
	@make -C includes/gnl fclean
	@rm -rf $(NAME)
	@rm -rf $(INCLUDES)
	@if [ -n "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean > /dev/null; fi
	@rm -f tests/test_ghosts
re: fclean all

unit: $(LIBS)
	@$(CC) -I includes $(MLX_INC) $(FLAGS) $(UNIT_SRCS) $(INCLUDES) -o tests/test_ghosts
	@tests/test_ghosts

.PHONY: all libs $(LIBS) clean fclean re unit