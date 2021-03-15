/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:18:22 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/15 18:18:24 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void 	init_rc(t_all *all)
{
	all->camera_x = 2 * all->x / (double)all->win_width - 1;
	all->ray_dir_x = all->plr_dir_x + all->plane_x * all->camera_x;
	all->ray_dir_y = all->plr_dir_y + all->plane_y * all->camera_x;
	all->map_x = (int)(all->plr_x);
	all->map_y = (int)(all->plr_y);
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
//	if (calc_hit(all) <= 0)
//		return ;
	calc_hit(all);
}

void 	draw_calc(t_all *all)
{
	if (all->side == 0)
		all->perp_wall_dist = (all->map_x - all->plr_x + (1.0 - all->step_x)
				/ 2.0) / all->ray_dir_x;
	else
		all->perp_wall_dist = (all->map_y - all->plr_y + (1.0 - all->step_y)
				/ 2.0) / all->ray_dir_y;
	all->line_height = (int)(all->win_height / all->perp_wall_dist);
	all->draw_start = all->win_height / 2 - all->line_height / 2;
	all->draw_end = all->win_height / 2 + all->line_height / 2;
	if (all->draw_start < 0)
		all->draw_start = 0;
	if (all->draw_end >= all->win_height)// || all->draw_end < 0)// added 2nd condition
		all->draw_end = all->win_height - 1;
}

// TODO
void 	tex_calc(t_all *all)
{
	double wall_x;
	double step;
	int tex_x;

	find_tex_id(all);
	if (all->side == 0)
		wall_x = all->plr_y + all->perp_wall_dist * all->ray_dir_y;
	else
		wall_x = all->plr_x + all->perp_wall_dist * all->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int) (wall_x * (double) all->tex[all->tex_id].img_width);
	if (all->side == 0 && all->ray_dir_x > 0)
		tex_x = all->tex[all->tex_id].img_width - tex_x - 1;//affects WHAT???? kinda side walls + rotation
	if (all->side == 1 && all->ray_dir_y < 0)
		tex_x = all->tex[all->tex_id].img_width - tex_x - 1;
	step = 1.0 * all->tex[all->tex_id].img_height / all->line_height;
	fill_buffer(all, tex_x, step);
}

void 	fill_buffer(t_all *all, int tex_x, double step)
{
	int 	tex_y;
	double 	tex_pos;

//	tex_pos = (all->draw_start - all->draw_end) * step;
	tex_pos = (all->draw_start - all->win_height / 2.0 + all->line_height / 2.0)
			* step;
	while (all->draw_start < all->draw_end)// <= causes digital artifacts
	{
		tex_y = (int)tex_pos & (all->tex[all->tex_id].img_height - 1);
	//	if ((int)tex_pos >= all->tex[all->tex_id].img_height)
	//		tex_y = (int)tex_pos % all->tex[all->tex_id].img_height - 1;//
	//	else
	//		tex_y = (int)tex_pos;
		tex_pos += step;
//		all->addr[all->line_len / 4 * y + x] = all->tex[all->tex_id].addr[all->tex[all->tex_id].img_height * tex_y + tex_x];
		all->buf[all->draw_start][all->x]
			= all->tex[all->tex_id].addr[all->tex[all->tex_id].img_height
			* tex_y + tex_x];
//		all->buf[y][x] = all->color;
		all->draw_start++;
	}
}

void	draw(t_all *all)
{
	int 	y;
	int 	x;

	y = 0;
	while (y < all->win_height)
	{
		x = 0;
		while (x < all->win_width)
		{
			all->addr[all->line_len / 4 * y + x] = all->buf[y][x];
			x++;
		}
		y++;
	}
//	mlx_put_image_to_window(all->mlx, all->win, all->img, 0, 0);
}

