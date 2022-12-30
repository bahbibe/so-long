# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 11:47:55 by bahbibe           #+#    #+#              #
#    Updated: 2022/12/25 05:53:15 by bahbibe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

Off=\033[0m
Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

NAME = gnl.a
FLAGS = -Wall -Wextra -Werror
SRCS =	get_next_line.c \
		get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@:
$(NAME): $(OBJS)
	@printf '\n$(Green)Created gnl ✅ $(Off)\n'
%.o: %.c get_next_line.h
	@printf '\r$ $(Yellow)Compiling gnl ⏳ $(Off)'
	@cc $(FLAGS) -c $< -o $@
	@ar -rcs $(NAME) $@
clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
.PHONY:all