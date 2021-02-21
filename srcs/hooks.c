/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 21:50:44 by bswag             #+#    #+#             */
/*   Updated: 2021/02/21 19:21:23 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		key_press_hook(int keycode, t_base *base)
{
	unsigned char	*flg;

	flg = &(base->key_flags);
	if (keycode == 0)
		*flg |= KF_A;
	if (keycode == 1)
		*flg |= KF_S;
	if (keycode == 2)
		*flg |= KF_D;
	if (keycode == 13)
		*flg |= KF_W;
	if (keycode == 123)
		*flg |= KF_LEFT;
	if (keycode == 124)
		*flg |= KF_RIGHT;
	if (keycode == 53)
		exit(0);
	return (0);
}

int		key_release_hook(int keycode, t_base *base)
{
	unsigned char	*flg;

	flg = &(base->key_flags);
	if (keycode == 0)
		*flg &= ~KF_A;
	if (keycode == 1)
		*flg &= ~KF_S;
	if (keycode == 2)
		*flg &= ~KF_D;
	if (keycode == 13)
		*flg &= ~KF_W;
	if (keycode == 123)
		*flg &= ~KF_LEFT;
	if (keycode == 124)
		*flg &= ~KF_RIGHT;
	if (keycode == 53)
		exit(0);
	return (0);
}

int		destroy_win(void)
{
	exit(0);
}

double	what_time_is_it(void)
{
	struct timespec	now;

	clock_gettime(CLOCK_REALTIME, &now);
	return (now.tv_sec + now.tv_nsec * 1e-9);
}

int		render_next_frame(t_base *base)
{
	static double time;

	ft_change_pos_plr(base, base->key_flags);
	ft_print_map(base, base->map);
	ft_cast_rays(base);
	mlx_put_image_to_window(base->mlx, base->win, base->scr->img, 0, 0);
	mlx_put_image_to_window(base->mlx, base->win, base->min_map->img, 0, 0);
	printf("FPS %.0lf\n", 1 / (what_time_is_it() - time));
	time = what_time_is_it();
	return (0);
}
