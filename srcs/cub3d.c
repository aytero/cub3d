#include "cub3d.h"
#include "parser.h"

int	hook_frame(t_all *all)
{
	move(all, SPEED);
	move_sideways(all, SPEED);
	rotate(all, SPEED);
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
	return (0);
}

static int	cross_press(t_all *all)
{
	exit_cube(all, 0);
	return (0);
}

void	init_mlx(t_all *all)
{
	all->mlx = mlx_init();
	if (!all->mlx)
		exit_cube(all, "Mlx init failed\n");
	all->depth_buf = malloc(sizeof(double) * all->res_x);
	if (!all->depth_buf)
		exit_cube(all, "Memory allocation failed\n");
	load_texture(all);
	all->win = mlx_new_window(all->mlx, all->res_x, all->res_y, "yume");
	if (!all->win)
		exit_cube(all, "Failed to create window\n");
	all->img.img = mlx_new_image(all->mlx, all->res_x, all->res_y);
	if (!all->img.img)
		exit_cube(all, "Failed to create image\n");
	all->img.addr = (int *)mlx_get_data_addr(all->img.img,
			&all->img.bits_per_pixel, &all->img.line_len, &all->img.endian);
	if (!all->img.addr)
		exit_cube(all, "Failed to create image\n");
	if (all->save)
		hook_frame(all);
	mlx_hook(all->win, 2, 1L, key_press, all);
	mlx_hook(all->win, 3, 1L, key_release, all);
	mlx_hook(all->win, 17, 0L, cross_press, all);
	mlx_loop_hook(all->mlx, hook_frame, all);
	mlx_loop(all->mlx);
}

void	check_args(t_all *all, int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_all	all;

	ft_bzero(&all, sizeof(all));
	check_args(&all, argc, argv);
	parse_file(&all, argv[1]);
	init_sprites(&all);
	init_buf(&all);
	init_mlx(&all);
	return (0);
}
