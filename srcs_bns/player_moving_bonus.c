/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moving.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:24:41 by bswag             #+#    #+#             */
/*   Updated: 2021/02/23 22:34:28 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void		change_xy_plr(t_base *base, float angle, float k)
{
	t_plr	*p;
	float	dx;
	float	dy;

	p = base->plr;
	dx = p->x + VELOCITY * k * cos(p->dir + angle);
	dy = p->y + VELOCITY * k * sin(p->dir + angle);
	if (base->map[(int)base->plr->y][(int)dx] != '1')
		base->plr->x = dx;
	if (base->map[(int)dy][(int)base->plr->x] != '1')
		base->plr->y = dy;
}

static float	ft_how_many_keys(unsigned char flags)
{
	float	k;

	k = 0;
	if (flags & KF_W || flags & KF_S)
		k++;
	if (flags & KF_A || flags & KF_D)
		k++;
	if (k == 2)
		return (0.70710);
	else
		return (k);
}

void			ft_change_pos_plr(t_base *base, unsigned char flags)
{
	float	k_vel;

	k_vel = ft_how_many_keys(flags);
	if (flags & KF_W)
		change_xy_plr(base, 0, k_vel);
	if (flags & KF_S)
		change_xy_plr(base, -M_PI, k_vel);
	if (flags & KF_A)
		change_xy_plr(base, -M_PI_2, k_vel);
	if (flags & KF_D)
		change_xy_plr(base, M_PI_2, k_vel);
	if (flags & KF_LEFT)
		base->plr->dir -= 0.3 * VELOCITY;
	if (flags & KF_RIGHT)
		base->plr->dir += 0.3 * VELOCITY;
	base->plr->dir > 2 * M_PI ? base->plr->dir -= 2 * M_PI : 0;
	base->plr->dir < 0 ? base->plr->dir += 2 * M_PI : 0;
}
