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

CC		=	cc
NAME	=	so_long
FLAGS	=	-Wall -Wextra -Werror# -fsanitize=address -g

SRCS	=	src/error_checkers.c \
			src/animations.c \
			src/helpers.c \
			src/init.c\
			src/map_checkers.c \
			src/path_checker.c \
			src/textures.c \
			main.c

LIBS		=	libft gnl

INCLUDES	=	$(LIBS:%=includes/$*/%.a)

MLX_macos	=	-lmlx -framework OpenGL -framework AppKit

all: $(LIBS) $(NAME)
	@:
$(NAME): $(SRCS)
	@$(CC) -I includes $(FLAGS) $(SRCS) $(INCLUDES) $(MLX_macos) -o $(NAME)
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
re: fclean all
.PHONY: all