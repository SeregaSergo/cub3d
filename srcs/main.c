/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:16:33 by bswag             #+#    #+#             */
/*   Updated: 2021/02/02 17:42:40 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
    char	*dst;

    dst = base->addr + (y * base->line_length + x * (base->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	ft_mouse_enter(void)
{
	printf("Hi!\n");
	return (0);
}

/*
int	mouse_tap_hook(int button, int x, int y, t_base *base)
{
	printf("You pressed %i ( %i , %i )\n", button, x, y);
	return (0);
}
*/
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

int	loop_hook(t_base *base)
{
	my_mlx_pixel_put(base, base->x_mouse - 4, base->y_mouse - 4, 0x00FF0000);
	mlx_put_image_to_window(base->mlx, base->win, base->img, 0, 0);
	return (0);
}

void	print_base(t_base *base)
{
	int i = 0;
	ft_printf("BPP = %i\nEndian = %i\nWidth = %i\nHight = %i\nColor of floor = %i\n", base->bits_per_pixel, \
	base->endian, base->width, base->hight, base->col_floor);
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
	print_base(&base);
   /* base.win = mlx_new_window(base.mlx, base.width, base.hight, "Be glad or be dead!");
	base.img = mlx_new_image(base.mlx, base.width, base.hight);
	 
 	base.addr = mlx_get_data_addr(&base.img, &base.bits_per_pixel, \
	 							&base.line_length, &base.endian);

	mlx_put_image_to_window(base.mlx, base.win, base.img, 0, 0);
	mlx_key_hook(base.win, key_hook, &base);
	mlx_mouse_hook(base.win, mouse_tap_hook, &base); 
	mlx_mouse_get_pos(base.win, &base.x_mouse, &base.y_mouse);
	mlx_loop_hook(base.mlx, loop_hook, &base);
	mlx_loop(base.mlx);*/
	return (0);
}