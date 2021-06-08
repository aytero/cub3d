#include "cub3d.h"

static void	memory_clean_array(char **arr, int len)
{
	int		i;

	i = -1;
	if (arr)
	{
		while (++i < len)
		{
			if (arr[i])
				free(arr[i]);
		}
	}
}

static void	memory_clean(t_all *all)
{
	int		i;

	if (all->depth_buf)
		free(all->depth_buf);
	i = -1;
	if (all->buf)
	{
		while (++i < all->res_y)
		{
			if (all->buf[i])
				free(all->buf[i]);
		}
		free(all->buf);
	}
	memory_clean_array(all->tex_path, 5);
	memory_clean_array(all->map, all->map_height);
	if (all->map)
		free(all->map);
	if (all->sprt_pos)
		free(all->sprt_pos);
	if (all->tex)
		free(all->tex);
}

void	exit_cube(t_all *all, char *str)
{
	if (str)
	{
		write(1, "Error:\n", 7);
		write(1, str, ft_strlen(str));
	}
	if (all->tex)
	{
		if (all->tex[0].img && all->tex[0].addr)
			mlx_destroy_image(all->mlx, all->tex[0].img);
		if (all->tex[1].img && all->tex[1].addr)
			mlx_destroy_image(all->mlx, all->tex[1].img);
		if (all->tex[2].img && all->tex[2].addr)
			mlx_destroy_image(all->mlx, all->tex[2].img);
		if (all->tex[3].img && all->tex[3].addr)
			mlx_destroy_image(all->mlx, all->tex[3].img);
		if (all->tex[4].img && all->tex[4].addr)
			mlx_destroy_image(all->mlx, all->tex[4].img);
	}
	if (all->img.img)
		mlx_destroy_image(all->mlx, all->img.img);
	if (all->win)
		mlx_destroy_window(all->mlx, all->win);
	memory_clean(all);
	exit(0);
}
