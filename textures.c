/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:22:35 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/03 04:22:39 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
void 	image()
{
}
*/

/*
void 	tex_mem(t_all *all)
{
ft_memset(buf[i], 0, all->win_height);
while ()
	ft_memset(buf[i][j], 0, all->win_width);
}

void 	texture(t_all *all)
{
all->tex1 = mlx_xpm_file_to_image(all->mlx,
		"textures/dark_green.xpm", &all->img_width, &all->img_height);
all->tex1_addr = mlx_get_data_addr(all->tex1, all->bits_per_pixel, all->line_len, all->endian);
}
*/

void 	tex_mem(t_all *all)
{

	int		i;
	int		j;

	i = 0;
	while (i < all->win_height)
	{
		j = 0;
		while (j < all->win_width)
		{
			all->buf[i][j] = 0;
			j++;
		}
		i++;
	}
//	ft_memset(all->buf, 0, sizeof(all->buf[0][0]) * TEX_HEIGHT * TEX_WIDTH);
	//if (!(all->texture = (int **)malloc(sizeof(int *) * 4)))// 4 - num of textures
		//all->error = 1;
	all->texture = (int **)malloc(sizeof(int *) * 4);
	i = 0;
	while (i++ < 4)
	{
		all->texture[i] = (int *)malloc(sizeof(int) * TEX_HEIGHT * TEX_WIDTH);
		//if - error
	}
	i = 0;
	while (i++ < 4)
	{
		j = 0;
		while (j++ < TEX_HEIGHT * TEX_WIDTH)
			all->texture[i][j] = 0;
	}
	//	ft_memset(all->texture, 0, sizeof(all->texture[0][0]) * 4 * TEX_WIDTH * TEX_HEIGHT);
}

void	load_image(t_all *all, int *texture, char *path)
{
	printf("what\n");
	all->img = mlx_xpm_file_to_image(all->mlx, path, &all->img_width, &all->img_height);
	printf("nu\n");
	all->addr = (int *)mlx_get_data_addr(all->img, &all->bits_per_pixel, &all->line_len, &all->endian);
	printf("that\n");
	int y = 0;
	int x;
	while (y < all->img_height)
	{
		x = 0;
		while (x < all->img_width)
		{
			texture[all->img_width * y + x] = all->addr[all->img_width * y + x];//where the texture var goes?
			x++;
		}
		y++;
	}
	mlx_destroy_image(all->mlx, all->tex_img);
}

void	load_texture(t_all *all)
{
	load_image(all, all->texture[0], "textures/beige.xpm");
	load_image(all, all->texture[1], "textures/dark_green.xpm");
	load_image(all, all->texture[2], "textures/light_green.xpm");
	load_image(all, all->texture[3], "textures/brown.xpm");
}
