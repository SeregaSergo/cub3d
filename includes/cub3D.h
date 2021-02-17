/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:22:40 by bswag             #+#    #+#             */
/*   Updated: 2021/02/17 16:57:05 by bswag            ###   ########.fr       */
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
#define ER_NOT_VALID_MAP	7

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

# define KF_W			0b00000001
# define KF_S			0b00000010
# define KF_A			0b00000100
# define KF_D			0b00001000
# define KF_RIGHT		0b00010000
# define KF_LEFT		0b00100000

# define SCALE			64
# define OFFSET			6
# define MAP_SIZE		4
# define VELOCITY		3

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct  	s_xpm {
	t_img			*img;
	int				width;
	int				hight;
}					t_xpm;

typedef struct		s_plr
{
	float			x;
	float			y;
	float			dir;	
}					t_plr;

typedef struct		s_point
{
	float			x;
	float			y;	
}					t_point;

typedef struct		s_hit
{
	float			dst;
	t_xpm			*xpm;
	float			offset;
}					t_hit;

typedef struct  	s_base {
	void			*mlx;
	void			*win;
	
	t_img			*scr;
	t_img			*min_map;
	
	int				hight;
	int				width;
	t_xpm			*NO;
	t_xpm			*SO;
	t_xpm			*WE;
	t_xpm			*EA;
	t_xpm			*S;
	int				col_floor;
	int				col_ceiling;
	char			**map;
	int				map_scale;
	int				map_width;
	int				map_hight;
	
	t_plr			*plr;
	unsigned char	key_flags;
}					t_base;

void	ft_initialize_input(char *file, t_base *base);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		ft_str_content(char *str, char *pattern);
int		ft_char_in_set(char c, char *pattern);
void	free_arr_str(char **list);
void	ft_error(unsigned char er);
int		ft_arrlen(char **str);
void	process_flag(unsigned char flag, char **lst, t_base *base);
char	**make_map(t_list **head, int size);
int		render_next_frame(t_base *base);
int		key_press_hook(int keycode, t_base *base);
int		key_release_hook(int keycode, t_base *base);
void	ft_cast_rays(t_base *base);
void	ft_print_map(t_base *base, char **map);
void	ft_change_pos_plr(t_base *base, unsigned char flags);
int		destroy_win(void);
void	parse_line(char *line, t_base *base, unsigned char *flags);

#endif