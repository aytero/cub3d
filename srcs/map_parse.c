/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:00:19 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/05 17:30:01 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			map(t_all *all, char *str)
{
	int		i;

	if (!*str && all->map_flag)
		exit_cube(all, "Invalid map\n");
	i = 0;
	if (ft_strchr(str, '1') || ft_strchr(str, '0') || ft_strchr(str, '2'))
	{
		while (str[i])
		{
			if (!(ft_strchr("NSWE012 ", str[i])))
			{
				if (all->map_flag)
					exit_cube(all, "Invalid symbols in the map\n");
				return (0);
			}
			i++;
		}
		all->map_flag = 1;
		return (1);
	}
	return (0);
}

void		get_map_size(t_all *all, char *str)
{
	int		i;

	if (map(all, str))
	{
		if (!all->res_x || !all->res_y || all->fc_color[0] == -1
			|| all->fc_color[1] == -1 || !all->tex_path[0] || !all->tex_path[1]
			|| !all->tex_path[2] || !all->tex_path[3] || !all->tex_path[4])
			exit_cube(all, "Some configs are missing\n");
		all->map_height++;
		i = 0;
		while (str[i])
			i++;
		if (i > all->map_width)
			all->map_width = i;
	}
}

void		map_copy(t_all *all, char *str)
{
	int		i;

	all->cntr++;
	if (!(all->map[all->cntr] = malloc(sizeof(char)
									* (all->map_width + 1))))
		exit_cube(all, "Memory allocation failed\n");
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr("NSWE012 ", str[i]))
			exit_cube(all, "Invalid symbols in the map\n");
		all->map[all->cntr][i] = str[i];
	}
	i--;
	while (++i < all->map_width)
		all->map[all->cntr][i] = ' ';
	all->map[all->cntr][i] = '\0';
}
