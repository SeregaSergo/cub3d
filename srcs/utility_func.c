/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:52:44 by bswag             #+#    #+#             */
/*   Updated: 2021/02/17 16:56:58 by bswag            ###   ########.fr       */
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
