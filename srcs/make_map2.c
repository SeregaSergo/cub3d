/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:19:53 by bswag             #+#    #+#             */
/*   Updated: 2021/02/21 20:23:07 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	*ft_lst_proc_line(void *content, int size)
{
	char	*new_cont;
	int		i;
	char	*ptr;

	if (!(new_cont = (char *)ft_charalloc(size + 1, sizeof(char), ' ')))
		ft_error(ER_MEMMORY_LACK);
	i = 0;
	ptr = (char *)content;
	while (ptr[i])
	{
		new_cont[i + 1] = ptr[i];
		i++;
	}
	return (new_cont);
}

void	ft_lstmap_n(t_list *lst, void *(*f)(void *, int), int size)
{
	void	*new_cont;

	while (lst)
	{
		new_cont = f(lst->content, size);
		free(lst->content);
		lst->content = new_cont;
		lst = lst->next;
	}
}

int		find_max_width_len(t_list *lst)
{
	int	max_len;
	int	tmp;

	max_len = 0;
	while (lst)
	{
		tmp = ft_strlen(lst->content);
		if (max_len < tmp)
			max_len = tmp;
		lst = lst->next;
	}
	return (max_len);
}
