/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:16:33 by bswag             #+#    #+#             */
/*   Updated: 2021/02/05 16:13:46 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	change_xy_plr(t_base *base, float angle)
{
	t_plr	*p;
	float	dx;
	float	dy;

	p = base->plr;
	dx = p->x + cos(p->dir + angle);
	dy = p->y + sin(p->dir + angle);
	if (base->map[(int)(base->plr->y / SCALE)][(int)(dx / SCALE)] != '1')
		base->plr->x = dx;
	if (base->map[(int)(dy / SCALE)][(int)(base->plr->x / SCALE)] != '1')
		base->plr->y = dy;
}

void	ft_change_pos_plr(t_base *base, unsigned char flags)
{
	if (flags & KF_W)
		change_xy_plr(base, 0);
	if (flags & KF_S)
		change_xy_plr(base, -M_PI);
	if (flags & KF_A)
		change_xy_plr(base, -M_PI_2);
	if (flags & KF_D)
		change_xy_plr(base, M_PI_2);
	if (flags & KF_LEFT)
		base->plr->dir -= 0.1;
	if (flags & KF_RIGHT)
		base->plr->dir += 0.1;
	base->plr->dir > 2 * M_PI ? base->plr->dir -= 2 * M_PI : 0;
	base->plr->dir < 0 ? base->plr->dir += 2 * M_PI : 0;
}


int		what_color(char c)
{
	if (c == '2')
		return (0x00800080);
	if (c == '1')
		return (0x00808080);
	if (c == ' ')
		return (0x00000000);
	if (c == '0')
		return (0x00000000);
	return (0x00FF0000);
}

void	scaled_pixel_put(t_base *base, int x, int y, int col)
{
	int	sc_x;
	int	sc_y;
	int	end_x;
	int	end_y;
	
	end_x = x + SCALE;
	end_y = y + SCALE;
	sc_x = x;
	while (sc_x < end_x)
	{
		sc_y = y;
		while (sc_y < end_y)
		{
			my_mlx_pixel_put(base, sc_x, sc_y, col);
			sc_y++;
		}
		sc_x++;
	}
}

void	ft_print_map(t_base *base, char **map)
{
	int	i;
	int	j;
	int	color;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			color = what_color(map[i][j]);
			scaled_pixel_put(base, j * SCALE, i * SCALE, color);
			j++;
		}
		i++;
	}
}

///*
void	print_base(t_base *base)
{
	int i = 0;
	ft_printf("BPP = %i\nEndian = %i\nWidth = %i\nHight = %i\nColor of floor = %i\n", base->bpp, \
	base->endian, base->width, base->hight, base->col_floor);
	printf("plr_x = %f\nplr_y = %f\ndir = %f\n", base->plr->x, base->plr->y, base->plr->dir);
	printf("Line length %i\n", base->line_length);
	while(base->map[i])
	{
		ft_printf("%s\n", base->map[i]);
		i++;
	}
}
//*/

int     main(int argc, char **argv)
{
	t_base	base;

	if (argc != 2 || !argv[0])
		ft_error(ER_ARG);
    base.mlx = mlx_init();
	base.line_length = 0;
	base.endian = 0;
	base.bpp = 0;
	parse_input(argv[1], &base);
   	base.win = mlx_new_window(base.mlx, base.width, base.hight, "Be glad or be dead!");
	base.img = mlx_new_image(base.mlx, base.width, base.hight);
	base.addr = mlx_get_data_addr(base.img, &base.bpp, &base.line_length, &base.endian);
	print_base(&base);
	mlx_hook(base.win, 2, 1L<<0, &key_press_hook, &base);
	mlx_hook(base.win, 3, 1L<<1, &key_release_hook, &base);
	mlx_hook(base.win, 17, 1L<<17, &destroy_win, &base);
	mlx_loop_hook(base.mlx, render_next_frame, &base);
	mlx_loop(base.mlx);
	return (0);
}