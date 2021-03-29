/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/27 18:44:09 by ayto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//static void		validate_file_line(t_all *all, char *str)
//{
//	if (str == NULL)
//		return ;
//	printf("str val  %s\n", str);
//	if (!ft_strchr(str, 'R') && !ft_strchr(str, 'F') && !ft_strchr(str, 'C')
//		&& !ft_strchr(str, 'N') && !ft_strchr(str, 'S') && !ft_strchr(str, 'W')
//		&& !ft_strchr(str, 'E') && !all->map_flag)
//		exit_cube(all, "Symbol gotcha\n");
//}

static int		map(t_all *all, char *str)
{
	int		i;

//	if (!*str && all->map_flag)
//		exit_cube(all, "Invalid map\n");
	if (!*str && all->map_flag)
		exit_cube(all, "Invalid map\n");
	i = 0;
	if (ft_strchr(str, '1') || ft_strchr(str, '0'))
	{
			printf("str is map?   %s\n", str);
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

static void		get_map_size(t_all *all, char *str)
{
	int 	i;

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

static void		map_copy(t_all *all, char *str)
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
			exit_cube(all, "Invalid symbols in the map\n");// in the file
		all->map[all->cntr][i] = str[i];
	}
	i--;
	while (++i < all->map_width)
		all->map[all->cntr][i] = ' ';
	all->map[all->cntr][i] = '\0';
}

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
	while (get_next_line(fd, &str))
	{
		if (map(all, str))
			map_copy(all, str);
		free(str);
		str = 0;
	}
	free(str);
}

static void read_config(t_all *all, int fd)
{
	char 	*str;

	all->fc_color[0] = -1;
	all->fc_color[1] = -1;
	str = 0;
	while (get_next_line(fd, &str))
	{
//		validate_file_line(all, str);
//		if (!ft_strchr("RNSWEFC 012", *str) && !all->map_flag)
//			exit_cube(all, "Excess symbols in the file\n");
		if (*str == 'F')
			all->fc_color[0] = get_fc_colors(all, str);
		if (*str == 'C')
			all->fc_color[1] = get_fc_colors(all, str);
		if (*str == 'R')
			get_res(all, str);
		if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
			get_texture(all, str);
		get_map_size(all, str);
//		if (all->map_flag && !(ft_strchr("NSWE012 ", *str)))
//			exit_cube(all, "Invalid symbols in map\n");
		free(str);
		str = 0;
	}
	free(str);
}

void		parse_file(t_all *all, char *file)
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

	printf("plr x  %f\n", all->plr_x);
	printf("plr y  %f\n", all->plr_y);

	printf("x %d  y %d\n", all->res_x, all->res_y);
	printf("tex0 %s\n", all->tex_path[0]);
	printf("tex1 %s\n", all->tex_path[1]);
	printf("tex2 %s\n", all->tex_path[2]);
	printf("tex3 %s\n", all->tex_path[3]);
	printf("tex4 %s\n", all->tex_path[4]);
	printf("F    %x\n", all->fc_color[0]);
	printf("C    %x\n", all->fc_color[1]);
}
