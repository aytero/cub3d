/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:33 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/25 20:26:41 by ayto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		hook_frame(t_all *all)
{
	all->x = 0;
	fill_solid(all);
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

void	init_mlx(t_all *all)
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
	if (all->save)
		hook_frame(all);
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
	check_args(&all, argc, argv);
	parse_file(&all, argv[1]);
	init(&all);
	init_mlx(&all);
	return (0);
}
