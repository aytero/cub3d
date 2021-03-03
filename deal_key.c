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

static void rotate(t_all *all, int keycode)
{
	double old_plane_x = all->plane_x;
	double old_dir_x = all->plr_dir_x;

	if (keycode == RIGHT)
	{
		all->plr_dir_x = all->plr_dir_x * cos(-SPEED) - all->plr_dir_y * sin(-SPEED);
		all->plr_dir_y = old_dir_x * sin(-SPEED) + all->plr_dir_y * cos(-SPEED);
		all->plane_x = all->plane_x * cos(-SPEED) - all->plane_y * sin(-SPEED);
		all->plane_y = old_plane_x * sin(-SPEED) + all->plane_y * cos(-SPEED);
	}
	else if (keycode == LEFT)
	{
		all->plr_dir_x = all->plr_dir_x * cos(SPEED) - all->plr_dir_y * sin(SPEED);
		all->plr_dir_y = old_dir_x * sin(SPEED) + all->plr_dir_y * cos(SPEED);
		all->plane_x = all->plane_x * cos(SPEED) - all->plane_y * sin(SPEED);
		all->plane_y = old_plane_x * sin(SPEED) + all->plane_y * cos(SPEED);
	}
}

static void	down(t_all *all)
{
	if (all->map[(int)(all->plr_x - all->plr_dir_x * SPEED)][(int)(all->plr_y)] != '1')// !(...)
		all->plr_x -= all->plr_dir_x * SPEED;
	if (all->map[(int)(all->plr_x)][(int)(all->plr_y - all->plr_dir_y * SPEED)] != '1')
		all->plr_y -= all->plr_dir_y * SPEED;
}

static void up(t_all *all)//x & y are messed up; mb int -> unsigned int
{
	if (all->map[(int)(all->plr_x + all->plr_dir_x * SPEED)][(int)(all->plr_y)] != '1')
		all->plr_x += all->plr_dir_x * SPEED;
	if (all->map[(int)(all->plr_x)][(int)(all->plr_y + all->plr_dir_y * SPEED)] != '1')
		all->plr_y += all->plr_dir_y * SPEED;
}

static void move_sideways(t_all *all, int keycode)
{
	if (keycode == A)
	{
		if (all->map[(int)(all->plr_x - all->plr_dir_y * SPEED)][(int)(all->plr_y)] != '1')
			all->plr_x -= all->plr_dir_y * SPEED;
		if (all->map[(int)(all->plr_x)][(int)(all->plr_y + all->plr_dir_x * SPEED)] != '1')
			all->plr_y += all->plr_dir_x * SPEED;
	}
	else if (keycode == D)
	{
		if (all->map[(int)(all->plr_x + all->plr_dir_y * SPEED)][(int)(all->plr_y)] != '1')
			all->plr_x += all->plr_dir_y * SPEED;
		if (all->map[(int)(all->plr_x)][(int)(all->plr_y - all->plr_dir_x * SPEED)] != '1')
			all->plr_y -= all->plr_dir_x * SPEED;
	}
}

int 	deal_key(int keycode, t_all *all)
{
	if (keycode == UP || keycode == W)
		up(all);
	else if (keycode == DOWN || keycode == S)
		down(all);
	else if (keycode == LEFT || keycode == RIGHT)
		rotate(all, keycode);
	else if (keycode == A || keycode == D)
		move_sideways(all, keycode);
	else if (keycode == ESC)
	{
		mlx_destroy_window(all->mlx, all->win);
		exit (0);
	}
	return (0);
}
