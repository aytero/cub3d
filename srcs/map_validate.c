#include "parser.h"

void	map_validate(t_all *all)
{
	int		y;
	int		x;

	y = -1;
	while (++y < all->map_height)
	{
		x = -1;
		while (++x < all->map_width)
		{
			if (!(find_plr(all, y, x)))
				exit_cube(all, "Invalid player position\n");
			if (all->map[y][x] != '0' && all->map[y][x] != '2')
				continue ;
			if (x == 0 || y == 0 || y == all->map_height - 1
				|| x == all->map_width - 1)
				exit_cube(all, "Invalid map\n");
			if (all->map[y - 1][x] == ' ' || all->map[y][x - 1] == ' '
				|| all->map[y][x + 1] == ' ' || all->map[y + 1][x] == ' ')
				exit_cube(all, "Invalid map\n");
		}
	}
	if (!all->plr_flag)
		exit_cube(all, "No player in the map\n");
}

static void	init_plane(t_all *all)
{
	if (all->plr_dir[X_SIDE] == -1)
		all->plane[Y_SIDE] = 0.66;
	else if (all->plr_dir[X_SIDE] == 1)
		all->plane[Y_SIDE] = -0.66;
	else if (all->plr_dir[Y_SIDE] == -1)
		all->plane[X_SIDE] = -0.66;
	else if (all->plr_dir[Y_SIDE] == 1)
		all->plane[X_SIDE] = 0.66;
}

int	find_plr(t_all *all, int y, int x)
{
	if (all->map[y][x] == '1' || all->map[y][x] == '2' || all->map[y][x] == '0'
		|| all->map[y][x] == ' ')
		return (1);
	if (!all->plr_flag && ft_strchr("NSWE", all->map[y][x]))
	{
		if (all->map[y][x] == 'N')
			all->plr_dir[X_SIDE] = -1;
		if (all->map[y][x] == 'S')
			all->plr_dir[X_SIDE] = 1;
		if (all->map[y][x] == 'W')
			all->plr_dir[Y_SIDE] = -1;
		if (all->map[y][x] == 'E')
			all->plr_dir[Y_SIDE] = 1;
		all->plr[Y_SIDE] = x + 0.5;
		all->plr[X_SIDE] = y + 0.5;
		all->map[y][x] = '0';
		all->plr_flag = 1;
		init_plane(all);
		return (1);
	}
	return (0);
}
