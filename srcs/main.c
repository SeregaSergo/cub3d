/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:16:33 by bswag             #+#    #+#             */
/*   Updated: 2021/02/17 15:12:50 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	change_xy_plr(t_base *base, float angle, float k)
{
	t_plr	*p;
	float	dx;
	float	dy;

	p = base->plr;
	dx = p->x + VELOCITY * k * cos(p->dir + angle);
	dy = p->y + VELOCITY * k * sin(p->dir + angle);
	if (base->map[(int)(base->plr->y / SCALE)][(int)(dx / SCALE)] != '1')
		base->plr->x = dx;
	if (base->map[(int)(dy / SCALE)][(int)(base->plr->x / SCALE)] != '1')
		base->plr->y = dy;
}

float		ft_how_many_keys(unsigned char	flags)
{
	float	k;

	k = 0;
	if (flags & KF_W || flags & KF_S)
		k++;
	if (flags & KF_A || flags & KF_D)
		k++;
	if (k == 2)
		return (0.70710);
	else
		return (k);
}

void	ft_change_pos_plr(t_base *base, unsigned char flags)
{
	float	k_vel;
	
	k_vel = ft_how_many_keys(flags);
	if (flags & KF_W)
		change_xy_plr(base, 0, k_vel);
	if (flags & KF_S)
		change_xy_plr(base, -M_PI, k_vel);
	if (flags & KF_A)
		change_xy_plr(base, -M_PI_2, k_vel);
	if (flags & KF_D)
		change_xy_plr(base, M_PI_2, k_vel);
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
		return (0x002F93B2);
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
	
	end_x = x + base->map_scale;
	end_y = y + base->map_scale;
	sc_x = x;
	while (sc_x < end_x)
	{
		sc_y = y;
		while (sc_y < end_y)
		{
			my_mlx_pixel_put(base->min_map, sc_x, sc_y, col);
			sc_y++;
		}
		sc_x++;
	}
}

void	ft_print_line(t_img *min_map, t_point *p1, t_point *p2)
{
	float	dir;
	float	x;
	float	y;
	
	dir = atan2(p2->y - p1->y, p2->x - p1->x);
	x = p1->x;
	y = p1->y;
	if ((dir < M_PI_2 && dir > -M_PI_2) || dir > (M_PI_2 * 3) || dir < (-M_PI_2 * 3))
	{
		while (x < p2->x)
		{
			my_mlx_pixel_put(min_map, x, y, 0x00E28D2C);
			x += cos(dir);
			y += sin(dir);
		}
	}
	else
	{
		while (x > p2->x)
		{
			my_mlx_pixel_put(min_map, x, y, 0x00E28D2C);
			x += cos(dir);
			y += sin(dir);
		}
	}
}

void	ft_print_player(t_base *base)
{
	static t_point	plr;
	static t_point	point1;
	static t_point	point2;
	
	plr.x = base->plr->x / SCALE * base->map_scale;
	plr.y = base->plr->y / SCALE * base->map_scale;
	point1.x = plr.x + base->map_scale * cos(base->plr->dir);
	point1.y = plr.y + base->map_scale * sin(base->plr->dir);
	point2.x = plr.x + base->map_scale * cos(base->plr->dir - M_PI_4 * 3) * 0.7;
	point2.y = plr.y + base->map_scale * sin(base->plr->dir - M_PI_4 * 3) * 0.7;
	ft_print_line(base->min_map, &plr, &point1);
	ft_print_line(base->min_map, &plr, &point2);
	ft_print_line(base->min_map, &point1, &point2);
	point2.x = plr.x + base->map_scale * cos(base->plr->dir + M_PI_4 * 3) * 0.7;
	point2.y = plr.y + base->map_scale * sin(base->plr->dir + M_PI_4 * 3) * 0.7;
	ft_print_line(base->min_map, &plr, &point2);
	ft_print_line(base->min_map, &point1, &point2);
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
			scaled_pixel_put(base, j * base->map_scale, i * base->map_scale, color);
			j++;
		}
		i++;
	}
	ft_print_player(base);
}

void	print_img(t_img *image, char *s)
{
	printf("%s\n", s);
	printf("Img %p\nAddres %p\nBPP = %i\nLL = %i\nendian = %i\n\n", image->img, image->addr, image->bpp, image->line_length, image->endian);
}

void	print_base(t_base *base)
{
	int i = 0;
	
	printf("base.width = %i\nbase_hight = %i\n", base->width, base->hight);
	printf("plr_x = %f\nplr_y = %f\ndir = %f\n", base->plr->x, base->plr->y, base->plr->dir);
	print_img(base->scr, "SCR");
	print_img(base->min_map, "MAP");
	printf("map_scale %i\nmap_widht %i\nmap_hight %i\n", base->map_scale, base->map_width, base->map_hight);
	printf("\nimg LL = %d\nwidth = %i\nhight = %i\n", base->WE->img->line_length, base->WE->width, base->WE->hight);
	while(base->map[i])
	{
		ft_printf("%s\n", base->map[i]);
		i++;
	}
}

int     main(int argc, char **argv)
{
	t_base	base;

	if (argc != 2 || !argv[0])
		ft_error(ER_ARG);
    base.mlx = mlx_init();
	parse_input(argv[1], &base);
   	base.win = mlx_new_window(base.mlx, base.width, base.hight, "Be glad or be dead!");
	base.scr->img = mlx_new_image(base.mlx, base.width, base.hight);
	base.scr->addr = mlx_get_data_addr(base.scr->img, &base.scr->bpp, &base.scr->line_length, &base.scr->endian);
	base.min_map->img = mlx_new_image(base.mlx, base.map_width * base.map_scale, base.map_hight * base.map_scale);
	base.min_map->addr = mlx_get_data_addr(base.min_map->img, &base.min_map->bpp, &base.min_map->line_length, &base.min_map->endian);
	print_base(&base);
	mlx_hook(base.win, 2, 1L<<0, &key_press_hook, &base);
	mlx_hook(base.win, 3, 1L<<1, &key_release_hook, &base);
	mlx_hook(base.win, 17, 1L<<17, &destroy_win, &base);
	mlx_loop_hook(base.mlx, render_next_frame, &base);
	mlx_loop(base.mlx);
	return (0);
}