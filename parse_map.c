/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:00:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/23 23:24:21 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_validate(t_all *all)
{
	int		y;
	int		x;

	y = -1;
	while (++y < all->map_lines)//make it recursive ?
	{
		x = -1;
		while (++x < all->max_line_len)
		{
			//printf("here y %d   x %d\n", y, x);
			if (!(find_plr(all, y, x)))
				exit_cube(all, "Player\n");
			if (all->map[y][x] != '0')
				continue;
			if (x == 0 || y == 0 || y == all->map_lines - 1
			 || x == all->max_line_len - 1)
				exit_cube(all, "Invalid map 1\n");
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
		all->plr_y = x + 0.2;
		all->plr_x = y + 0.2;
		all->map[y][x] = '0';
		all->plr = 1;
		return (1);
	}
	return (0);//error
}

void 	find_sprites(t_all *all, t_sprite *sprt)
{
	int i;
	int j;
	int	num;

	i = -1;
	while (++i < all->map_lines)
	{
		j = -1;
		while (++j < all->max_line_len)
		{
			if (all->map[i][j] == '2')
				all->nbr_sprt++;
		}
	}
	if (!(sprt->order = malloc(sizeof(int) * all->nbr_sprt)))
		exit_cube(all, "Memory allocation failed\n");
	if (!(sprt->dist = malloc(sizeof(double) * all->nbr_sprt)))
		exit_cube(all, "Memory allocation failed\n");
	if (!(all->sprt_cords = malloc(sizeof(t_sprt_cords) * all->nbr_sprt)))
		exit_cube(all, "Memory allocation failed\n");
	i = -1;
	num = 0;
	while (++i < all->map_lines)
	{
		j = -1;
		while (++j < all->max_line_len)
		{
			if (all->map[i][j] == '2')
			{
				all->sprt_cords[num].x = i;
				all->sprt_cords[num].y = j;
				num++;
			}
		}
	}
}
