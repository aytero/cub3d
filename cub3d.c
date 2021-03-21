/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:38:33 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/21 20:45:24 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		hook_frame(t_all *all)
{
	all->x = 0;
//	ft_memset(all->buf, 0, sizeof(all->buf[0][0]) * all->res_y * all->res_x);
//	ft_memset(all->buf, 0, sizeof(all->buf[0]) * all->res_y * all->res_x);
	int i = 0;
	int j;
	while (i < all->res_y)
	{
		j = 0;
		while (j < all->res_x)
		{
			all->buf[i][j] = 0;
			j++;
		}
		i++;
	}
//	fill(all);
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
	//free(all->buf);
	return (0);
}

static void 	init_mlx(t_all *all, int argc)
{
	if (!(all->mlx = mlx_init()))
		exit_cube(all, "Mlx init failed\n");
//	tex_mem(&all);
	if (!(all->depth_buf = malloc(sizeof(double) * all->res_x)))
		exit_cube(all, "Memory allocation failed\n");
	load_texture(all);
//	exit_cube(&all, "text\n");
	all->win = mlx_new_window(all->mlx, all->res_x, all->res_y, "yume");
	all->img.img = mlx_new_image(all->mlx, all->res_x, all->res_y);
	all->img.addr = (int *)mlx_get_data_addr(all->img.img,
				&all->img.bits_per_pixel, &all->img.line_len, &all->img.endian);

	//all->save = 1;
	if (argc == 2 || (argc == 3 && all->save))
		hook_frame(all);
	else
		exit_cube(all, "Invalid arguments\n");
	mlx_hook(all->win, 2, 1L, deal_key, all);
	mlx_hook(all->win, 17, 0L, exit_cube, all);
	mlx_loop_hook(all->mlx, hook_frame, all);
	mlx_loop(all->mlx);
}

int		main(int argc, char **argv)
{
	t_all all;

	ft_bzero(&all, sizeof(all));
//	all.res_x = 600;
//	all.res_y = 540;
	all.plr_x = 5;
    all.plr_y = 7;  //x and y start position
    all.plr_dir_x = -1.0;
    all.plr_dir_y = 0.0; //initial direction vector
    all.plane_x = 0.0;
    all.plane_y = 0.66; //the 2d raycaster version of camera plane

	all.nbr_sprites = 4;

	if (argc < 2 || argc > 3)
	{
		write(1, "Error:\n", 7);
		write(1, "Invalid number of arguments\n", 28);
		exit (0);
	}
	parse_file(&all, argv[1]);

	/*
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
*/
	int i;
	if (!(all.buf = malloc(sizeof(int *) * all.res_y)))
		return (-1);
	i = 0;
	while (i < all.res_y)
	{
		if (!(all.buf[i] = malloc(sizeof(int) * all.res_x)))
			return (-1);
		i++;
	}

	if (all.res_y > all.res_x)
		all.coef = (double)(all.res_y) / (double)(all.res_x) * 10.0;
	else
		all.coef = (double)(all.res_x) / (double)(all.res_y) * 10.0;
	printf("coef  %g\n", all.coef);

	init_mlx(&all, argc);
	return (0);
}
