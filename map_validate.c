/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:00:43 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/26 21:00:45 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_validate(t_all *all)
{
	int		y;
	int		x;

	y = -1;
	while (++y < all->map_height)//make it recursive ?
	{
		x = -1;
		while (++x < all->map_width)
		{
			if (!(find_plr(all, y, x)))
				exit_cube(all, "Invalid player position\n");
			if (all->map[y][x] != '0')
				continue;
			if (x == 0 || y == 0 || y == all->map_height - 1
				|| x == all->map_width - 1)
				exit_cube(all, "Invalid map\n");
			if (all->map[y - 1][x - 1] == ' ' || all->map[y - 1][x] == ' '
				|| all->map[y - 1][x + 1] == ' ' || all->map[y][x - 1] == ' '
				|| all->map[y][x + 1] == ' ' || all->map[y + 1][x - 1] == ' '
				|| all->map[y + 1][x] == ' ' || all->map[y + 1][x + 1] == ' ')
				exit_cube(all, "Invalid map\n");
		}
	}
}

int		find_plr(t_all *all, int y, int x)
{
	if (all->map[y][x] == '1' || all->map[y][x] == '2' || all->map[y][x] == '0'
		|| all->map[y][x] == ' ')
		return (1);
	if (!all->plr && ft_strchr("NSWE", all->map[y][x]))
	{
		if (all->map[y][x] == 'N')
		{
			all->plr_dir_x = -1;
			all->plane_y = 0.66;
		}
		if (all->map[y][x] == 'S')
		{
			all->plr_dir_x = 1;
			all->plane_y = -0.66;
		}
		if (all->map[y][x] == 'W')
		{
			all->plr_dir_y = -1;
			all->plane_x = -0.66;
		}
		if (all->map[y][x] == 'E')
		{
			all->plr_dir_y = 1;
			all->plane_x = 0.66;
		}
		all->plr_y = x + 0.5;
		all->plr_x = y + 0.5;
		all->map[y][x] = '0';
		all->plr = 1;
		return (1);
	}
	return (0);
}
