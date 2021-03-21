#include "cub3d.h"

/*
void 	init(t_all *all)
{
	int		i;

	all.buf = malloc(sizeof(int *) * all.res_y);
	i = 0;
	while (i < all.res_y)
	{
		all.buf[i] = malloc(sizeof(int) * all.res_x);
		i++;
	}
}
*/

void	init_rc(t_all *all)
{
	all->camera_x = 2 * all->x / (double)all->res_x - 1;
	all->ray_dir_x = all->plr_dir_x + all->plane_x * all->camera_x;
	all->ray_dir_y = all->plr_dir_y + all->plane_y * all->camera_x;
	all->map_x = (int)(all->plr_x);
	all->map_y = (int)(all->plr_y);
	all->hit = 0;
	all->wall_dist = 0;
}

void 	tmp_init_sprite(t_all *all, t_sprite *sprt)//
{

	if (!(sprt->order = malloc(sizeof(int) * all->nbr_sprites)))
		exit_cube(all, "Memory allocation failed\n");
	if (!(sprt->dist = malloc(sizeof(double) * all->nbr_sprites)))
		exit_cube(all, "Memory allocation failed\n");
	if (!(all->sprt_cords = malloc(sizeof(t_sprt_cords)
							* all->nbr_sprites)))
		exit_cube(all, "Memory allocation failed\n");

	all->sprt_cords[0].x = 6;
	all->sprt_cords[0].y = 6;
	all->sprt_cords[1].x = 7;
	all->sprt_cords[1].y = 6;
	all->sprt_cords[2].x = 4;
	all->sprt_cords[2].y = 6;
	all->sprt_cords[3].x = 3.5;
	all->sprt_cords[3].y = 6;
}
