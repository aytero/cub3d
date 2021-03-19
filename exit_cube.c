/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:24:15 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/03 04:24:16 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		memory_clean(t_all *all)
{

	if (all->map)
		free(all->map);
//	free(all->tex);//gets freed in mlx func
	//free(all);
	//free(all->buf);
	if (all->depth_buf)
		free(all->depth_buf);
	//i = 0;
	//while (i++ < all->sprt.nbr_sprites)
}

int				exit_cube(t_all *all, char *str)
{
	int 	i;

	if (str)
	{
		write(1, "Error:\n", 7);
		write(1, str, ft_strlen(str));
	}
	i = 0;
	while (i < 5)
	{
		if (all->tex[i].img)
			mlx_destroy_image(all->mlx, all->tex[i].img);
		i++;
	}
	if (all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	memory_clean(all);
	exit (0);
}
