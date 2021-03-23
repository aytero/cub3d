/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:32 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/23 18:51:21 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		rotate(t_all *all, double angle)
{
	double old_plane_x;
	double old_dir_x;

	if (all->keys[4] || all->keys[5])
	{
		if (all->keys[5])
			angle *= -1;
		old_plane_x = all->plane_x;
		old_dir_x = all->plr_dir_x;
		all->plr_dir_x = all->plr_dir_x * cos(angle) - all->plr_dir_y * sin(angle);
		all->plr_dir_y = old_dir_x * sin(angle) + all->plr_dir_y * cos(angle);
		all->plane_x = all->plane_x * cos(angle) - all->plane_y * sin(angle);
		all->plane_y = old_plane_x * sin(angle) + all->plane_y * cos(angle);
	}
}

void		move(t_all *all, double angle)
{
	if (all->keys[0] || all->keys[1])
	{
		if (all->keys[1])
			angle *= -1;
		if (all->map[(int)(all->plr_x + all->plr_dir_x * angle)][(int)(all->plr_y)] != '1')
			all->plr_x += all->plr_dir_x * angle;
		if (all->map[(int)(all->plr_x)][(int)(all->plr_y + all->plr_dir_y * SPEED)] != '1')
			all->plr_y += all->plr_dir_y * angle;
	}
}

void		move_sideways(t_all *all, double angle)
{
	if (all->keys[2] || all->keys[3])
	{
		if (all->keys[3])
			angle *= -1;
		if (all->map[(int)(all->plr_x - all->plr_dir_y * angle)][(int)(all->plr_y)] != '1')
			all->plr_x -= all->plr_dir_y * angle;
		if (all->map[(int)(all->plr_x)][(int)(all->plr_y + all->plr_dir_x * angle)] != '1')
			all->plr_y += all->plr_dir_x * angle;
	}
}
/*
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
		exit_cube(all, 0);
	return (0);
}
 */

int 		key_press(int keycode, t_all *all)
{
	if (keycode == UP || keycode == W)
		all->keys[0] = 1;
	else if (keycode == DOWN || keycode == S)
		all->keys[1] = 1;
	else if (keycode == A)
		all->keys[2] = 1;
	else if (keycode == D)
		all->keys[3] = 1;
	else if (keycode == LEFT)
		all->keys[4] = 1;
	else if (keycode == RIGHT)
		all->keys[5] = 1;
	else if (keycode == ESC)
		exit_cube(all, 0);
	return (0);
}

int 	key_release(int keycode, t_all *all)
{
	if (keycode == UP || keycode == W)
		all->keys[0] = 0;
	else if (keycode == DOWN || keycode == S)
		all->keys[1] = 0;
	else if (keycode == A)
		all->keys[2] = 0;
	else if (keycode == D)
		all->keys[3] = 0;
	else if (keycode == LEFT)
		all->keys[4] = 0;
	else if (keycode == RIGHT)
		all->keys[5] = 0;
	return (0);
}
