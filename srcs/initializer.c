/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:42:52 by bswag             #+#    #+#             */
/*   Updated: 2021/02/22 22:33:17 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_param_plr(t_base *base, int i, int j)
{
	t_plr	*ptr;

	if (!(ptr = (t_plr *)malloc(sizeof(t_plr))))
		ft_error(ER_MEMMORY_LACK);
	base->plr = ptr;
	if (base->map[i][j] == 'W')
		base->plr->dir = M_PI;
	else if (base->map[i][j] == 'N')
		base->plr->dir = M_PI + M_PI_2;
	else if (base->map[i][j] == 'E')
		base->plr->dir = 0;
	else if (base->map[i][j] == 'S')
		base->plr->dir = M_PI_2;
	base->plr->dir += 0.0001;
	base->plr->x = j + 0.5;
	base->plr->y = i + 0.5;
}

void	initialize_plr(t_base *base)
{
	int	i;
	int	j;

	i = 0;
	base->key_flags = 0;
	while (base->map[i])
	{
		j = 0;
		while (base->map[i][j])
		{
			if (ft_char_in_set(base->map[i][j], "WENS"))
			{
				put_param_plr(base, i, j);
				base->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	calc_map_scale(t_base *base)
{
	int	map_wdth;
	int	map_hght;

	map_wdth = (int)(base->width / (ft_strlen(base->map[0])) / MAP_SIZE);
	map_hght = (int)((base->hight / ft_arrlen(base->map)) / MAP_SIZE);
	if (map_wdth < map_hght)
		base->map_scale = map_wdth;
	else
		base->map_scale = map_hght;
	base->map_width = ft_strlen(base->map[0]);
	base->map_hight = ft_arrlen(base->map);
}

void	init_struct_images(t_base *base)
{
	if (!(base->scr = (t_img *)malloc(sizeof(t_img))))
		ft_error(ER_MEMMORY_LACK);
	if (!(base->min_map = (t_img *)malloc(sizeof(t_img))))
		ft_error(ER_MEMMORY_LACK);
}

void	ft_initialize_input(char *file, t_base *base)
{
	int				fd;
	char			*line;
	unsigned char	flags;
	t_list			*head;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error(ER_READ);
	line = NULL;
	flags = P_EMPTY;
	head = NULL;
	while (get_next_line(fd, &line) == 1)
	{
		if (flags != 255)
			parse_line(line, base, &flags);
		else
			ft_lstadd_back(&head, ft_lstnew(line));
	}
	if (flags != 255)
		ft_error(ER_NOT_ENOUGH_INFO);
	ft_lstadd_back(&head, ft_lstnew(line));
	base->map = make_map(&head, ft_lstsize(head));
	calc_map_scale(base);
	initialize_plr(base);
	init_struct_images(base);
}
