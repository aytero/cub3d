/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/05 17:26:33 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		read_map(t_all *all, int fd)
{
	char	*str;

	all->cntr = -1;
	if (!all->map_height || !all->map_width)
		exit_cube(all, "No map\n");
	str = 0;
	if (!(all->map = ft_calloc(sizeof(char *), all->map_height)))
		exit_cube(all, "Memory allocation failed\n");
	all->map_flag = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (map(all, str))
			map_copy(all, str);
		free(str);
		str = 0;
	}
	free(str);
}

static void		read_config(t_all *all, int fd)
{
	char	*str;

	all->fc_color[0] = -1;
	all->fc_color[1] = -1;
	str = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (*str && !map(all, str) && all->map_flag)
			exit_cube(all, "Invalid config file\n");
		if (*str == 'F')
			all->fc_color[0] = get_fc_colors(all, str);
		if (*str == 'C')
			all->fc_color[1] = get_fc_colors(all, str);
		if (*str == 'R')
			get_res(all, str + 1);
		if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
			get_texture(all, str);
		get_map_size(all, str);
		if (!ft_strchr("RNSWEFC", *str) && !all->map_flag)
			exit_cube(all, "Excess symbols in the file\n");
		free(str);
		str = 0;
	}
	free(str);
}

void			parse_file(t_all *all, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		exit_cube(all, "Failed to read map file\n");
	read_config(all, fd);
	close(fd);
	if ((fd = open(file, O_RDONLY)) < 0)
		exit_cube(all, "Failed to read map file\n");
	read_map(all, fd);
	close(fd);
	map_validate(all);
}
