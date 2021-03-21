/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:18:22 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/20 20:33:58 by ayto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calc_hit(t_all *all)
{
	while (all->hit != 1 && all->map_x > 0 && all->map_y > 0
			&& all->map_y < all->res_y - 1 && all->map_x < all->res_x - 1)
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
	return (all->hit);
}

void	cast_rays(t_all *all)
{
	init_rc(all);

	all->delta_dist_y = fabs(1 / all->ray_dir_y);
	all->delta_dist_x = fabs(1 / all->ray_dir_x);
	all->side_dist_x = all->ray_dir_x >= 0
			? (all->map_x + 1.0 - all->plr_x) * all->delta_dist_x
			: (all->plr_x - all->map_x) * all->delta_dist_x;
	all->step_x = all->ray_dir_x >= 0 ? 1 : -1;
	all->side_dist_y = all->ray_dir_y >= 0
			? (all->map_y + 1.0 - all->plr_y) * all->delta_dist_y
			: (all->plr_y - all->map_y) * all->delta_dist_y;
	all->step_y = all->ray_dir_y >= 0 ? 1 : -1;
	if (!calc_hit(all))
		return ;
}

void 	wall_draw_calc(t_all *all)
{
	if (all->side == 0)
		all->wall_dist = (all->map_x - all->plr_x + (1.0 - all->step_x)
						/ 2.0) / all->ray_dir_x;
	else
		all->wall_dist = (all->map_y - all->plr_y + (1.0 - all->step_y)
						/ 2.0) / all->ray_dir_y;
	all->line_height = (int)(all->res_y / all->wall_dist);
	all->draw_start = all->res_y / 2 - all->line_height / 2;
	all->draw_end = all->res_y / 2 + all->line_height / 2;
	if (all->draw_start < 0)
		all->draw_start = 0;
	if (all->draw_end >= all->res_y)
		all->draw_end = all->res_y - 1;
}

void 	tex_calc(t_all *all)
{
	double wall_x;
	double step;
	int tex_x;

	find_tex_id(all);
	if (all->side == 0)
		wall_x = all->plr_y + all->wall_dist * all->ray_dir_y;
	else
		wall_x = all->plr_x + all->wall_dist * all->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int) (wall_x * (double) all->tex[all->tex_id].width);
	if (all->side == 0 && all->ray_dir_x > 0)
		tex_x = all->tex[all->tex_id].width - tex_x - 1;
	if (all->side == 1 && all->ray_dir_y < 0)
		tex_x = all->tex[all->tex_id].width - tex_x - 1;
	step = 1.0 * all->tex[all->tex_id].height / all->line_height;
	fill_buffer(all, tex_x, step);
}

void 	fill_buffer(t_all *all, int tex_x, double step)
{
	int 	tex_y;
	double 	tex_pos;

	tex_pos = (all->draw_start - all->res_y / 2.0 + all->line_height / 2.0)
			* step;
	while (all->draw_start < all->draw_end)
	{
		tex_y = (int)tex_pos & (all->tex[all->tex_id].height - 1);
	//	if ((int)tex_pos >= all->tex[all->tex_id].height)
	//		tex_y = (int)tex_pos % all->tex[all->tex_id].height - 1;//
	//	else
	//		tex_y = (int)tex_pos;
		tex_pos += step;
//		all->addr[all->line_len / 4 * y + x] = all->tex[all->tex_id].addr[all->tex[all->tex_id].height * tex_y + tex_x];
		all->buf[all->draw_start][all->x]
				= all->tex[all->tex_id].addr[all->tex[all->tex_id].height
				* tex_y + tex_x];
		all->draw_start++;
	}
}
