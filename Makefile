# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/02/01 22:30:39 by bswag            ###   ########.fr        #
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

$(NAME): $(OBJ) $(PATHLIB)$(LIB) $(PATHMLX)$(MLX)	
	make -C mlx
	$(CC) $(OBJ) -L$(PATHMLX) -lmlx -L$(PATHLIB) -lcub -framework OpenGL \
	-framework AppKit -o $(NAME)

$(PATHMLX)$(MLX):
	make -C $(PATHMLX)
	
$(PATHLIB)$(LIB):
	make -C $(PATHLIB)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -o $@ $<

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
