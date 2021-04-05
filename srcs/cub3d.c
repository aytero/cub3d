/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:33 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/05 19:11:54 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			hook_frame(t_all *all)
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

static int	cross_press(t_all *all)
{
	exit_cube(all, 0);
	return (0);
}

void		init_mlx(t_all *all)
{
	if (!(all->mlx = mlx_init()))
		exit_cube(all, "Mlx init failed\n");
	if (!(all->depth_buf = malloc(sizeof(double) * all->res_x)))
		exit_cube(all, "Memory allocation failed\n");
	load_texture(all);
	if (!(all->win = mlx_new_window(all->mlx, all->res_x,
					all->res_y, "yume")))
		exit_cube(all, "Failed to create window\n");
	all->img.img = mlx_new_image(all->mlx, all->res_x, all->res_y);
	all->img.addr = (int *)mlx_get_data_addr(all->img.img,
				&all->img.bits_per_pixel, &all->img.line_len, &all->img.endian);
	if (all->save)
		hook_frame(all);
	mlx_hook(all->win, 2, 1L, key_press, all);
	mlx_hook(all->win, 3, 1L, key_release, all);
	mlx_hook(all->win, 17, 0L, cross_press, all);
	mlx_loop_hook(all->mlx, hook_frame, all);
	mlx_loop(all->mlx);
}

void		check_args(t_all *all, int argc, char **argv)
{
	int		len;

	if (argc < 2 || argc > 3)
		exit_cube(all, "Invalid number of arguments\n");
	len = ft_strlen(argv[1]);
	if (!((argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u'
			&& argv[1][len - 3] == 'c' && argv[1][len - 4] == '.')))
		exit_cube(all, "Invalid map file extension\n");
	if (argc == 3)
	{
		len = ft_strlen(argv[2]);
		if (ft_strncmp("--save", argv[2], len) || len != 6)
			exit_cube(all, "Invalid second argument\n");
		all->save = 1;
	}
}

int			main(int argc, char **argv)
{
	t_all all;

	ft_bzero(&all, sizeof(all));
	check_args(&all, argc, argv);
	parse_file(&all, argv[1]);
	init_sprites(&all);
	init_buf(&all);
	init_mlx(&all);
	return (0);
}
