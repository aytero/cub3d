/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/03 04:23:19 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void get_tex_no(t_all *all, char **str)
{
	(void)all;
	if (**str == 'N' && **str + 1 == 'O')
	{
		while (**str != '.' && **str + 1 != '/')
			(*str)++;
	}
		printf("%s\n", *str);
}

static void	get_res(t_all *all, char **str)
{
	while (**str == ' ' || **str == '\n')
		(*str)++;
	if (**str == 'R')
	{
		(*str)++;
		all->res_x = ft_atoi(*str);
		//skip space or comma
		(*str)++;
		all->res_y = ft_atoi(*str);
		printf("x %d  y %d\n", all->res_x, all->res_x);
		//printf("%s\n", *str);
	}
}

static void read_config(t_all *all, int fd)
{
	char 	*str;

	str = NULL;
	get_next_line(fd, &str);
		get_res(all, &str);
	get_next_line(fd, &str);
	get_tex_no(all, &str);
		//get_tex_no(all, str);
		//map;
//	free(str);//leaks without it
}

static char	*read_map(int fd, char *tab)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		// check errors
		tab = ft_strjoin(tab, line);
		tab = ft_strjoin(tab, "\n");
		free(line);
	}
	free(line);
	return (tab);
}

void		parse_map(t_all *all, char *file)
{
	int		fd;
	char	*tab;

	tab = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		exit_cube(all, "Failed to read map\n");
	}
	read_config(all, fd);
	tab = read_map(fd, tab);
	all->map = ft_split(tab, '\n');//split skips empty lines as just divider
	close(fd);
	free(tab);
}
