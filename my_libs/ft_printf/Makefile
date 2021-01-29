# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bswag <bswag@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 17:19:13 by bswag             #+#    #+#              #
#    Updated: 2021/01/29 19:58:24 by bswag            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c \
	   ./parser/parse_flags.c \
	   ./parser/parse_width.c \
	   ./parser/parse_precision.c \
	   ./parser/ft_parser.c \
	   ./parser/parse_type.c \
	   ./processor/ft_processor.c \
	   ./processor/process_int.c \
	   ./processor/process_uxx.c \
	   ./processor/process_p.c \
	   ./processor/process_str.c \
	   ./processor/process_char.c
OBJS = $(SRCS:%.c=%.o)
PATHLIB = ../libft/
CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
DEPS = ft_printf.h

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS) $(PATHLIB)libft.a
	cp $(PATHLIB)libft.a ./$(NAME)
	ar -rcs $(NAME) $(OBJS)

$(PATHLIB)libft.a:
	make -C $(PATHLIB)		

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

bonus: all

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
