/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/02/02 19:24:18 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "./libft.h"
#include "./get_next_line.h"
#include "./ft_printf.h"
#include "./mlx.h"
#include <sys/errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdio.h>
#include <math.h>

#define ER_ARG              2
#define ER_READ             3
#define ER_WRONG_PARAM      4
#define ER_MEMMORY_LACK     5
#define ER_NOT_ENOUGH_INFO  6

# define P_EMPTY		0b00000000
# define P_R      		0b00000001
# define P_NO     		0b00000010
# define P_SO     		0b00000100
# define P_WE   		0b00001000 
# define P_EA   		0b00010000
# define P_S     		0b00100000
# define P_F       		0b01000000 
# define P_C   	    	0b10000000
# define P_ERR          0b11111110

typedef struct  s_xpm {
	void	*xpm;
	int		width;
	int		hight;
}				t_xpm;

typedef struct  s_base {
	void		*mlx;
	void		*win;
	
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	
	int			hight;
	int			width;
	t_xpm		*NO;
	t_xpm		*SO;
	t_xpm		*WE;
	t_xpm		*EA;
	t_xpm		*S;
	int			col_floor;
	int			col_ceiling;
	char		**map;

	int			x_mouse;
	int			y_mouse;
}				t_base;

void	parse_input(char *file, t_base *base);
void	my_mlx_pixel_put(t_base *base, int x, int y, int color);
int		process_color_FC(unsigned char flag, char *str, t_base *base);
int		process_xpm(unsigned char flag, char *file, t_base *base);
int		process_R(char *wdth, char *hght, t_base *base);
int		ft_str_content(char *str, char *pattern);
int		ft_char_in_set(char c, char *pattern);
void	free_arr_str(char **list);
void	ft_error(unsigned char er);
int		ft_arrlen(char **str);
char	**make_map(t_list **head, int size);

#endif