/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:44:05 by bswag             #+#    #+#             */
/*   Updated: 2021/02/22 21:28:44 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned char	what_flag(char *s)
{
	if (s == NULL)
		return (P_EMPTY);
	if (ft_strlen(s) > 2 || ft_strlen(s) < 1)
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

void			parse_line(char *line, t_base *base, unsigned char *flags)
{
	unsigned char	flag;
	char			**list;

	flag = 0;
	if (!(list = ft_split(line, ' ')))
		ft_error(ER_MEMMORY_LACK);
	free(line);
	if ((flag = what_flag(list[0])) == P_ERR || *flags & flag)
		ft_error(ER_WRONG_PARAM);
	process_flag(flag, list, base);
	free_arr_str(list);
	*flags = *flags | flag;
}
