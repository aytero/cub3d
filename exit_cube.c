/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:24:15 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/23 22:29:35 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void		memory_clean(t_all *all)
{
	int		i;

	if (all->depth_buf)
		free(all->depth_buf);

	i = -1;
	while (++i < all->res_y)
		free(all->buf[i]);
	free(all->buf);

	i = -1;
	while (++i < 5)
	{
		if (all->tex_path[i])
			free(all->tex_path[i]);
	}
	i = -1;
	while (++i < all->map_lines)
	{
		if (all->map[i])
			free(all->map[i]);
	}
	free(all->map);
	//i = -1;
	//while (++i < all->nbr_sprt)
	//	free(all->sprt_cords + i);
	//free(all->sprt_cords);
	//i = 0;
	//while (i++ < all->sprt.nbr_sprt)
}



int				exit_cube(t_all *all, char *str)
{
//	int 	i;

	if (str)
	{
		write(1, "Error:\n", 7);
		write(1, str, ft_strlen(str));
	}
//	i = 0;
//	while (i < 5)
//	{
//		if (all->tex[i].img)
//			mlx_destroy_image(all->mlx, all->tex[i].img);
//		i++;
//	}
	if (all->tex[0].img)
		mlx_destroy_image(all->mlx, all->tex[0].img);
	if (all->tex[1].img)
		mlx_destroy_image(all->mlx, all->tex[1].img);
	if (all->tex[2].img)
		mlx_destroy_image(all->mlx, all->tex[2].img);
	if (all->tex[3].img)
		mlx_destroy_image(all->mlx, all->tex[3].img);
	if (all->tex[4].img)
		mlx_destroy_image(all->mlx, all->tex[4].img);
	if (all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	memory_clean(all);
//	sleep(999);
	exit (0);
}
