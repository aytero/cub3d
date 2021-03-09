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
#include <unistd.h>

/*
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

	ft_memset(all->buf, 0, sizeof(all->buf[0][0]) * HEIGHT * WIDTH);
	//if (!(all->texture = (int **)malloc(sizeof(int *) * 4)))// 4 - num of textures
		//all->error = 1;
	all->texture = (int **)malloc(sizeof(int *) * 4);
	i = 0;
	while (i < 4)
	{
		all->texture[i] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
		i++;
		//if - error
	}
	i = 0;
 	while (i < 4)
 	{
 		j = 0;
 		while (j < (TEX_HEIGHT * TEX_WIDTH))
		{
			all->texture[i][j] = 0;
			j++;
		}
 		i++;
 	}
//	ft_memset(all->texture, 0, sizeof(all->texture[0][0]) * TEX_HEIGHT * TEX_WIDTH);
}

void	load_image(t_all *all, int *texture, char *path, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(all->mlx, path, &tex->img_width, &tex->img_height);
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_len, &tex->endian);

	int y = 0;
	int x;
	while (y < tex->img_height)
	{
		x = 0;
		while (x < tex->img_width)
		{
			texture[tex->img_width * y + x] = tex->addr[tex->img_width * y + x];//where the texture var goes? - pointer
			x++;
		}
		y++;
	}
	mlx_destroy_image(all->mlx, tex->img);

}

void	load_texture(t_all *all)
{
	/*
	all->tex = ft_calloc(4, sizeof(t_tex));//tex_num + 4?
	load_image(all, all->tex, "textures/beige.xpm");
	load_image(all, all->tex + 1, "textures/dark_green.xpm");
	load_image(all, all->tex + 2, "textures/light_green.xpm");
	load_image(all, all->tex + 3, "textures/brown.xpm");
	*/
	t_tex	tex;

	load_image(all, all->texture[0], "textures/beige.xpm", &tex);
	load_image(all, all->texture[1], "textures/dark_green.xpm", &tex);
	load_image(all, all->texture[2], "textures/light_green.xpm", &tex);
	load_image(all, all->texture[3], "textures/brown.xpm", &tex);
}
