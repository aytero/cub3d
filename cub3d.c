/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:33 by lpeggy            #+#    #+#             */
/*   Updated: 2021/02/12 18:11:40 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		hook_frame(t_all *all)
{
	all->x = 0;

	all->img = mlx_new_image(all->mlx, all->win_width, all->win_height);
	all->addr = (int *)mlx_get_data_addr(all->img, &all->bits_per_pixel,
			&all->line_len, &all->endian); //why use casting to int?

	fill(all);
	ft_memset(all->buf, 0, sizeof(all->buf[0][0]) * all->win_height * all->win_width);
	while (all->x < all->win_width)
	{
		cast_rays(all);
		draw_calc(all);
		tex_calc(all);
		all->x++;
	}
	draw(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img, 0, 0);
//	mlx_destroy_image(all->mlx, all->img);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all all;

	(void)argc;//
	ft_bzero(&all, sizeof(all));
	all.win_width = 600;
	all.win_height = 540;
	all.plr_x = 5;
    all.plr_y = 7;  //x and y start position
    all.plr_dir_x = -1.0;
    all.plr_dir_y = 0.0; //initial direction vector
    all.plane_x = 0.0;
    all.plane_y = 0.66; //the 2d raycaster version of camera plane
//	if (argc != 2)
//	{
		//write error;
//		return (0); //or exit
//	}
	//check argv;
	parse_map(&all, argv[1]);
	all.mlx = mlx_init();
//	tex_mem(&all);
	load_texture(&all);
	all.win = mlx_new_window(all.mlx, all.win_width, all.win_height, "yume");

	mlx_hook(all.win, 2, 1L, deal_key, &all);
	mlx_hook(all.win, 17, 0L, exit_cube, &all);
	mlx_loop_hook(all.mlx, hook_frame, &all);
	mlx_loop(all.mlx);
	return (0);
}
