/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:46:31 by bswag             #+#    #+#             */
/*   Updated: 2021/02/23 22:34:44 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int		ft_is_in_map_range(t_plr *pnt, t_base *base)
{
	int	i;
	int	j;

	i = (int)pnt->y + 1;
	j = (int)pnt->x + 1;
	if (j > base->map_width || i > base->map_hight || j < 2 || i < 2)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

char	ft_got_color(t_hit *hit, t_base *base, int x, int y)
{
	unsigned int	col;
	int				pix_y;

	pix_y = hit->xpm->hight * (y - hit->wall_s) / \
	(hit->wall_e - hit->wall_s) * hit->xpm->width;
	col = *((int *)hit->xpm->img->addr + pix_y + hit->pix_x);
	if (col == 0xFF000000)
		return (1);
	*((int *)base->scr->addr + y * base->width + x) = col;
	return (0);
}

void	print_screen_line(t_base *base, t_list *hit_points, int x)
{
	int				y;
	t_list			*ptr;
	t_hit			*hit;

	y = 0;
	ptr = hit_points;
	while (y < base->hight)
	{
		hit = ptr->content;
		if (y < hit->wall_s)
			*((int *)base->scr->addr + y * base->width + x) = base->col_ceiling;
		else if (y >= hit->wall_e)
			*((int *)base->scr->addr + y * base->width + x) = base->col_floor;
		else if (ft_got_color(hit, base, x, y))
		{
			ptr = ptr->next;
			continue ;
		}
		y++;
		ptr = hit_points;
	}
}
