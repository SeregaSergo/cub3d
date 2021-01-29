# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/01/29 20:09:04 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libcub.a
SRCS =		get_next_line.c \
			get_next_line_utils.c
PATHSRC =	./GNL
OBJS =	$(SRCS:%.c=%.o)
LIB =		libftprintf.a
PATHLIB = ./ft_printf
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
DEPS = $(PATHSRC)get_next_line.h

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(PATHLIB)$(LIB)
	cp $(PATHLIB)$(LIB) ./$(NAME)
	ar -rcs $(NAME) $(OBJS)

$(PATHLIB)libftprintf.a:
	make -C $(PATHLIB)		

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
