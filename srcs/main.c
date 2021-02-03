/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:16:33 by bswag             #+#    #+#             */
/*   Updated: 2021/02/04 01:11:50 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
    char	*dst;

    dst = base->addr + (y * base->line_length + x * (base->bpp / 8));
    *(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_base *base)
{
	printf("You pressed %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(base->mlx, base->win); 
		exit (0);
	}
	return (0);
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
	
	end_x = (x + 1) * SCALE;
	end_y = (y + 1) * SCALE;
	sc_x = x * SCALE;
	while (sc_x < end_x)
	{
		sc_y = y * SCALE;
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
			scaled_pixel_put(base, j, i, color);
			j++;
		}
		i++;
	}
}

int	render_next_frame(t_base *base)
{
	ft_print_map(base, base->map);
	//ft_print_player(base);
	mlx_put_image_to_window(base->mlx, base->win, base->img, 0, 0);
	return (0);
}
///*
void	print_base(t_base *base)
{
	int i = 0;
	ft_printf("BPP = %i\nEndian = %i\nWidth = %i\nHight = %i\nColor of floor = %i\n", base->bpp, \
	base->endian, base->width, base->hight, base->col_floor);
	printf("plr_x = %f\nplr_y = %f\ndir = %f\n", base->plr_x, base->plr_y, base->dir);
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
//	mlx_key_hook(base.win, key_hook, &base);
	mlx_loop_hook(base.mlx, render_next_frame, &base);
	mlx_loop(base.mlx);
	return (0);
}