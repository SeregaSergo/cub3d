/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:03:14 by bswag             #+#    #+#             */
/*   Updated: 2021/01/30 16:10:08 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

char    **make_map(t_list **head, int size)
{
    char    **map;
    int     i;
    t_list  *ptr;
    
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

unsigned char   what_flag(char *s)
{
    int len;

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
    else
        return (P_ERR);
}

int     process_flag(unsigned char flag, char **lst, t_base *base)
{
    
    return (0);
}

void    free_arr_str(char **list)
{
    
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
    if ((flag = what_flag(list[0])) == P_ERR || *flags & flag)
    {
        free(line);
        free_arr_str(list);
        ft_error(ER_WRONG_PARAM);
    }
    if (process_flag(flag, list[1], base))
        free_arr_str(list);
    *flags | flag;
}

int parse_input(char *file, t_base *base)
{
    int             fd;
    char            *line;
    unsigned char   flags;
    t_list          *head;
    
    if (fd = open(file, O_RDONLY) < 0)
        return (1);
    line = NULL;
    flags = P_EMPTY;
    head = NULL;
    while(get_next_line(fd, &line) == 1)
    {
        if (file != 255)
        {
            parse_line(line, base, &flags);
            free(line);
        }
        else
            ft_lstadd_back(&head, ft_lstnew(line));
    }
    if (file == 255)
    {
        ft_lstadd_back(&head, ft_lstnew(line));
        base->map = make_map(&head, ft_lstsize(head));
    }
    else
        free(line);
}