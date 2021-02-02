/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:10:12 by bswag             #+#    #+#             */
/*   Updated: 2021/02/02 19:10:43 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*ptr;

	if (!(map = ft_calloc(size + 1, sizeof(char *))))
		return (NULL);
	i = -1;
	ptr = *head;
	while (ptr)
	{
		map[++i] = ptr->content;
		ptr = ptr->next;
	}
	return (map);
}