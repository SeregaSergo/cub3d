/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/18 15:32:53 by bswag            ###   ########.fr       */
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

int		find_horizontal_point(t_base *base, t_hit *pnts, t_plr *ray)
{
	float	xo;
	float	yo;
	t_plr	pnt;
	float	spin;
	
	pnt = *ray;
	pnt.dir = 100; // for horizonal points
	spin = -1 / tan(ray->dir);
	if (sin(ray->dir) < 0) //looking up
		{
			pnt.y = ((int)pnt.y >> OFFSET << OFFSET) - 0.0001;
			pnt.x = (ray->y - pnt.y) * spin + ray->x;
			yo = -SCALE;
			xo = -yo * spin;
		}
	else if (sin(ray->dir) > 0) //looking down
		{
			pnt.y = ((int)pnt.y >> OFFSET << OFFSET) + SCALE;
			pnt.x = (ray->y - pnt.y) * spin + ray->x;
			yo = SCALE;
			xo = -yo * spin;
		}
	else
		return (0);
	while (ft_is_in_map_range(&pnt, base))
	{
		if (ft_is_wall(&pnt, pnts, base, ray))
		/*{
			pnt->dst = ft_distance(ray->x, ray->y, rx, ry);
			if (yo == -SCALE)
				pnt->offset =  (rx - ((int)rx >> OFFSET << OFFSET)) / SCALE;
			else
				pnt->offset =  1 - (rx - ((int)rx >> OFFSET << OFFSET)) / SCALE; */
			return (0);
		pnt.x += xo;
		pnt.y += yo; 
	}
	return (0);
}

int		find_vertical_point(t_base *base, t_list **pnts, t_plr *ray)
{
	float	xo;
	float	yo;
	t_plr	pnt;
	float	spin;
	
	pnt	= *ray;
	spin = -tan(ray->dir);
	if (cos(ray->dir) < 0) //looking left
		{
			pnt.x = ((int)pnt.x >> OFFSET << OFFSET) - 0.0001;
			pnt.y = (ray->x - pnt.x) * spin + ray->y;
			xo = -SCALE;
			yo = -xo * spin;
		}
	else if (cos(ray->dir) > 0) //looking right
		{
			pnt.x= ((int)pnt.x >> OFFSET << OFFSET) + SCALE;
			pnt.y = ((ray->x - pnt.x) * spin + ray->y);
			xo = SCALE;
			yo = -xo * spin;
		}
	else
		return (0);
	while (ft_is_in_map_range(&pnt, base))
	{
		if (ft_is_wall(&pnt, pnts, base, ray))
		/*	if (pnt->dst > ft_distance(ray->x, ray->y, rx, ry))
			{
				pnt->dst = ft_distance(ray->x, ray->y, rx, ry);
				if (xo == -SCALE)
					pnt->offset =  (ry - ((int)ry >> OFFSET << OFFSET)) / SCALE;
				else
					pnt->offset =  1 - (ry - ((int)ry >> OFFSET << OFFSET)) / SCALE;
				return (1); */
			return (0);
		pnt.x += xo;
		pnt.y += yo; 		
	}
	return (0);
}

void	find_hit_point(t_list **hit_points, t_base *base, t_plr *ray)
{
	find_horizontal_points(base, hit_points, ray);
	find_vertical_points(base, hit_points, ray);
	/*	{
			if (cos(ray->dir) < 0)
				hit_point->xpm = base->EA;
			else
				hit_point->xpm = base->WE; 
		}
	else
		{
			if (sin(ray->dir) < 0)
				hit_point->xpm = base->SO;
			else
				hit_point->xpm = base->NO;	
		}*/
}

void	ft_cast_rays(t_base *base)
{
	t_plr	ray;
	float	end;
	int		i;
	t_list	*hit_points;

	ray = *base->plr;
  	end = ray.dir + (M_PI / 6); // край веера лучей
	ray.dir -= (M_PI / 6); // начало веера лучей
	i = 0;
	while (ray.dir <= end)
	{
		hit_points = NULL;
		find_hit_point(&hit_points, base, &ray);
		//hit_point.dst *= cos(base->plr->dir - ray.dir);
		print_screen_line(base, &hit_points, i);
		ft_lstclear(&hit_points, &free);
		ray.dir += (M_PI / 3) / base->width;
		i++;
	}
}