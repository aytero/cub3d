#include "cub3d.h"

static int	calc_hit(t_all *all)
{
	while (all->hit != 1)
	{
		if (all->side_dist[X_SIDE] < all->side_dist[Y_SIDE])
		{
			all->side_dist[X_SIDE] += all->delta_dist[X_SIDE];
			all->map_cur[X_SIDE] += all->step[X_SIDE];
			all->side = X_SIDE;
		}
		else
		{
			all->side_dist[Y_SIDE] += all->delta_dist[Y_SIDE];
			all->map_cur[Y_SIDE] += all->step[Y_SIDE];
			all->side = Y_SIDE;
		}
		if (all->map[all->map_cur[X_SIDE]][all->map_cur[Y_SIDE]] == '1')
			all->hit = 1;
	}
	return (all->hit);
}

void	cast_rays(t_all *all)
{
	init_rc(all);

	int i = X_SIDE;
	while (i < 2)
	{
		all->delta_dist[i] = fabs(1 / all->ray_dir[i]);
		if (all->ray_dir[i] >= 0)
		{
			all->side_dist[i] = (all->map_cur[i] + 1.0 - all->plr[i])
								* all->delta_dist[i];
			all->step[i] = 1;
		}
		else
		{
			all->side_dist[i] = (all->plr[i] - all->map_cur[i]) * all->delta_dist[i];
			all->step[i] = -1;
		}
		i++;
	}


//	all->delta_dist[Y_SIDE] = fabs(1 / all->ray_dir[Y_SIDE]);
//	all->delta_dist[X_SIDE] = fabs(1 / all->ray_dir[X_SIDE]);
//	if (all->ray_dir[X_SIDE] >= 0)
//	{
//		all->side_dist[X_SIDE] = (all->map_x + 1.0 - all->plr[X_SIDE]) * all->delta_dist[X_SIDE];
//		all->step[X_SIDE] = 1;
//	}
//	else
//	{
//		all->side_dist[X_SIDE] = (all->plr[X_SIDE] - all->map_x) * all->delta_dist[X_SIDE];
//		all->step[X_SIDE] = -1;
//	}
//	if (all->ray_dir[Y_SIDE] >= 0)
//	{
//		all->side_dist[Y_SIDE] = (all->map_y + 1.0 - all->plr[Y_SIDE]) * all->delta_dist[Y_SIDE];
//		all->step[Y_SIDE] = 1;
//	}
//	else
//	{
//		all->side_dist[Y_SIDE] = (all->plr[Y_SIDE] - all->map_y) * all->delta_dist[Y_SIDE];
//		all->step[Y_SIDE] = -1;
//	}
	if (!calc_hit(all))
		return ;
}

void	wall_draw_calc(t_all *all)
{

	all->wall_dist = (all->map_cur[all->side] - all->plr[all->side]
		+ (1.0 - all->step[all->side]) / 2.0) / all->ray_dir[all->side];

//	if (all->side == X_SIDE)
//		all->wall_dist = (all->map_x - all->plr[X_SIDE] + (1.0 - all->step[X_SIDE])
//				/ 2.0) / all->ray_dir[X_SIDE];
//	else
//		all->wall_dist = (all->map_y - all->plr[Y_SIDE] + (1.0 - all->step[Y_SIDE])
//				/ 2.0) / all->ray_dir[Y_SIDE];
	all->line_height = (int)(all->res_y * all->coef / all->wall_dist);
	all->draw_start = all->res_y / 2 - all->line_height / 2;
	all->draw_end = all->res_y / 2 + all->line_height / 2;
	if (all->draw_start < 0)
		all->draw_start = 0;
	if (all->draw_end >= all->res_y)
		all->draw_end = all->res_y - 1;
}

void	tex_calc(t_all *all)
{
	double	wall_x;
	double	step;
	int		tex_x;

	find_tex_id(all);

//	wall_x = all->plr[all->side] + all->wall_dist * all->ray_dir[all->side];
	if (all->side == X_SIDE)
		wall_x = all->plr[Y_SIDE] + all->wall_dist * all->ray_dir[Y_SIDE];
	else
		wall_x = all->plr[X_SIDE] + all->wall_dist * all->ray_dir[X_SIDE];
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)all->tex[all->tex_id].width);
	if (all->side == X_SIDE && all->ray_dir[X_SIDE] > 0)
		tex_x = all->tex[all->tex_id].width - tex_x - 1;
	if (all->side == Y_SIDE && all->ray_dir[Y_SIDE] < 0)
		tex_x = all->tex[all->tex_id].width - tex_x - 1;
	step = 1.0 * all->tex[all->tex_id].height / all->line_height;
	fill_walls(all, tex_x, step);
}

void	fill_walls(t_all *all, int tex_x, double step)
{
	int		tex_y;
	double	tex_pos;

	tex_pos = (all->draw_start - all->res_y / 2.0 + all->line_height / 2.0)
		* step;
	while (all->draw_start < all->draw_end)
	{
		tex_y = (int)tex_pos & (all->tex[all->tex_id].height - 1);
		tex_pos += step;
		all->buf[all->draw_start][all->x] = all->tex[all->tex_id].addr
		[all->tex[all->tex_id].height * tex_y + tex_x];
		all->draw_start++;
	}
}
