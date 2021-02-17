/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:16:33 by bswag             #+#    #+#             */
/*   Updated: 2021/02/17 16:40:36 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
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
*/
int     main(int argc, char **argv)
{
	t_base	base;

	if (argc != 2 || !argv[0])
		ft_error(ER_ARG);
    base.mlx = mlx_init();
	ft_initialize_input(argv[1], &base);
   	base.win = mlx_new_window(base.mlx, base.width, base.hight, "Be glad or be dead!");
	base.scr->img = mlx_new_image(base.mlx, base.width, base.hight);
	base.scr->addr = mlx_get_data_addr(base.scr->img, &base.scr->bpp, &base.scr->line_length, &base.scr->endian);
	base.min_map->img = mlx_new_image(base.mlx, base.map_width * base.map_scale, base.map_hight * base.map_scale);
	base.min_map->addr = mlx_get_data_addr(base.min_map->img, &base.min_map->bpp, &base.min_map->line_length, &base.min_map->endian);
	// print_base(&base);
	mlx_hook(base.win, 2, 1L<<0, &key_press_hook, &base);
	mlx_hook(base.win, 3, 1L<<1, &key_release_hook, &base);
	mlx_hook(base.win, 17, 1L<<17, &destroy_win, &base);
	mlx_loop_hook(base.mlx, render_next_frame, &base);
	mlx_loop(base.mlx);
	return (0);
}