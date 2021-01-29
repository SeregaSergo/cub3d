/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/01/29 20:27:08 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "./libft.h"
#include "./get_next_line.h"
#include "./ft_printf.h"
#include <mlx.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <math.h>

#define ER_ARG      2
#define ER_READ     3

typedef struct  s_base {
    void        *mlx;
    void        *win;
    
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    
    int         hight;
    int         width;
    char        *NO;
    char        *SO;
    char        *WE;
    char        *EA;
    char        *sprite;
    int         col_floor;
    int         col_ceiling;
    char        **map;

    int         x_mouse;
    int         y_mouse;
}               t_base;

int     parse_input(char *file, t_base properties);
void	my_mlx_pixel_put(t_base *base, int x, int y, int color)
#endif
