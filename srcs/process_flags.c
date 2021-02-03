/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 17:46:28 by bswag             #+#    #+#             */
/*   Updated: 2021/02/02 21:32:37 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
    t_xpm   *ptr;
    
    if (!(ptr = (t_xpm *)ft_calloc(1, sizeof(t_xpm))))
        return (1);
    if (!(ptr->xpm = mlx_xpm_file_to_image(base->mlx, file, &ptr->width, &ptr->hight)))
    {
        free(ptr);
        return (1);
    }
    if (flag == P_NO)
        base->NO = ptr;
    else if (flag == P_SO)
        base->SO = ptr;
    else if (flag == P_WE)
        base->WE = ptr;
    else if (flag == P_EA)
        base->EA = ptr;
    else if (flag == P_S)
        base->S = ptr;
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
    result = 0;
    while (i < 3)
    {
        if ((tmp = ft_atoi(list[i])) > 255)
        {
            free_arr_str(list);
            return (1);
        }
        result = (result << 8) + tmp;
        i++;
    }
    if (flag == P_C)
        base->col_ceiling = result;
    else
        base->col_floor = result;
    free_arr_str(list);     
    return (0);
}