# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/02/01 23:27:08 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	cub3D
SRC =	main.c \
		input_parser.c \
		process_flags.c
OBJ = $(SRC:%.c=%.o)
LIB = libcub.a
MLX = libmlx.a
PATHLIB = my_libs/
PATHMLX = mlx/
INC = includes
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(PATHMLX)	
	make -C $(PATHLIB)
	$(CC) $(OBJ) -L$(PATHMLX) -lmlx -L$(PATHLIB) -lcub -framework OpenGL \
	-framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
