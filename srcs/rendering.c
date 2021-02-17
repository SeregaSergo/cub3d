/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/17 19:06:52 by bswag            ###   ########.fr       */
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

float	ft_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
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
	while (y < base->hight)
	{
		if (y > wall_e)
			col = base->col_floor;
		else if (y < wall_s)
			col = base->col_ceiling;
		else
			col = my_mlx_pixel_get(point->xpm->img, (int)(point->xpm->width * point->offset), (int)(point->xpm->hight * (y - wall_s) / (wall_e - wall_s)));
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
	float	spin;
	
	rx = ray->x;
	ry = ray->y;
	pnt->dst = 10000 * SCALE;
	spin = -1 / tan(ray->dir);
	if (ray->dir > M_PI) //looking up
		{
			ry = ((int)ry >> OFFSET << OFFSET) - 0.0001;
			rx = (ray->y - ry) * spin + ray->x;
			yo = -SCALE;
			xo = -yo * spin;
		}
	else if (ray->dir < M_PI) //looking down
		{
			ry = ((int)ry >> OFFSET << OFFSET) + SCALE;
			rx = (ray->y - ry) * spin + ray->x;
			yo = SCALE;
			xo = -yo * spin;
		}
	else
		return (0);
	while (ft_is_in_map_range(rx, ry, base))
	{
		if (ft_is_wall(rx, ry, base))
		{
			pnt->dst = ft_distance(ray->x, ray->y, rx, ry);
			if (yo == -SCALE)
				pnt->offset =  (rx - ((int)rx >> OFFSET << OFFSET)) / SCALE;
			else
				pnt->offset =  1 - (rx - ((int)rx >> OFFSET << OFFSET)) / SCALE;
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
	float	spin;
	
	rx = ray->x;
	ry = ray->y;
	spin = -tan(ray->dir);
	if (ray->dir > M_PI_2 && ray->dir < 3 * M_PI_2) //looking left
		{
			rx = ((int)rx >> OFFSET << OFFSET) - 0.0001;
			ry = (ray->x - rx) * spin + ray->y;
			xo = -SCALE;
			yo = -xo * spin;
		}
	else if (ray->dir < M_PI_2 || ray->dir > (3 * M_PI_2)) //looking right
		{
			rx = ((int)rx >> OFFSET << OFFSET) + SCALE;
			ry = ((ray->x - rx) * spin + ray->y);
			xo = SCALE;
			yo = -xo * spin;
		}
	else
		return (0);
	while (ft_is_in_map_range(rx, ry, base))
	{
		if (ft_is_wall(rx, ry, base))
		{
			if (pnt->dst > ft_distance(ray->x, ray->y, rx, ry))
			{
				pnt->dst = ft_distance(ray->x, ray->y, rx, ry);
				if (xo == -SCALE)
					pnt->offset =  (ry - ((int)ry >> OFFSET << OFFSET)) / SCALE;
				else
					pnt->offset =  1 - (ry - ((int)ry >> OFFSET << OFFSET)) / SCALE;
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
			if (ray->dir > M_PI_2 && ray->dir < (M_PI + M_PI_2))
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
		ray.dir = start;
		find_hit_point(&hit_point, base, &ray);
		hit_point.dst *= cos(base->plr->dir - start);
		print_screen_line(base, &hit_point, i);
		start += (M_PI / 3) / base->width;
		i++;
	}
}