/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:10:12 by bswag             #+#    #+#             */
/*   Updated: 2021/02/22 22:33:26 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	formating_map(t_list **head)
{
	int		max_len;
	char	*empty_line;
	t_list	*new_elem;

	new_elem = NULL;
	max_len = find_max_width_len(*head) + 2;
	ft_lstmap_n(*head, ft_lst_proc_line, max_len);
	empty_line = ft_charalloc(max_len + 1, sizeof(char), ' ');
	if (!empty_line || !(new_elem = ft_lstnew(empty_line)))
		ft_error(ER_MEMMORY_LACK);
	ft_lstadd_front(head, new_elem);
	empty_line = ft_charalloc(max_len + 1, sizeof(char), ' ');
	if (!empty_line || !(new_elem = ft_lstnew(empty_line)))
		ft_error(ER_MEMMORY_LACK);
	ft_lstadd_back(head, new_elem);
}

int		process_map_list(t_list **head)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	i = 0;
	lst = *head;
	while (lst && !(((char *)(lst->content))[0]))
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
		i++;
	}
	*head = lst;
	formating_map(head);
	return (i - 2);
}

int		wall_surrounded(int i, int j, char **map)
{
	int	a;
	int	b;

	a = i - 1;
	while (a < (i + 2))
	{
		b = j - 1;
		while (b < (j + 2))
		{
			if (map[a][b] == ' ')
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}

void	validate_map(char **map)
{
	int		i;
	int		j;
	char	flag;

	i = 0;
	flag = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][++j])
		{
			if (!ft_char_in_set(map[i][j], "012WENS "))
				ft_error(ER_NOT_VALID_MAP);
			else if (ft_char_in_set(map[i][j], "02WENS"))
			{
				if (!wall_surrounded(i, j, map))
					ft_error(ER_NOT_VALID_MAP);
				if (ft_char_in_set(map[i][j], "WENS"))
					flag++;
			}
		}
	}
	if (flag != 1)
		ft_error(ER_NOT_VALID_MAP);
}

char	**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*ptr;

	size -= process_map_list(head);
	if (!(map = ft_calloc(size + 1, sizeof(char *))))
		ft_error(ER_MEMMORY_LACK);
	i = -1;
	ptr = *head;
	while (ptr)
	{
		map[++i] = ptr->content;
		ptr = ptr->next;
	}
	ft_free_lst(head);
	validate_map(map);
	return (map);
}
