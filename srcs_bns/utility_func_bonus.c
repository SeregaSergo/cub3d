/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:52:44 by bswag             #+#    #+#             */
/*   Updated: 2021/02/24 18:19:32 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

float	ft_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
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
		ft_printf("You passed incorrect number of arguments.\n");
	else if (er == ER_READ)
		ft_printf("Can't open the file.\n");
	else if (er == ER_WRONG_PARAM)
		ft_printf("You passed incorrect parameters of map.\n");
	else if (er == ER_MEMMORY_LACK)
		ft_printf("Not enough memmory to allocate.\n");
	else if (er == ER_NOT_ENOUGH_INFO)
		ft_printf("Needed more information about the map.\n");
	else if (er == ER_NOT_VALID_MAP)
		ft_printf("The map is not valid.\n");
	else if (er == ER_SAVE_IMG)
		ft_printf("To get an image put '--save' as a second parameter\n");
	else if (er == ER_MAP_NAME)
		ft_printf("Not valid map name\n");
	exit(1);
}
