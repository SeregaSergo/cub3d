# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/01/26 20:07:54 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = main.c
OBJ = $(SRC:%.c=%.o)
PATHLIB = libft/
INC = includes
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -L. -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(PATHLIB)libft.a:
	make -C libft		

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
