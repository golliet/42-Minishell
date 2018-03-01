# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: golliet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 15:26:08 by golliet           #+#    #+#              #
#    Updated: 2018/02/13 15:34:20 by golliet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = minishell

SRC = main.c cd.c tab.c env.c bin.c myterm.c echo.c env2.c misc.c misc2.c display_caps.c read.c

OBJ = $(SRC:.c=.o)

SAN = -g3

FLAG = -Werror -Wextra -Wall -ltermcap

all: $(NAME)

debug : $(OBJ)
	make -C libft/
	gcc -o $(NAME) $(SAN) $(FLAG) $(OBJ) libft/libft.a

$(NAME) : $(OBJ)
	echo "\033[1;31m"Compilation"\033[0m"
	make -C libft/
	gcc -o $(NAME) $(FLAG) $(OBJ) libft/libft.a

clean :
	echo "\033[1;35m"Cleaning"\033[0m"
	rm -f $(OBJ)
	make clean -C libft/

fclean :
	echo "\033[1;35m"Cleaning"\033[0m"
	rm -f $(OBJ)
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all
