/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bswag <bswag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 18:02:04 by bswag             #+#    #+#             */
/*   Updated: 2021/02/23 20:29:44 by bswag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3dbns.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	ft_write_image(int fd, t_base *base)
{
	int				width;
	int				hight;
	unsigned char	*ptr;
	int				pad;

	hight = base->hight - 1;
	while (hight >= 0)
	{
		width = 0;
		ptr = (unsigned char *)base->scr->addr + base->width * hight * 4;
		while (width < base->width)
		{
			write(fd, ptr, 3);
			ptr += 4;
			width++;
		}
		hight--;
	}
	if ((pad = 4 - (base->width * base->hight * 3) % 4))
		write(fd, 0, pad);
}

void	ft_write_map(int fd, t_base *base, int w, int h)
{
	int		width;
	int		hight;
	char	*ptr;
	int		offset;

	lseek(fd, 54 + (base->hight - h) * base->width * 3, SEEK_SET);
	offset = (base->width - w) * 3;
	hight = h - 1;
	while (hight >= 0)
	{
		width = 0;
		ptr = base->min_map->addr + w * hight * 4;
		while (width < w)
		{
			if (*(unsigned int *)ptr != 0xFF000000)
				write(fd, ptr, 3);
			else
				lseek(fd, 3, SEEK_CUR);
			ptr += 4;
			width++;
		}
		hight--;
		lseek(fd, offset, SEEK_CUR);
	}
}

void	ft_write_header(int fd, int width, int height)
{
	unsigned char		header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, 54 + 3 * width * height);
	set_int_in_char(header + 10, 54);
	set_int_in_char(header + 14, 40);
	set_int_in_char(header + 18, width);
	set_int_in_char(header + 22, height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void	ft_save_image(t_base *base)
{
	int	fd;

	fd = open("./screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	ft_print_map(base, base->map);
	ft_cast_rays(base);
	ft_write_header(fd, base->width, base->hight);
	ft_write_image(fd, base);
	ft_write_map(fd, base, base->map_width * base->map_scale, \
	base->map_hight * base->map_scale);
	close(fd);
	exit(0);
}
