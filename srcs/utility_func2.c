/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_func2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:15:52 by bswag             #+#    #+#             */
/*   Updated: 2021/02/22 21:29:21 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Fills n symbols of the string with given char
*/

void	ft_bchar(void *s, int n, char c)
{
	char	*ptr;
	int		i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	ptr[n] = '\0';
}

/*
** Allocates (count) objects of size (size) and fills it with given char
*/

void	*ft_charalloc(size_t count, int size, char c)
{
	void	*ptr;
	int		total_size;

	total_size = count * size;
	if (!(ptr = malloc(total_size)))
		return (NULL);
	ft_bchar(ptr, total_size, c);
	return (ptr);
}

void	ft_free_lst(t_list **lst)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *lst;
	*lst = NULL;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	tmp = NULL;
	ptr = NULL;
}
