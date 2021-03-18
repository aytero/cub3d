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

int		exit_cube(t_all *all)
{
	int 	i;

	i = 0;
	while (i < 5)
	{
		if (all->tex[i].img)
			mlx_destroy_image(all->mlx, all->tex[i].img);
		i++;
	}
	if (all->img)
		mlx_destroy_image(all->mlx, all->img);
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	free(all->map);
	free(all->tex);
	//free(all);
	//free(all->buf);
	//free(all->sprt.depth_buf);

	// or func free_everything
	exit (0);
}
