NAME =	cub3D
NAME_BNS = cub3D_bonus
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
SRCSBNS =	./srcs_bns/main_bonus.c \
			./srcs_bns/initializer_bonus.c \
			./srcs_bns/input_parser_bonus.c \
			./srcs_bns/process_flags_bonus.c \
			./srcs_bns/make_map_bonus.c \
			./srcs_bns/rendering_bonus.c \
			./srcs_bns/hooks_bonus.c \
			./srcs_bns/map_rendering_bonus.c \
			./srcs_bns/player_moving_bonus.c \
			./srcs_bns/utility_func_bonus.c \
			./srcs_bns/hits_bonus.c \
			./srcs_bns/save_bmp_bonus.c \
			./srcs_bns/utility_func2_bonus.c \
			./srcs_bns/make_map2_bonus.c \
			./srcs_bns/rendering2_bonus.c
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

bonus: $(NAME_BNS)

$(NAME_BNS): $(OBJSBNS) $(MLX) $(LIB)
	$(CC) $(CFLAGS) -I$(INC) -L$(PATHMLX) -lmlx -L$(PATHLIB) -lcub $(OBJSBNS) -framework OpenGL \
	-framework AppKit -o $(NAME_BNS)

%_bonus.o: %_bonus.c ./includes/cub3dbns.h
	$(CC) -c $(CFLAGS) -I$(INC) -o $@ $<

clean:
	/bin/rm -f $(OBJS) $(OBJSBNS)

fclean: clean
	/bin/rm -f $(NAME) $(NAME_BNS)

re: fclean all