/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:33 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/23 22:37:45 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		hook_frame(t_all *all)
{
	all->x = 0;
	fill(all);
	while (all->x < all->res_x)
	{
		cast_rays(all);
		wall_draw_calc(all);
		tex_calc(all);
		all->depth_buf[all->x] = all->wall_dist;
		all->x++;
	}
	sprite(all);
	fill_img(all);
	if (all->save)
	{
		create_bmp(all);
		exit_cube(all, 0);
	}
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	move(all, SPEED);
	move_sideways(all, SPEED);
	rotate(all, SPEED);
	return (0);
}

static void 	init_mlx(t_all *all, int argc)
{
	if (!(all->mlx = mlx_init()))
		exit_cube(all, "Mlx init failed\n");
	if (!(all->depth_buf = malloc(sizeof(double) * all->res_x)))
		exit_cube(all, "Memory allocation failed\n");
	load_texture(all);
	all->win = mlx_new_window(all->mlx, all->res_x, all->res_y, "yume");
	all->img.img = mlx_new_image(all->mlx, all->res_x, all->res_y);
	all->img.addr = (int *)mlx_get_data_addr(all->img.img,
				&all->img.bits_per_pixel, &all->img.line_len, &all->img.endian);

	//all->save = 1;
	if (argc == 2 || (argc == 3 && all->save))// ft_strncmp("--save", argv[2], 6) and strlrn
		hook_frame(all);
	else
		exit_cube(all, "Invalid arguments\n");
	mlx_hook(all->win, 2, 1L, key_press, all);
	mlx_hook(all->win, 3, 1L, key_release, all);
	mlx_hook(all->win, 17, 0L, exit_cube, all);
	mlx_loop_hook(all->mlx, hook_frame, all);
	mlx_loop(all->mlx);
}

int		main(int argc, char **argv)
{
	t_all all;

	ft_bzero(&all, sizeof(all));

//  all.plr_dir_x = -1.0;
//  all.plr_dir_y = 0.0; //initial direction vector
//  all.plane_x = 0.0;
//	all.plane_y = 0.66; //the 2d raycaster version of camera plane

	if (argc < 2 || argc > 3)
	{
		write(1, "Error:\n", 7);
		write(1, "Invalid number of arguments\n", 28);
		exit (0);
	}
	parse_file(&all, argv[1]);

	init(&all);

	init_mlx(&all, argc);
	return (0);
}
