/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:10:12 by bswag             #+#    #+#             */
/*   Updated: 2021/02/03 18:44:03 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	ft_free_map(char **map)
{
	int i;
	
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
}

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
/*
void	print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("%s\n", lst->content);
		lst = lst->next;
	}
	ft_printf("\n\n");
}
*/

void	formating_map(t_list **head)
{
	int		max_len;
	char	*empty_line;
	t_list	*new_elem;

	new_elem = NULL;
	max_len = find_max_width_len(*head) + 2;
	ft_lstmap_n(*head, ft_lst_proc_line, max_len);
	if (!(empty_line = ft_charalloc(max_len + 1, sizeof(char), ' ')) || !(new_elem = ft_lstnew(empty_line)))
		ft_error(ER_MEMMORY_LACK);
	ft_lstadd_front(head, new_elem);
	if (!(empty_line = ft_charalloc(max_len + 1, sizeof(char), ' ')) || !(new_elem = ft_lstnew(empty_line)))
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
	while (lst && !((char *)(lst->content))[0])
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

int			wall_surrounded(int i, int j, char **map)
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

void		validate_map(char **map)
{
	int		i;
	int		j;
	char	flag;

	i = 1;
	flag = 0;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
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
			j++;
		}
		i++;
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
	validate_map(map);
	return (map);
}