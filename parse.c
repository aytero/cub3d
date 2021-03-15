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

static void get_params(t_all *all)
{
	if (**all->map == 'R')
	{
		(*all->map)++;
		all->win_height = ft_atoi(*all->map);
		while
		all->win_width = ft_atoi(*all->map);
		printf("%d\n", all->win_height);
		printf("%d\n", all->win_width);
	}
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
	}
	return (tab);
}

void		parse_map(t_all *all, char *file)
{
	int		fd;
	char	*tab;

	tab = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
	//	error;
	//	free;
		exit(0);
	}
	tab = read_map(fd, tab);
	all->map = ft_split(tab, '\n');//split skips empty lines as just divider
	get_params(all);
	close(fd);
	free(tab);
}
