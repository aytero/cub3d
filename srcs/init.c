#include "cub3d.h"

void	init_buf(t_all *all)
{
	int		j;
	int		i;

	all->buf = ft_calloc(sizeof(int *), all->res_y);
	if (!all->buf)
		exit_cube(all, "Memory allocation failed\n");
	i = 0;
	while (i < all->res_y)
	{
		all->buf[i] = malloc(sizeof(int) * all->res_x);
		if (!all->buf[i])
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
	all->coef = (double)(all->res_x) / (double)(all->res_y) *0.75;
}

void	init_rc(t_all *all)
{
	all->camera_x = 2 * all->x / (double)all->res_x - 1;
	all->ray_dir[X_SIDE] = all->plr_dir[X_SIDE] + all->plane[X_SIDE] * all->camera_x;
	all->ray_dir[Y_SIDE] = all->plr_dir[Y_SIDE] + all->plane[Y_SIDE] * all->camera_x;
	all->map_cur[X_SIDE] = (int)(all->plr[X_SIDE]);
	all->map_cur[Y_SIDE] = (int)(all->plr[Y_SIDE]);
	all->hit = 0;
	all->wall_dist = 0;
}

static void	init_sprites_pos(t_all *all)
{
	int		i;
	int		j;
	int		num;

	num = 0;
	i = -1;
	while (++i < all->map_height)
	{
		j = -1;
		while (++j < all->map_width)
		{
			if (all->map[i][j] == '2')
			{
				all->sprt_pos[num].x = i + 0.5;
				all->sprt_pos[num].y = j + 0.5;
				all->map[i][j] = '0';
				num++;
			}
		}
	}
}

void	init_sprites(t_all *all)
{
	int		i;
	int		j;

	i = -1;
	while (++i < all->map_height)
	{
		j = -1;
		while (++j < all->map_width)
		{
			if (all->map[i][j] == '2')
				all->nbr_sprt++;
		}
	}
	all->sprt_pos = ft_calloc(sizeof(t_sprt_pos), all->nbr_sprt);
	if (!all->sprt_pos)
		exit_cube(all, "Memory allocation failed\n");
	init_sprites_pos(all);
}

void	init_sprites_utils(t_all *all, t_sprite *sprt)
{
	int		i;

	i = -1;
	while (++i < all->nbr_sprt)
	{
		sprt->order[i] = i;
		sprt->dist[i] = pow(all->plr[X_SIDE] - all->sprt_pos[i].x, 2)
			+ pow(all->plr[Y_SIDE] - all->sprt_pos[i].y, 2);
	}
}
