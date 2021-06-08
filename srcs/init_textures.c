#include "cub3d.h"

void	find_tex_id(t_all *all)
{
	if (all->side == 1 && all->step[Y_SIDE] > 0)
		all->tex_id = 0;
	else if (all->side == 1 && all->step[Y_SIDE] < 0)
		all->tex_id = 1;
	else if (all->side == 0 && all->step[X_SIDE] > 0)
		all->tex_id = 2;
	else
		all->tex_id = 3;
}

void	load_image(t_all *all, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(all->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit_cube(all, "Failed to load texture\n");
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		exit_cube(all, "Failed to load texture\n");
}

void	load_texture(t_all *all)
{
	all->tex = ft_calloc(5, sizeof(t_img));
	if (!all->tex)
		exit_cube(all, "Memory allocation filed\n");
	load_image(all, all->tex, all->tex_path[0]);
	load_image(all, all->tex + 1, all->tex_path[1]);
	load_image(all, all->tex + 2, all->tex_path[2]);
	load_image(all, all->tex + 3, all->tex_path[3]);
	load_image(all, all->tex + 4, all->tex_path[4]);
}
