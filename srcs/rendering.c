/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/19 17:30:53 by bswag            ###   ########.fr       */
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

unsigned int	ft_get_color(t_hit *hit, int y, t_base *base)
{
	if (y < hit->wall_s)
		return (base->col_ceiling);
	else if (y >= hit->wall_e)
		return (base->col_floor);
	else
	{
		int	pix_y;
		
		pix_y = (int)(hit->xpm->hight * (y - hit->wall_s) / (hit->wall_e - hit->wall_s));
		return (my_mlx_pixel_get(hit->xpm->img, hit->pix_x, pix_y));
	}
}

void	print_screen_line(t_base *base, t_list *hit_points, int x)
{
	int				y;
	unsigned int	col;
	t_list			*ptr;

	y = 0;
	while (y < base->hight)
	{
		ptr = hit_points;	
		while ((col = ft_get_color(ptr->content, y, base)) == 0xFF000000)
			ptr = ptr->next;
		my_mlx_pixel_put(base->scr, x, y, col);
		y++;
	}
}

int		find_horizontal_points(t_base *base, t_list **pnts, t_plr *ray)
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
			return (0);
		pnt.x += xo;
		pnt.y += yo; 
	}
	return (0);
}

int		find_vertical_points(t_base *base, t_list **pnts, t_plr *ray)
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
			return (0);
		pnt.x += xo;
		pnt.y += yo; 		
	}
	return (0);
}

void	ft_cast_rays(t_base *base)
{
	t_plr	ray;
	float	end;
	int		i;
	t_list	*hit_points;

	hit_points = NULL;
	ray = *base->plr;
  	end = ray.dir + (M_PI / 6); // край веера лучей
	ray.dir -= (M_PI / 6); // начало веера лучей
	i = 0;
	while (ray.dir <= end)
	{
		find_horizontal_points(base, &hit_points, &ray);
		find_vertical_points(base, &hit_points, &ray);
		print_screen_line(base, hit_points, i);
		ft_lstclear(&hit_points, &free);
		ray.dir += (M_PI / 3) / base->width;
		i++;
	}
}