# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 13:20:08 by atoof             #+#    #+#              #
#    Updated: 2023/03/09 11:43:28 by atoof            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = error_print.c child.c free.c main.c helper_functions.c
HEADER = pipex.h
LIBFT = ./libft/libft.a
FLAGS = -Wall -Werror -Wextra

all: $(NAME)
	
$(NAME): $(SRC)
	make -C ./libft
	cc $(FLAGS) $(SRC) -I$(HEADER) $(LIBFT) -o $@

clean:
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)

re: fclean all
