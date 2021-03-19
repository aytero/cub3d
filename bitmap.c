/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:22:14 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/18 19:25:33 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		bmp_colors(t_all *all, int img_size, int fd)
{
	int		x;
	int		y;
	int		colors[img_size];
	int	i = 0;

	y = all->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < all->res_x && i <= img_size)
		{
			colors[i++] = get_color(all, x, y);
			x++;
		}
		y--;
	}
	write(fd, colors, img_size);
}

static void		cast(int val, unsigned char *dst)
{
	dst[0] = (unsigned char)val;
	dst[1] = (unsigned char)(val >> 8);
	dst[2] = (unsigned char)(val >> 16);
	dst[3] = (unsigned char)(val >> 24);
}

static void		bmp_header(t_all *all, int img_size, int fd)
{
	unsigned char bmp[54];

	ft_memset(bmp, 0, 54);
	bmp[0] = 'B';
	bmp[1] = 'M';
	cast(img_size + 54, &bmp[2]);//54 - offset
	ft_memset(&bmp[10], (int)54, 1);//pixel data offset
	ft_memset(&bmp[14], (int)40, 1);//header size
	cast(all->res_x, &bmp[18]);//img width
	cast(all->res_y, &bmp[22]);//img height
	ft_memset(&bmp[26], (short)1, 1);//color plane
	ft_memset(&bmp[28], (short)32, 1);//bits per pixel
	ft_memset(&bmp[34], (int)img_size, 1);
	write(fd, bmp, 54);
}

void			create_bmp(t_all *all)
{
	int		fd;
	int		img_size;

	img_size = all->res_x * all->res_y * 4;// 4 - bytes per pixel
	if ((fd = open("screenshot.bmp", O_WRONLY | O_APPEND
										| O_TRUNC | O_CREAT, 0664)) < 0)
		exit_cube(all, "Screenshot failed\n");
	bmp_header(all, img_size, fd);
	bmp_colors(all, img_size, fd);
	close(fd);
}
