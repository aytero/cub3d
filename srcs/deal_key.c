#include "cub3d.h"

void	rotate(t_all *all, double ang)
{
	double	old_plane_x;
	double	old_dir_x;

	if (all->keys[LEFT_KEY] || all->keys[Q_KEY] || all->keys[RIGHT_KEY] || all->keys[E_KEY])
	{
		if (all->keys[RIGHT_KEY] || all->keys[E_KEY])
			ang *= -1;
		old_plane_x = all->plane[X_SIDE];
		old_dir_x = all->plr_dir[X_SIDE];
		all->plr_dir[X_SIDE] = all->plr_dir[X_SIDE] * cos(ang) - all->plr_dir[Y_SIDE] * sin(ang);
		all->plr_dir[Y_SIDE] = old_dir_x * sin(ang) + all->plr_dir[Y_SIDE] * cos(ang);
		all->plane[X_SIDE] = all->plane[X_SIDE] * cos(ang) - all->plane[Y_SIDE] * sin(ang);
		all->plane[Y_SIDE] = old_plane_x * sin(ang) + all->plane[Y_SIDE] * cos(ang);
	}
}

void	move(t_all *all, double angle)
{
	if (all->keys[UP_KEY] || all->keys[DOWN_KEY] || all->keys[W_KEY] || all->keys[S_KEY])
	{
		if (all->keys[DOWN_KEY] || all->keys[S_KEY])
			angle *= -1;
		if (all->map[(int)(all->plr[X_SIDE] + all->plr_dir[X_SIDE] * angle)]
		[(int)(all->plr[Y_SIDE])] != '1')
			all->plr[X_SIDE] += all->plr_dir[X_SIDE] * angle;
		if (all->map[(int)(all->plr[X_SIDE])]
		[(int)(all->plr[Y_SIDE] + all->plr_dir[Y_SIDE] * angle)] != '1')
			all->plr[Y_SIDE] += all->plr_dir[Y_SIDE] * angle;
	}
}

void	move_sideways(t_all *all, double angle)
{
	if (all->keys[A_KEY] || all->keys[D_KEY])
	{
		if (all->keys[D_KEY])
			angle *= -1;
		if (all->map[(int)(all->plr[X_SIDE] - all->plr_dir[Y_SIDE] * angle)]
		[(int)(all->plr[Y_SIDE])] != '1')
			all->plr[X_SIDE] -= all->plr_dir[Y_SIDE] * angle;
		if (all->map[(int)(all->plr[X_SIDE])]
		[(int)(all->plr[Y_SIDE] + all->plr_dir[X_SIDE] * angle)] != '1')
			all->plr[Y_SIDE] += all->plr_dir[X_SIDE] * angle;
	}
}

int	key_press(int keycode, t_all *all)
{
	if (keycode == ESC_KEY)
		exit_cube(all, 0);
	all->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_all *all)
{
	all->keys[keycode] = 0;
	return (0);
}
