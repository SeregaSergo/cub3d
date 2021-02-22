/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:49:22 by bswag             #+#    #+#             */
/*   Updated: 2021/02/22 20:47:10 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		ft_init_horiz(t_plr *ray, float *xo, float *yo, t_plr *pnt)
{
	float	spin;

	spin = -1 / tan(ray->dir);
	if (sin(ray->dir) < 0)
	{
		pnt->y = (int)pnt->y - 0.00001;
		pnt->x = (ray->y - pnt->y) * spin + ray->x;
		*yo = -1;
		*xo = -(*yo) * spin;
		return (0);
	}
	else if (sin(ray->dir) > 0)
	{
		pnt->y = (int)pnt->y + 1;
		pnt->x = (ray->y - pnt->y) * spin + ray->x;
		*yo = 1;
		*xo = -(*yo) * spin;
		return (0);
	}
	return (1);
}

int		find_horizontal_points(t_base *base, t_list **pnts, t_plr *ray)
{
	float	xo;
	float	yo;
	t_plr	pnt;

	pnt = *ray;
	pnt.dir = 100;
	if (ft_init_horiz(ray, &xo, &yo, &pnt))
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

int		ft_init_vert(t_plr *ray, float *xo, float *yo, t_plr *pnt)
{
	float	spin;

	spin = -tan(ray->dir);
	if (cos(ray->dir) < 0)
	{
		pnt->x = (int)pnt->x - 0.00001;
		pnt->y = (ray->x - pnt->x) * spin + ray->y;
		*xo = -1;
		*yo = -(*xo) * spin;
		return (0);
	}
	else if (cos(ray->dir) > 0)
	{
		pnt->x = (int)pnt->x + 1;
		pnt->y = ((ray->x - pnt->x) * spin + ray->y);
		*xo = 1;
		*yo = -(*xo) * spin;
		return (0);
	}
	return (1);
}

int		find_vertical_points(t_base *base, t_list **pnts, t_plr *ray)
{
	float	xo;
	float	yo;
	t_plr	pnt;

	pnt = *ray;
	if (ft_init_vert(ray, &xo, &yo, &pnt))
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
	end = ray.dir + (M_PI / 6);
	ray.dir -= (M_PI / 6);
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
