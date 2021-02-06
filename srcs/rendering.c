/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/06 22:37:09 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char	*dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

int		my_mlx_pixel_get(t_img *img, int x, int y)
{
    char	*dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    return (*(unsigned int*)dst);
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
		if (y > wall_e)
			col = base->col_floor;
		else if (y < wall_s)
			col = base->col_ceiling;
		else
			col = 0x00FF33FF;
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
		while (base->map[(int)ray.y >> OFFSET][(int)ray.x >> OFFSET] != '1')
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

void	print_screen_line(t_base *base, t_hit *point, int x)
{
	int	y;
	int	wall_s;
	int	wall_e;
	int	col;

	y = 0;
	wall_s = base->hight / 2 - SCALE * (base->hight / point->dst);
	wall_e = base->hight / 2 + SCALE * (base->hight / point->dst);
	wall_s < 0 ? wall_s = 0 : 0;
	wall_e > base->hight ? wall_e = base->hight : 0;
	while (y < base->hight)
	{
		if (y > wall_e)
			col = base->col_floor;
		else if (y < wall_s)
			col = base->col_ceiling;
		else
			col = my_mlx_pixel_get(point->xpm->img->img, (int)(point->xpm->width * point->offset), (int)(point->xpm->hight * (y - wall_s) / (wall_e - wall_s)));
		my_mlx_pixel_put(base->scr, x, y, col);
		y++;
	}
}

int		find_horizontal_point(t_base *base, t_hit *pnt, t_plr *ray)
{
	float	xo;
	float	yo;
	float	rx;
	float	ry;
	
	rx = ray->x;
	ry = ray->y;
	pnt->dst = 10000 * SCALE;
	if (ray->dir > M_PI)
		{
			ry = (int)(ry / SCALE) * SCALE - 0.0001;
			rx = (ray->y - ry) * (-1 / tan(ray->dir) + ray->x);
			yo = -SCALE;
			xo = -yo * (-1 / tan(ray->dir) + ray->x);
		}
	else if (ray->dir < M_PI)
		{
			ry = (int)(ry / SCALE) + SCALE;
			rx = (ray->y - ry) * (-1 / tan(ray->dir) + ray->x);
			yo = SCALE;
			xo = -yo * (-1 / tan(ray->dir) + ray->x);
		}
	else if (ray->dir == 0 || ray->dir == M_PI)
		return (0);
	while (ft_is_in_map_range(rx, ry))
	{
		if (ft_is_wall(rx, ry))
		{
			pnt->dst = ft_segmentlen(ray->x, ray->y, rx, ry);
			pnt->offset =  
			return (1);
		}
		else
		{
			rx += xo;
			ry += yo; 		
		}
	}
	return (0);
}

int		find_vertical_point(t_base *base, t_hit *pnt, t_plr *ray)
{
	
}

void	find_hit_point(t_hit *hit_point, t_base *base, t_plr *ray)
{
	
	find_horizontal_point(base, hit_point, ray);
	if (find_vertical_point(base, hit_point, ray))
		{
			if (ray->dir > M_PI && ray->dir < (M_PI + M_PI_2))
				hit_point->xpm = base->EA;
			else
				hit_point->xpm = base->WE; 
		}
	else
		{
			if (ray->dir > M_PI)
				hit_point->xpm = base->SO;
			else
				hit_point->xpm = base->NO;	
		}
}

void	ft_cast_rays(t_base *base)
{
	t_plr	ray;
	float	start;
	float	end;
	int		i;
	t_hit	hit_point;

	ray = *base->plr;
	start = ray.dir - (M_PI / 6); // начало веера лучей
  	end = ray.dir + (M_PI / 6); // край веера лучей
	i = 0;
	while (start <= end)
	{
		find_hit_point(&hit_point, base, &ray);
		hit_point.dst *= cos(base->plr->dir - start);
		print_screen_line(base, &hit_point, i);
		start += (M_PI / 3) / base->width;
		i++;
	}
}