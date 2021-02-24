/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 19:16:33 by bswag             #+#    #+#             */
/*   Updated: 2021/02/24 18:23:37 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	base_struct_init(t_base *base)
{
	char	*name;

	name = "Yo dude!";
	base->win = mlx_new_window(base->mlx, base->width, base->hight, name);
	base->scr->img = mlx_new_image(base->mlx, base->width, base->hight);
	base->scr->addr = mlx_get_data_addr(base->scr->img, &base->scr->bpp, \
	&base->scr->line_length, &base->scr->endian);
	base->min_map->img = mlx_new_image(base->mlx, \
	base->map_width * base->map_scale, base->map_hight * base->map_scale);
	base->min_map->addr = mlx_get_data_addr(base->min_map->img, \
	&base->min_map->bpp, &base->min_map->line_length, &base->min_map->endian);
}

void	ft_check_ext(char *map)
{
	int	len;

	len = ft_strlen(map);
	if (len < 4)
		ft_error(ER_MAP_NAME);
	if (ft_strncmp(&(map[len - 4]), ".cub", 5))
		ft_error(ER_MAP_NAME);
}

int		main(int argc, char **argv)
{
	t_base	base;

	if (argc > 3 || argc < 2)
		ft_error(ER_ARG);
	base.mlx = mlx_init();
	ft_check_ext(argv[1]);
	ft_initialize_input(argv[1], &base);
	base_struct_init(&base);
	if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "--save", 7))
			ft_save_image(&base);
		else
			ft_error(ER_SAVE_IMG);
	}
	mlx_hook(base.win, 2, 1L << 0, &key_press_hook, &base);
	mlx_hook(base.win, 3, 1L << 1, &key_release_hook, &base);
	mlx_hook(base.win, 17, 1L << 17, &destroy_win, &base);
	mlx_loop_hook(base.mlx, render_next_frame, &base);
	mlx_loop(base.mlx);
	return (0);
}
