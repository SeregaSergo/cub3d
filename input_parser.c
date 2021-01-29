/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 18:03:14 by bswag             #+#    #+#             */
/*   Updated: 2021/01/29 13:34:07 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

unsigned char   parse_line(char *line, t_base base)
{
    
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
            if (ft_isalpha(line[0]))
                flags = flags | parse_line(line, base);
            free(line);
        }
        else
            ft_lstadd_back(&head, ft_lstnew(line));
    }
    if (file == 255)
        ft_lstadd_back(&head, ft_lstnew(line));
    else
        free(line);
    make_map(&head, ft_lstsize(head))
}