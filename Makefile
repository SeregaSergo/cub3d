NAME =	cub3D
SRCS =	./srcs/main.c \
		./srcs/initializer.c \
		./srcs/input_parser.c \
		./srcs/process_flags.c \
		./srcs/make_map.c \
		./srcs/rendering.c \
		./srcs/hooks.c \
		./srcs/map_rendering.c \
		./srcs/player_moving.c \
		./srcs/utility_func.c \
		./srcs/hits.c \
		./srcs/save_bmp.c \
		./srcs/utility_func2.c \
		./srcs/make_map2.c
OBJS = $(SRCS:%.c=%.o)
LIB = libcub.a
MLX = libmlx.a
PATHLIB = my_libs/
PATHMLX = mlx/
INC = includes
CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIB)
	$(CC) -g $(CFLAGS) -I$(INC) -L$(PATHMLX) -lmlx -L$(PATHLIB) -lcub $(OBJS) -framework OpenGL \
	-framework AppKit -o $(NAME)

$(MLX):
	$(MAKE) -C $(PATHMLX)

$(LIB):
	$(MAKE) -C $(PATHLIB)

%.o: %.c ./includes/cub3D.h
	$(CC) -c $(CFLAGS) -I$(INC) -o $@ $<

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all