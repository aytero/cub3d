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

/*
void 	tex_mem(t_all *all)
{
	int		i = 0;
	int		j;

//	ft_memset(all->buf, 0, sizeof(all->buf[0][0]) * HEIGHT * WIDTH);
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
*/

void	find_tex_id(t_all *all)
{
	if (all->side == 1 && all->step_y > 0)
		all->tex_id = 0;
	else if (all->side == 1 && all->step_y < 0)
		all->tex_id = 1;
	else if (all->side == 0 && all->step_x > 0)
		all->tex_id = 2;
	else//(all->side == 0 && all->step_x < 0)
		all->tex_id = 3;
	//else
	//	all->tex_id = 4;//sprite
}

void	load_image(t_all *all, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(all->mlx, path,
				&tex->img_width, &tex->img_height);
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
				&tex->line_len, &tex->endian);
}

void	load_texture(t_all *all)
{
	all->tex = ft_calloc(5, sizeof(t_tex));//nbr tex
	load_image(all, all->tex, "textures/star.xpm");
	load_image(all, all->tex + 1, "textures/quartz_pillar_top.xpm");
	load_image(all, all->tex + 2, "textures/brain_coral_block.xpm");
	load_image(all, all->tex + 3, "textures/frosted_ice.xpm");
	load_image(all, all->tex + 4, "textures/red_mushroom.xpm");
}
