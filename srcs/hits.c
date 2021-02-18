/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:14:05 by bswag             #+#    #+#             */
/*   Updated: 2021/02/18 23:13:06 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

float	ft_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
}

int		ft_is_in_map_range(t_plr *pnt, t_base *base)
{
	int	i;
	int	j;
	
	i = ((int)pnt->y >> OFFSET) + 1;
	j = ((int)pnt->x >> OFFSET) + 1;
	if (j > base->map_width || i > base->map_hight || j < 2 || i < 2)
		return (0);
	return (1);
}

t_hit	*ft_proc_wall(t_plr *pnt, t_base *base, t_plr *ray)
{
	t_hit	*ptr;

	if (!(ptr = (t_hit *)malloc(sizeof(t_hit))))
		ft_error(ER_MEMMORY_LACK);
	ptr->dst = cos(base->plr->dir - ray->dir) * ft_distance(ray->x, ray->y, pnt->x, pnt->y);
	ptr->wall_s = base->hight / 2 - SCALE * (base->hight / ptr->dst);
	ptr->wall_e = base->hight / 2 + SCALE * (base->hight / ptr->dst);
	if (pnt->dir == 100) // horizontal point
	{
		if (sin(ray->dir) < 0)// looking up
		{
			ptr->xpm = base->SO;
			ptr->pix_x = (int)(ptr->xpm->width * fmod(pnt->x, SCALE) / SCALE);
		}
		else// looking down
		{
			ptr->xpm = base->NO;
			ptr->pix_x = (int)(ptr->xpm->width * (1 - fmod(pnt->x, SCALE) / SCALE));
		}
	}
	else
	{
		if (cos(ray->dir) < 0) //looking left
		{
			ptr->xpm = base->EA;
			ptr->pix_x = (int)(ptr->xpm->width * fmod(pnt->y, SCALE) / SCALE);
		}
		else// looking down
		{
			ptr->xpm = base->WE;
			ptr->pix_x = (int)(ptr->xpm->width * (1 - fmod(pnt->y, SCALE) / SCALE));
		}
	}
	return (ptr);
}

t_hit	*ft_proc_sprite(t_plr *pnt, t_base *base, t_plr *ray)
{
	t_hit	*ptr;
	t_point	cntr;
	float	dst;
	float	r;

	cntr.x = ((int)pnt->x >> OFFSET << OFFSET) + SCALE / 2;
	cntr.y = ((int)pnt->y >> OFFSET << OFFSET) + SCALE / 2;
	dst = ft_distance(ray->x, ray->y, cntr.x, cntr.y);
	r = dst * tan(atan2(cntr.y - ray->y, cntr.x - ray->x) - ray->dir);
	if (fabs(r) > (SCALE / 2))
		return (NULL);
	if (!(ptr = (t_hit *)malloc(sizeof(t_hit))))
		ft_error(ER_MEMMORY_LACK);
	ptr->dst = dst;
	ptr->wall_s = base->hight / 2 - SCALE *(base->hight / ptr->dst);
	ptr->wall_e = base->hight / 2 + SCALE *(base->hight / ptr->dst);
	ptr->xpm = base->S;
	ptr->pix_x = ptr->xpm->width * (r / SCALE + 0.5);
	return (ptr);
}

int		ft_add_sort_lst(t_hit *cont, t_list **head)
{
	t_list	**addr_prev;
	t_list	*ptr;
	
	addr_prev = head;
	ptr = *head;
	while (ptr)
	{
		if (((t_hit *)ptr->content)->dst > cont->dst)
		{
			if (!(*addr_prev = ft_lstnew(cont)))
				ft_error(ER_MEMMORY_LACK);
			(*addr_prev)->next = ptr;
			return (0);
		}
		addr_prev = &ptr->next;
		ptr = ptr->next;
	}
	if (!(*addr_prev = ft_lstnew(cont)))
		ft_error(ER_MEMMORY_LACK);
	return (0);
}

int		ft_is_wall(t_plr *pnt, t_list **pnts, t_base *base, t_plr *ray)
{
	char	cell;
	t_hit	*ptr;

	cell = base->map[(int)pnt->y >> OFFSET][(int)pnt->x >> OFFSET];
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