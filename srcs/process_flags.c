/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:46:28 by bswag             #+#    #+#             */
/*   Updated: 2021/02/22 21:29:02 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		process_r(char *wdth, char *hght, t_base *base)
{
	int		tmp;
	char	*cnt;

	cnt = "0123456789";
	if (!ft_str_content(wdth, cnt) || !ft_str_content(hght, cnt))
		return (1);
	mlx_get_screen_size(base->mlx, &base->width, &base->hight);
	tmp = ft_atoi(wdth);
	if (tmp < base->width)
		base->width = tmp;
	tmp = ft_atoi(hght);
	if (tmp < base->hight)
		base->hight = tmp;
	return (0);
}

int		process_xpm(unsigned char flag, char *file, t_base *base)
{
	t_xpm	*ptr;

	if (!(ptr = (t_xpm *)ft_calloc(1, sizeof(t_xpm))))
		return (1);
	if (!(ptr->img = (t_img *)ft_calloc(1, sizeof(t_img))))
		return (1);
	if (!(ptr->img->img = mlx_xpm_file_to_image(base->mlx, file, \
		&ptr->width, &ptr->hight)))
		return (1);
	ptr->img->addr = mlx_get_data_addr(ptr->img->img, &ptr->img->bpp, \
					&ptr->img->line_length, &ptr->img->endian);
	if (flag == P_NO)
		base->no = ptr;
	else if (flag == P_SO)
		base->so = ptr;
	else if (flag == P_WE)
		base->we = ptr;
	else if (flag == P_EA)
		base->ea = ptr;
	else if (flag == P_S)
		base->s = ptr;
	return (0);
}

int		process_color_fc(unsigned char flag, char *str, t_base *base)
{
	char	**list;
	int		tmp;
	int		result;
	int		i;

	if (!ft_str_content(str, "0123456789,") || !(list = ft_split(str, ',')) \
		|| ft_arrlen(list) != 3)
		return (1);
	i = 0;
	result = 0;
	while (i < 3)
	{
		if ((tmp = ft_atoi(list[i])) > 255)
			return (1);
		result = (result << 8) + tmp;
		i++;
	}
	if (flag == P_C)
		base->col_ceiling = result;
	else
		base->col_floor = result;
	free_arr_str(list);
	return (0);
}

void	process_flag(unsigned char flag, char **lst, t_base *base)
{
	int	len;
	int	res;

	res = 0;
	len = ft_arrlen(lst);
	if (flag == P_EMPTY)
		;
	else if (flag == P_R && len == 3)
		res = process_r(lst[1], lst[2], base);
	else if (flag > P_R && flag < P_F && len == 2)
		res = process_xpm(flag, lst[1], base);
	else if ((flag == P_F || flag == P_C) && len == 2)
		res = process_color_fc(flag, lst[1], base);
	else
		ft_error(ER_WRONG_PARAM);
	if (res)
	{
		free_arr_str(lst);
		ft_error(ER_WRONG_PARAM);
	}
}
