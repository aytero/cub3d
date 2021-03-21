/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/21 01:49:43 by ayto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
static char 	*get_texture(t_all *all, char **str)
{
	char	*texture;

	while (ft_isalpha(**str))
		(*str)++;
	if (!(ft_strchr(*str, '.')) && !(ft_strchr(*str + 1, '/')))
		exit_cube(all, "tex\n");
	//if (!(all->tex_no = malloc(sizeof(char) * (ft_strlen(*str) + 1))))
	if (!(texture = ft_strdup(*str)))
		exit_cube(all, "mess\n");
	//free ? at exit_cube
	return (texture);
}

static void		parse_texture(t_all *all, char **str)
{
	if (**str == 'N' && **str + 1 == 'O')
		all->tex_no = get_texture(all, str);
//	else if (**str == 'S' && **str + 1 == 'O')
//		all->tex_so = get_texture(all, *str);
//	else if (**str == 'W' && **str + 1 == 'E')
//		all->tex_we = get_texture(all, *str);
//	else if (**str == 'E' && **str + 1 == 'A')
//		all->tex_ea = get_texture(all, *str);
//	else if (**str == 'S')
//		all->tex_sprt = get_texture(all, *str);
	//else if
	//	error
	printf("%s\n", all->tex_no);
}
*/

/*
static unsigned int		rgb_to_hex(int r, int g, int b)
{
	unsigned int 	color;

	color = (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
	return (color);
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
		while (**str == ' ' || **str == '\n' || **str == ',')
			(*str)++;
		while (ft_isdigit(**str))
			(*str)++;
		(*str)++;
		all->res_y = ft_atoi(*str);
		printf("x %d  y %d\n", all->res_x, all->res_y);
	}
	else if (**str == 'F')// || **str == 'C')
	{
		//flag for f or c; or mb global counter; array of cntrs for map lines
		unsigned int	color[3];
		int i = -1;
		(*str)++;
		while(++i < 3)
		{
			color[i] = ft_atoi(*str);
			while (**str == ' ' || **str == '\n')
				(*str)++;
			while (ft_isdigit(**str) || **str == ',')
				(*str)++;
		}
		all->floor_color = rgb_to_hex(color[0], color[1], color[2]);
	}
	//else if ()
		//error
}
*/

static void read_config(t_all *all, int fd)
{
	char 	*str;

	str = NULL;
	get_next_line(fd, &str);
	//skip empty lines
		//parse_texture(all, &str);
		//get_res_n_colors(all, &str);
	//get_next_line(fd, &str);
		// if map return ? or strdup
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
