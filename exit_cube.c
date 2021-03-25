/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:24:15 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/25 02:46:08 by ayto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void		memory_clean(t_all *all)
{
	int		i;

	if (all->depth_buf)
		free(all->depth_buf);

//	i = -1;
//	while (++i < all->res_y)
//	{
//		printf("%d\n", i);
//		free(all->buf[i]);
//	}
	if (all->buf)
		free(all->buf);

	i = -1;
	while (++i < 5)
	{
		if (all->tex_path[i])
			free(all->tex_path[i]);
	}
	i = -1;
	while (++i < all->map_height)
	{
		if (all->map[i])
			free(all->map[i]);
	}
	if (all->map)
		free(all->map);

	if (all->sprt_cords)
		free(all->sprt_cords);
	if (all->tex)
		free(all->tex);
}



int				exit_cube(t_all *all, char *str)
{
	if (str)
	{
		write(1, "Error:\n", 7);
		write(1, str, ft_strlen(str));
	}
	if (all->tex)
	{
		mlx_destroy_image(all->mlx, all->tex[0].img);
		mlx_destroy_image(all->mlx, all->tex[1].img);
		mlx_destroy_image(all->mlx, all->tex[2].img);
		mlx_destroy_image(all->mlx, all->tex[3].img);
		mlx_destroy_image(all->mlx, all->tex[4].img);
	}
	if (all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	if (all->mlx)
		free(all->mlx);
	memory_clean(all);
//	sleep(999);
	exit (0);
}
