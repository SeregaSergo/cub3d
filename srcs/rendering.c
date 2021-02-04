/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/04 23:25:53 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
    char	*dst;

    dst = base->addr + (y * base->line_length + x * (base->bpp / 8));
    *(unsigned int*)dst = color;
}

void	ft_cast_rays(t_base *base)
{
	t_plr	ray;
	float	start;
	float	end;
	
	ray = *base->plr;
	start = ray.dir - (M_PI / 6); // начало веера лучей
  	end = ray.dir + (M_PI / 6); // край веера лучей
	while (start <= end)
	{
		ray.x = base->plr->x + SCALE / 2; // каждый раз возвращаемся в точку начала
		ray.y = base->plr->y + SCALE / 2;
		while (base->map[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
		{
			ray.x += cos(start);
			ray.y += sin(start);
			my_mlx_pixel_put(base, ray.x, ray.y, 0x00008080);
		}
		start += (M_PI / 3) / 50;
	}
}