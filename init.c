/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <lpeggy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 15:56:27 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/24 21:17:48 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void 	init(t_all *all)
{
	int	j;
	int i;

	if (!(all->buf = malloc(sizeof(int *) * all->res_y)))
		exit_cube(all, "Memory allocation failed\n");//
	i = 0;
	while (i < all->res_y)
	{
		if (!(all->buf[i] = malloc(sizeof(int) * all->res_x)))
			exit_cube(all, "Memory allocation failed\n");
		i++;
	}
	i = -1;
	while (++i < all->res_y)
	{
		j = -1;
		while (++j < all->res_x)
			all->buf[i][j] = 0;
	}
	all->coef = (double)(all->res_x) / (double)(all->res_y) * 0.75;
	printf("coef  %f\n", all->coef);
}

void	init_rc(t_all *all)
{
	all->camera_x = 2 * all->x / (double)all->res_x - 1;
	all->ray_dir_x = all->plr_dir_x + all->plane_x * all->camera_x;
	all->ray_dir_y = all->plr_dir_y + all->plane_y * all->camera_x;
	all->map_x = (int)(all->plr_x);
	all->map_y = (int)(all->plr_y);
	all->hit = 0;
	all->wall_dist = 0;
}
