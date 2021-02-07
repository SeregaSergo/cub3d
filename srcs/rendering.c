/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/07 18:07:55 by bswag            ###   ########.fr       */
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
/*
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

void	ft_cast_rays_1(t_base *base)
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
		printf("True dst %f\n", ft_segmentlen(base->plr->x, base->plr->y, ray.x, ray.y) * cos(base->plr->dir - start));
		//print_screen_line(base, ft_segmentlen(base->plr->x, base->plr->y, ray.x, ray.y) * cos(base->plr->dir - start), i);
		start += (M_PI / 3) / 10;//base->width;
		i++;
	}
}
*/
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
			// col = 0x00000000;
			col = my_mlx_pixel_get(point->xpm->img->img, (int)(point->xpm->width * point->offset), (int)(point->xpm->hight * (y - wall_s) / (wall_e - wall_s)));
		my_mlx_pixel_put(base->scr, x, y, col);
		y++;
	}
}

int		ft_is_in_map_range(float x, float y, t_base *base)
{
	int	i;
	int	j;
	
	i = ((int)y >> OFFSET) + 1;
	j = ((int)x >> OFFSET) + 1;
	if (j > base->map_width || i > base->map_hight || j < 2 || i < 2)
		return (0);
	return (1);
}

int		ft_is_wall(float x, float y, t_base *base)
{
	if (base->map[(int)y >> OFFSET][(int)x >> OFFSET] == '1')
		return (1);
	else
		return (0);
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
	if (ray->dir > M_PI) //looking up
		{
			ry = (int)(ry / SCALE) * SCALE - 0.0001;
			rx = (ray->y - ry) * (-1 / tan(ray->dir)) + ray->x;
			yo = -SCALE;
			xo = -yo * (-1 / tan(ray->dir));
		}
	else if (ray->dir < M_PI) //looking down
		{
			ry = (int)(ry / SCALE) * SCALE + SCALE;
			rx = (ray->y - ry) * (-1 / tan(ray->dir)) + ray->x;
			yo = SCALE;
			xo = -yo * (-1 / tan(ray->dir));
		}
	if (ray->dir == 0 || ray->dir == M_PI)
		return (0);
	// printf("dir = %f\nxo = %f\nyo = %f\n", ray->dir, xo, yo);
	while (ft_is_in_map_range(rx, ry, base))
	{
		// printf("( %f , %f )\n", rx, ry);
		if (ft_is_wall(rx, ry, base))
		{
			pnt->dst = ft_segmentlen(ray->x, ray->y, rx, ry);
			// printf("horiz dst = %f\n", pnt->dst);
			if (yo == -SCALE)
				pnt->offset =  (rx - (int)(rx / SCALE) * SCALE) / SCALE;
			else
				pnt->offset =  1 - (rx - (int)(rx / SCALE) * SCALE) / SCALE;
			return (1);
		}
		rx += xo;
		ry += yo; 
	}
	return (0);
}

int		find_vertical_point(t_base *base, t_hit *pnt, t_plr *ray)
{
	float	xo;
	float	yo;
	float	rx;
	float	ry;
	
	rx = ray->x;
	ry = ray->y;
	if (ray->dir > M_PI_2 && ray->dir < 3 * M_PI_2) //looking left
		{
			rx = (int)(rx / SCALE) * SCALE - 0.0001;
			ry = (ray->x - rx) * (-tan(ray->dir)) + ray->y;
			xo = -SCALE;
			yo = -xo * (-tan(ray->dir));
		}
	else if (ray->dir < M_PI_2 || ray->dir > (3 * M_PI_2)) //looking right
		{
			rx = (int)(rx / SCALE) * SCALE + SCALE;
			ry = ((ray->x - rx) * (-1 * tan(ray->dir)) + ray->y);
			xo = SCALE;
			yo = -xo * (-tan(ray->dir));
		}
	if (ray->dir == M_PI_2 || ray->dir == 3 * M_PI_2)
		return (0);
	// printf("dir = %f\nxo = %f\nyo = %f\n", ray->dir, xo, yo);
	while (ft_is_in_map_range(rx, ry, base))
	{
		//  printf("( %f , %f )\n", rx, ry);
		if (ft_is_wall(rx, ry, base))
		{
			if (pnt->dst > ft_segmentlen(ray->x, ray->y, rx, ry))
			{
				pnt->dst = ft_segmentlen(ray->x, ray->y, rx, ry);
				// printf("vert dst = %f\n", pnt->dst);
				if (xo == -SCALE)
					pnt->offset =  (ry - (int)(ry / SCALE) * SCALE) / SCALE;
				else
					pnt->offset =  1 - (ry - (int)(ry / SCALE) * SCALE) / SCALE;
				return (1);
			}
			return (0);
		}
		rx += xo;
		ry += yo; 		
	}
	return (0);
}

void	find_hit_point(t_hit *hit_point, t_base *base, t_plr *ray)
{
	if (ray->dir < 0)
		ray->dir += 2 * M_PI;
	else if (ray->dir > 2 * M_PI)
		ray->dir -= 2 * M_PI;
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

void	ft_cast_rays_2(t_base *base)
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
		// printf("\n%i\n", i);
		ray.dir = start;
		find_hit_point(&hit_point, base, &ray);
		hit_point.dst *= cos(base->plr->dir - start);
		// printf("HIT_POINT\ndst = %f\noffset = %f\nxpm = %p\n", hit_point.dst, hit_point.offset, hit_point.xpm);
		print_screen_line(base, &hit_point, i);
		start += (M_PI / 3) / base->width;
		i++;
	}
}