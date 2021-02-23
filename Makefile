NAME =	cub3D
NAMEBNS = cub3DBNS
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
		./srcs/make_map2.c \
		./srcs/rendering2.c
SRCSBNS =	./srcs_bns/main.c \
			./srcs_bns/initializer.c \
			./srcs_bns/input_parser.c \
			./srcs_bns/process_flags.c \
			./srcs_bns/make_map.c \
			./srcs_bns/rendering.c \
			./srcs_bns/hooks.c \
			./srcs_bns/map_rendering.c \
			./srcs_bns/player_moving.c \
			./srcs_bns/utility_func.c \
			./srcs_bns/hits.c \
			./srcs_bns/save_bmp.c \
			./srcs_bns/utility_func2.c \
			./srcs_bns/make_map2.c \
			./srcs_bns/rendering2.c
OBJS = $(SRCS:%.c=%.o)
OBJSBNS = $(SRCSBNS:%.c=%.o)
LIB = libcub.a
MLX = libmlx.a
PATHLIB = my_libs/
PATHMLX = mlx/
INC = includes
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIB)
	$(CC) $(CFLAGS) -I$(INC) -L$(PATHMLX) -lmlx -L$(PATHLIB) -lcub $(OBJS) -framework OpenGL \
	-framework AppKit -o $(NAME)

$(MLX):
	$(MAKE) -C $(PATHMLX)

$(LIB):
	$(MAKE) -C $(PATHLIB)

%.o: %.c ./includes/cub3d.h
	$(CC) -c $(CFLAGS) -I$(INC) -o $@ $<

bonus: $(NAMEBNS)

$(NAMEBNS): $(OBJSBNS) $(MLX) $(LIB)
	$(CC) $(CFLAGS) -I$(INC) -L$(PATHMLX) -lmlx -L$(PATHLIB) -lcub $(OBJSBNS) -framework OpenGL \
	-framework AppKit -o $(NAMEBNS)

%.o: %.c ./includes/cub3dbns.h
	$(CC) -c $(CFLAGS) -I$(INC) -o $@ $<

clean:
	/bin/rm -f $(OBJS) $(OBJSBNS)

fclean: clean
	/bin/rm -f $(NAME) $(NAMEBNS)

re: fclean all