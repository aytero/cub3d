#include "cub3d.h"

static void 	init_rc(t_all *all, int x)
{
	all->camera_x = 2 * x / (double) all->win_width - 1;
	all->ray_dir_x = all->plr_dir_x + all->plane_x * all->camera_x;
	all->ray_dir_y = all->plr_dir_y + all->plane_y * all->camera_x;
	all->map_x = (int) (all->plr_x);
	all->map_y = (int) (all->plr_y);
	all->hit = 0;
	all->perp_wall_dist = 0;
}

static void 	calc_hit(t_all *all)
{
	while (all->hit != 1)
	{
		if (all->side_dist_x < all->side_dist_y)
		{
			all->side_dist_x += all->delta_dist_x;
			all->map_x += all->step_x;
			all->side = 0;
		}
		else
		{
			all->side_dist_y += all->delta_dist_y;
			all->map_y += all->step_y;
			all->side = 1;
		}
		if (all->map[all->map_x][all->map_y] == '1')
			all->hit = 1;
	}
}

void	cast_rays(t_all *all, int x)
{
	init_rc(all, x);

	all->delta_dist_x = all->ray_dir_y == 0 ? 0 : fabs(1 / all->ray_dir_x);
	all->delta_dist_y = fabs(1 / all->ray_dir_y);

	all->side_dist_x = all->ray_dir_x >= 0 ? (all->map_x + 1.0 - all->plr_x) * all->delta_dist_x
										   : (all->plr_x - all->map_x) * all->delta_dist_x;
	all->step_x = all->ray_dir_x >= 0 ? 1 : -1;
	all->side_dist_y = all->ray_dir_y >= 0 ? (all->map_y + 1.0 - all->plr_y) * all->delta_dist_y
										   : (all->plr_y - all->map_y) * all->delta_dist_y;
	all->step_y = all->ray_dir_y >= 0 ? 1 : -1;
//	if (calc_hit(all) <= 0)
//		return ;
	calc_hit(all);
}

void 	draw_calc(t_all *all, int x)
{
	if (all->side == 0)
		all->perp_wall_dist = ((double)all->map_x - all->plr_x + (1.0 - all->step_x) / 2.0) / all->ray_dir_x;
	else
		all->perp_wall_dist = ((double)all->map_y - all->plr_y + (1.0 - all->step_y) / 2.0) / all->ray_dir_y;
	all->line_height = (int)(all->win_height / all->perp_wall_dist);
	all->draw_start = -all->line_height / 2 + all->win_height / 2;
	if (all->draw_start < 0)
		all->draw_start = 0;
	all->draw_end = all->line_height / 2 + all->win_height / 2;
	if (all->draw_end >= all->win_height || all->draw_end < 0)// added 2nd condition
		all->draw_end = all->win_height - 1;
	(void)x;
/*
	while (all->draw_start < all->draw_end)
	{
		if (all->side == 1)
			pixel_put(all, x, all->draw_start, 0xb0b0b0);
		else
			pixel_put(all, x, all->draw_start, 0x9c9c9c);
		all->draw_start++;
	}
 */
}

// TODO
void 	tex_calculations(t_all *all, int x)
{
	int 	y;

	all->tex_num = all->map[all->map_x][all->map_y] - 1;
	if (all->side == 0)
		all->wall_x = all->plr_y + all->perp_wall_dist * all->ray_dir_y;
	else
		all->wall_x = all->plr_x + all->perp_wall_dist * all->plr_dir_x;
	all->wall_x -= floor(all->wall_x);
	all->tex_x = (int)(all->wall_x * (double)TEX_WIDTH);
	if (all->side == 0 && all->ray_dir_x > 0)
		all->tex_x = TEX_WIDTH - all->tex_x - 1;
	if (all->side == 1 && all->ray_dir_y < 0)
		all->tex_x = TEX_WIDTH - all->tex_x - 1;
	all->step = 1.0 * TEX_HEIGHT / all->line_height;
	all->tex_pos = (all->draw_start - all->win_height / 2 + all->line_height / 2) * all->step;
	y = all->draw_start;
	while (y < all->draw_end)
	{
		all->tex_y = (int)all->tex_pos & (TEX_HEIGHT - 1);
		all->tex_pos += all->step;
	//	all->buf[y][x] = all->texture[all->tex_num][TEX_HEIGHT * all->tex_y + all->tex_x];//rm all->color from struct
		all->color = all->texture[all->tex_eum][TEX_HEIGHT * all->tex_y + all->tex_x]//!!!!!
		all->buf[y][x] = all->color;
		y++;
	}
}

void	draw(t_all *all)
{
	int 	y;
	int 	x;

	y = 0;
	while (y++ < all->win_height)
	{
		x = 0;
		while (x++ < all->win_width)
			all->addr[y * all->win_width + x] = all->buf[y][x];
	}
//	mlx_put_image_to_window(all->mlx, all->win, all->img, 0, 0);
}
