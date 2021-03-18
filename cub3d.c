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

int		hook_frame(t_all *all)
{
	all->x = 0;

	ft_memset(all->buf, 0, sizeof(all->buf[0][0]) * all->res_y * all->res_x);
	fill(all);
	while (all->x < all->res_x)
	{
		cast_rays(all);
		draw_calc(all);
		tex_calc(all);
		all->sprt.depth_buf[all->x] = all->perp_wall_dist;
		all->x++;
	}
	sprite(all);
	draw(all);

	if (all->save)
	{
		create_bmp(all);
		exit_cube(all);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img, 0, 0);
	//free(all->buf);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all all;

	ft_bzero(&all, sizeof(all));
	all.res_x = 600;
	all.res_y = 540;
	all.plr_x = 5;
    all.plr_y = 7;  //x and y start position
    all.plr_dir_x = -1.0;
    all.plr_dir_y = 0.0; //initial direction vector
    all.plane_x = 0.0;
    all.plane_y = 0.66; //the 2d raycaster version of camera plane

	all.sprt.nbr_sprites = 4;

	/*
	int n = 1;
	if (*(char *)&n == 1)//check endian
		write(1, "lil\n", 4);
	else
		write(1, "big\n", 4);
	 */
	all.sprt.depth_buf = malloc(sizeof(double) * all.res_x);
	parse_map(&all, argv[1]);
	int i = 0;
	int j;
	while (all.map[i])
	{
		j = 0;
		while (all.map[i][j])
		{
			printf("%c", all.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

//	init(&all);
	all.mlx = mlx_init();
//	tex_mem(&all);
	load_texture(&all);
	all.win = mlx_new_window(all.mlx, all.res_x, all.res_y, "yume");

	all.img = mlx_new_image(all.mlx, all.res_x, all.res_y);
	all.addr = (int *)mlx_get_data_addr(all.img, &all.bits_per_pixel,
										 &all.line_len, &all.endian); //why use casting to int?
	//all.save = 1;
	if (argc == 2 || (argc == 3 && all.save))
	{
		hook_frame(&all);
		//write error;
//		return (0); //or exit
	}
	mlx_hook(all.win, 2, 1L, deal_key, &all);
//	mlx_hook(all.win, 3, 1L, deal_key, &all);
	mlx_hook(all.win, 17, 0L, exit_cube, &all);
	mlx_loop_hook(all.mlx, hook_frame, &all);
	mlx_loop(all.mlx);
	return (0);
}
