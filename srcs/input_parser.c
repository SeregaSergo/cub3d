/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:03:14 by bswag             #+#    #+#             */
/*   Updated: 2021/02/04 22:00:33 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		ft_arrlen(char **str)
{
	int	cntr;

	cntr = 0;
	while (str[cntr] != NULL)
	{
		cntr++;
	}
	return (cntr);
}

void	ft_error(unsigned char er)
{
	ft_printf("Error\n");
	if (er == ER_ARG)
		ft_printf("You passed incorrect number of arguments.");
	else if (er == ER_READ)
		ft_printf("Can't open the file.");
	else if (er == ER_WRONG_PARAM)
		ft_printf("You passed incorrect parameters of map.");
	else if (er == ER_MEMMORY_LACK)
		ft_printf("Not enough memmory to allocate.");
	else if (er == ER_NOT_ENOUGH_INFO)
		ft_printf("Needed more information about the map.");
	else if (er == ER_NOT_VALID_MAP)
		ft_printf("The map is not valid.");
	exit(1);
}

unsigned char	what_flag(char *s)
{
	int	len;
	
	if (s == NULL)
		return (P_EMPTY);
	len = ft_strlen(s);
	if (len > 2 || len < 1)
		return (P_ERR);
	if (!(ft_strncmp(s, "\n", 1)))
		return (P_EMPTY);
	if (!(ft_strncmp(s, "R", 2)))
		return (P_R);
	if (!(ft_strncmp(s, "NO", 2)))
		return (P_NO);
	if (!(ft_strncmp(s, "SO", 2)))
		return (P_SO);
	if (!(ft_strncmp(s, "WE", 2)))
		return (P_WE);
	if (!(ft_strncmp(s, "EA", 2)))
		return (P_EA);
	if (!(ft_strncmp(s, "S", 2)))
		return (P_S);
	if (!(ft_strncmp(s, "F", 2)))
		return (P_F);
	if (!(ft_strncmp(s, "C", 2)))
		return (P_C);
	return (P_ERR);	
}

void	process_flag(unsigned char flag, char **lst, t_base *base)
{
	int	len;
	int	res;

	res = 0;
	len = ft_arrlen(lst);
	if (flag == P_EMPTY);
	else if (flag == P_R && len == 3)
		res = process_R(lst[1], lst [2], base);
	else if (flag > P_R && flag < P_F && len == 2)
		res = process_xpm(flag, lst[1], base);
	else if ((flag == P_F || flag == P_C) && len == 2)
		res = process_color_FC(flag, lst[1], base);
	else
		ft_error(ER_WRONG_PARAM);
	if (res)
	{
		free_arr_str(lst);
		ft_error(ER_WRONG_PARAM);
	}
}

void	free_arr_str(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

void    parse_line(char *line, t_base *base, unsigned char *flags)
{
	unsigned char   flag;
	char            **list;
	
	flag = 0;
	if (!(list = ft_split(line, ' ')))
	{
		free(line);
		ft_error(ER_MEMMORY_LACK);
	}
	free(line);
	if ((flag = what_flag(list[0])) == P_ERR || *flags & flag)
	{
		free_arr_str(list);
		ft_error(ER_WRONG_PARAM);
	}
	process_flag(flag, list, base);
	free_arr_str(list);
	*flags = *flags | flag;
}

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
	base->plr->x = j * SCALE;
	base->plr->y = i * SCALE;
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

void	parse_input(char *file, t_base *base)
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
	while(get_next_line(fd, &line) == 1)
	{
		if (flags != 255)
			parse_line(line, base, &flags);
		else
			ft_lstadd_back(&head, ft_lstnew(line));
	}
	if (flags != 255)
	{
		free(line);
		ft_error(ER_NOT_ENOUGH_INFO);
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	base->map = make_map(&head, ft_lstsize(head));
	initialize_plr(base);
}