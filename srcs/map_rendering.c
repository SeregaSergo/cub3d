/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:19:44 by bswag             #+#    #+#             */
/*   Updated: 2021/02/19 18:56:49 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		what_color(char c)
{
	if (c == '2')
		return (0x00800080);
	if (c == '1')
		return (0x002F93B2);
	if (c == ' ')
		return (0xFF000000);
	if (c == '0')
		return (0x66000000);
	return (0x00FF0000);
}

void	scaled_pixel_put(t_base *base, int x, int y, int col)
{
	int	sc_x;
	int	sc_y;
	int	end_x;
	int	end_y;
	
	end_x = x + base->map_scale;
	end_y = y + base->map_scale;
	sc_x = x;
	while (sc_x < end_x)
	{
		sc_y = y;
		while (sc_y < end_y)
		{
			my_mlx_pixel_put(base->min_map, sc_x, sc_y, col);
			sc_y++;
		}
		sc_x++;
	}
}

void	ft_print_line(t_img *min_map, t_point *p1, t_point *p2)
{
	float	dir;
	float	x;
	float	y;
	
	dir = atan2(p2->y - p1->y, p2->x - p1->x);
	x = p1->x;
	y = p1->y;
	if ((dir < M_PI_2 && dir > -M_PI_2) || dir > (M_PI_2 * 3) || dir < (-M_PI_2 * 3))
	{
		while (x < p2->x)
		{
			my_mlx_pixel_put(min_map, x, y, 0x00E28D2C);
			x += cos(dir);
			y += sin(dir);
		}
	}
	else
	{
		while (x > p2->x)
		{
			my_mlx_pixel_put(min_map, x, y, 0x00E28D2C);
			x += cos(dir);
			y += sin(dir);
		}
	}
}

void	ft_print_player(t_base *base)
{
	static t_point	plr;
	static t_point	point1;
	static t_point	point2;
	
	plr.x = base->plr->x * base->map_scale;
	plr.y = base->plr->y * base->map_scale;
	point1.x = plr.x + base->map_scale * cos(base->plr->dir);
	point1.y = plr.y + base->map_scale * sin(base->plr->dir);
	point2.x = plr.x + base->map_scale * cos(base->plr->dir - M_PI_4 * 3) * 0.7;
	point2.y = plr.y + base->map_scale * sin(base->plr->dir - M_PI_4 * 3) * 0.7;
	ft_print_line(base->min_map, &plr, &point1);
	ft_print_line(base->min_map, &plr, &point2);
	ft_print_line(base->min_map, &point1, &point2);
	point2.x = plr.x + base->map_scale * cos(base->plr->dir + M_PI_4 * 3) * 0.7;
	point2.y = plr.y + base->map_scale * sin(base->plr->dir + M_PI_4 * 3) * 0.7;
	ft_print_line(base->min_map, &plr, &point2);
	ft_print_line(base->min_map, &point1, &point2);
}

void	ft_print_map(t_base *base, char **map)
{
	int	i;
	int	j;
	int	color;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			color = what_color(map[i][j]);
			scaled_pixel_put(base, j * base->map_scale, i * base->map_scale, color);
			j++;
		}
		i++;
	}
	ft_print_player(base);
}