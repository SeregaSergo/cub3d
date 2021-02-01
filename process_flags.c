/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:46:28 by bswag             #+#    #+#             */
/*   Updated: 2021/02/01 21:51:10 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int ft_char_in_set(char c, char *pattern)
{
    int i;

    i = 0;
    while (pattern[i])
    {
        if (c == pattern[i])
            return (1);
        i++;
    }
    return (0);
}

int ft_str_content(char *str, char *pattern)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(ft_char_in_set(str[i], pattern)))
            return (0);
        i++;
    }
    return (1);
}

int process_R(char *wdth, char *hght, t_base *base)
{
    int tmp;
    
    if (!ft_str_content(wdth, "0123456789") || !ft_str_content(hght, "0123456789"))
        return (1);
    mlx_get_screen_size(base->mlx, &base->width, &base->hight);
    tmp = ft_atoi(wdth);
    if (tmp < base->width)
        base->width = tmp;
    tmp = ft_atoi(hght);
    if (tmp < base->hight)
        base->hight = tmp;
    return (0);
}

int process_xpm(unsigned char flag, char *file, t_base *base)
{
    void    *tmp;

    if (!(tmp = mlx_xpm_file_to_image(base->mlx, file, 100, 100)))
        return (1);
    if (flag == P_NO)
        base->NO = tmp;
    else if (flag == P_SO)
        base->SO = tmp;
    else if (flag == P_WE)
        base->WE = tmp;
    else if (flag == P_EA)
        base->EA = tmp;
    else if (flag == P_S)
        base->S = tmp;
    return (0);        
}

int process_color_FC(unsigned char flag, char *str, t_base *base)
{
    char    **list;
    int     tmp;
    int     result;
    int     i;
    
    if (!ft_str_content(str, "0123456789,") || !(list = ft_split(str, ',')) || ft_arrlen(list) != 3)
        return (1);
    i = 0;
    result;
    while (i < 3)
    {
        if ((tmp = ft_atoi(list[0])) > 255)
        {
            free_arr_str(list);
            return (1);
        }
        result = result << 8 + tmp;
        i++;
    }
    if (flag == P_C)
        base->col_ceiling = result;
    else
        base->col_floor = result;
    free_arr_str(list);     
    return (0);
}