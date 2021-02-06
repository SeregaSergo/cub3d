/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/06 12:15:56 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char	*dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

float	ft_segmentlen(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

void	print_screen_line(t_base *base, float dest, int x)
{
	int	y;
	int	wall_s;
	int	wall_e;
	int	col;

	y = 0;
	wall_s = base->hight / 2 - SCALE * (base->hight / dest);
	wall_e = base->hight / 2 + SCALE * (base->hight / dest);
	wall_s < 0 ? wall_s = 0 : 0;
	wall_e > base->hight ? wall_e = base->hight : 0;
	while (y < base->hight)
	{
		if (y > wall_s && y < wall_e)
			col = 0x00FF0000;
		else
			col = 0x00000000;
		my_mlx_pixel_put(base->scr, x, y, col);
		y++;
	}
}

void	ft_cast_rays(t_base *base)
{
	t_plr	ray;
	float	start;
	float	end;
	int		i;
	
	ray = *base->plr;
	start = ray.dir - (M_PI / 6); // начало веера лучей
  	end = ray.dir + (M_PI / 6); // край веера лучей
	i = 0;
	while (start <= end)
	{
		ray.x = base->plr->x; // каждый раз возвращаемся в точку начала
		ray.y = base->plr->y;
		while (base->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			if (i % 20 == 0)
				my_mlx_pixel_put(base->min_map, (int)(ray.x / SCALE * base->map_scale), (int)(ray.y / SCALE * base->map_scale), 0x00008080);
		}
		print_screen_line(base, ft_segmentlen(base->plr->x, base->plr->y, ray.x, ray.y) * cos(base->plr->dir - start), i);
		start += (M_PI / 3) / base->width;
		i++;
	}
}