/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:14:05 by bswag             #+#    #+#             */
/*   Updated: 2021/02/23 19:42:08 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_proc_horiz_wall(float sin, t_hit *ptr, float x, t_base *base)
{
	if (sin < 0)
	{
		ptr->xpm = base->so;
		ptr->pix_x = (int)(ptr->xpm->width * fmod(x, 1));
	}
	else
	{
		ptr->xpm = base->no;
		ptr->pix_x = (int)(ptr->xpm->width * (1 - fmod(x, 1)));
	}
}

void	ft_proc_vert_wall(float cos, t_hit *ptr, float y, t_base *base)
{
	if (cos < 0)
	{
		ptr->xpm = base->ea;
		ptr->pix_x = (int)(ptr->xpm->width * (1 - fmod(y, 1)));
	}
	else
	{
		ptr->xpm = base->we;
		ptr->pix_x = (int)(ptr->xpm->width * fmod(y, 1));
	}
}

t_hit	*ft_proc_wall(t_plr *pnt, t_base *base, t_plr *ray)
{
	t_hit	*ptr;

	if (!(ptr = (t_hit *)malloc(sizeof(t_hit))))
		ft_error(ER_MEMMORY_LACK);
	ptr->dst = cos(base->plr->dir - ray->dir) * \
	ft_distance(ray->x, ray->y, pnt->x, pnt->y);
	ptr->wall_s = base->hight / 2 - (base->hight / ptr->dst);
	ptr->wall_e = base->hight / 2 + (base->hight / ptr->dst);
	if (pnt->dir == 100)
		ft_proc_horiz_wall(sin(ray->dir), ptr, pnt->x, base);
	else
		ft_proc_vert_wall(cos(ray->dir), ptr, pnt->y, base);
	return (ptr);
}

t_hit	*ft_proc_sprite(t_plr *pnt, t_base *base, t_plr *ray)
{
	t_hit	*ptr;
	t_point	cntr;
	float	dst;
	float	r;

	cntr.x = (int)pnt->x + 0.5;
	cntr.y = (int)pnt->y + 0.5;
	dst = ft_distance(ray->x, ray->y, cntr.x, cntr.y);
	r = dst * tan(atan2(cntr.y - ray->y, cntr.x - ray->x) - ray->dir);
	if (fabs(r) > 0.5)
		return (NULL);
	if (!(ptr = (t_hit *)malloc(sizeof(t_hit))))
		ft_error(ER_MEMMORY_LACK);
	ptr->dst = dst;
	ptr->wall_s = base->hight / 2 - (base->hight / ptr->dst);
	ptr->wall_e = base->hight / 2 + (base->hight / ptr->dst);
	ptr->xpm = base->s;
	ptr->pix_x = ptr->xpm->width * (r + 0.5);
	return (ptr);
}

int		ft_is_wall(t_plr *pnt, t_list **pnts, t_base *base, t_plr *ray)
{
	char	cell;
	t_hit	*ptr;

	cell = base->map[(int)pnt->y][(int)pnt->x];
	if (cell == '1')
	{
		ptr = ft_proc_wall(pnt, base, ray);
		ft_add_sort_lst(ptr, pnts);
		return (1);
	}
	else if (cell == '2')
	{
		if (!(ptr = ft_proc_sprite(pnt, base, ray)))
			return (0);
		ft_add_sort_lst(ptr, pnts);
	}
	return (0);
}
