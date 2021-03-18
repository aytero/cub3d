/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:32 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/03 04:23:34 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		rotate(t_all *all, double angle)
{
	double old_plane_x;
	double old_dir_x;

	old_plane_x = all->plane_x;
	old_dir_x = all->plr_dir_x;
	all->plr_dir_x = all->plr_dir_x * cos(angle) - all->plr_dir_y * sin(angle);
	all->plr_dir_y = old_dir_x * sin(angle) + all->plr_dir_y * cos(angle);
	all->plane_x = all->plane_x * cos(angle) - all->plane_y * sin(angle);
	all->plane_y = old_plane_x * sin(angle) + all->plane_y * cos(angle);
}

static void		move(t_all *all, double angle)
{
	if (all->map[(int)(all->plr_x + all->plr_dir_x * angle)][(int)(all->plr_y)]
					!= '1')
		all->plr_x += all->plr_dir_x * angle;
	if (all->map[(int)(all->plr_x)][(int)(all->plr_y + all->plr_dir_y * SPEED)]
					!= '1')
		all->plr_y += all->plr_dir_y * angle;
}

static void		move_sideways(t_all *all, double angle)
{
	if (all->map[(int)(all->plr_x - all->plr_dir_y * angle)][(int)(all->plr_y)]
					!= '1')
		all->plr_x -= all->plr_dir_y * angle;
	if (all->map[(int)(all->plr_x)][(int)(all->plr_y + all->plr_dir_x * angle)]
					!= '1')
		all->plr_y += all->plr_dir_x * angle;
}

int				deal_key(int keycode, t_all *all)
{
	if (keycode == UP || keycode == W)
		move(all, SPEED);
	else if (keycode == DOWN || keycode == S)
		move(all, -SPEED);
	else if (keycode == LEFT)
		rotate(all, SPEED);
	else if (keycode == RIGHT)
		rotate(all, -SPEED);
	else if (keycode == A)
		move_sideways(all, SPEED);
	else if (keycode == D)
		move_sideways(all, -SPEED);
	else if (keycode == ESC)
		exit_cube(all);
	return (0);
}
