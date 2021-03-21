/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/21 19:19:26 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char 	*get_texture(t_all *all, char **str)
{
	char	*texture;

	//printf("tex str  %s\n", *str);
	while (ft_isalpha(**str))
		(*str)++;
	while (**str == ' ')
		(*str)++;
	if (!(ft_strchr(".", **str)) && !(ft_strchr("/", **str + 1)))
		exit_cube(all, "tex\n");
	//if (!(all->tex_no = malloc(sizeof(char) * (ft_strlen(*str) + 1))))
	if (!(texture = ft_strdup(*str)))
		exit_cube(all, "mess\n");
	//free ? at exit_cube
	return (texture);
}

static void		parse_texture(t_all *all, char **str)
{
//	all->tex_path = malloc(sizeof(char *) * 5);
	if (**str == 'N' && **str + 1 == 'O')
		all->tex_path[0] = get_texture(all, str);
	else if (**str == 'S' && *((*str) + 1) == 'O')
		all->tex_path[1] = get_texture(all, str);
	else if (**str == 'W' && *((*str) + 1) == 'E')
		all->tex_path[2] = get_texture(all, str);
	else if (**str == 'E' && *((*str) + 1) == 'A')
		all->tex_path[3] = get_texture(all, str);
	else if (**str == 'S' && all->tex_path[1])
		all->tex_path[4] = get_texture(all, str);
	//else if
	//	error
	//printf("%s\n", all->tex_path[0]);
}

static unsigned int		rgb_to_hex(int r, int g, int b)
{
	unsigned int 	color;//add padding for zero

	color = (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF));
	return (color);
}

static void	get_res_n_colors(t_all *all, char **str)
{
	int		i;
	unsigned int	color[3];

	while ((**str == ' ' || **str == '\n') && !all->map)
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
	}
	else if (**str == 'F')// || **str == 'C')
	{
		//flag for f or c; or mb global counter; array of cntrs for map lines
		i = -1;
		(*str)++;
		while(++i < 3)
		{
			color[i] = ft_atoi(*str);
			while (**str == ' ' || **str == '\n')
				(*str)++;
			while (ft_isdigit(**str) || **str == ',')
				(*str)++;
		}
		all->fc_color[0] = rgb_to_hex(color[0], color[1], color[2]);
	}
	else if (**str == 'C')
	{
		//flag for f or c; or mb global counter; array of cntrs for map lines
		i = -1;
		(*str)++;
		while (++i < 3)
		{
			color[i] = ft_atoi(*str);
			while (**str == ' ' || **str == '\n')
				(*str)++;
			while (ft_isdigit(**str) || **str == ',')
				(*str)++;
		}
		//printf("color  %x\n", all->fc_color[0]);
		all->fc_color[1] = rgb_to_hex(color[0], color[1], color[2]);
		//printf("color  %x\n", all->fc_color[1]);
	}
		//else if ()
		//error
}


static void		map(t_all *all, char **str)
{
	//printf("cntr %d\n", all->cntr);
	if (!all->res_x || !all->res_y || all->fc_color[0] == 0
		|| all->fc_color[1] == 0 || !all->tex_path[0] || !all->tex_path[1]
		|| !all->tex_path[2] || !all->tex_path[3] || !all->tex_path[4])
		return ;
	//printf("%s\n", all->map[0]);


	//printf("str %s\n", *str);
	all->cntr++;
	all->map[all->cntr] = ft_strdup(*str);
	//(void)str;

	printf("cntr %d     map %s\n", all->cntr, all->map[all->cntr]);
}


static void read_config(t_all *all, int fd)
{
	char 	*str;

	str = NULL;
	all->cntr = -1;
	if (!(all->map = malloc(sizeof(char *) * 10)))//num of lines
	{
		write(1, "wtf\n", 4);
		exit (0);
	}
	while (get_next_line(fd, &str))
	{
		//printf("gnl str %s\n", str);
		get_res_n_colors(all, &str);
		//printf("str %s\n", str);
		parse_texture(all, &str);
		map(all, &str);
		//free(str);
	}
	free(str);
	printf("x %d  y %d\n", all->res_x, all->res_y);
	printf("tex0 %s\n", all->tex_path[0]);
	printf("tex1 %s\n", all->tex_path[1]);
	printf("tex2 %s\n", all->tex_path[2]);
	printf("tex3 %s\n", all->tex_path[3]);
	printf("tex4 %s\n", all->tex_path[4]);
	printf("F    %x\n", all->fc_color[0]);
	printf("C    %x\n", all->fc_color[1]);
	//skip empty lines
		//parse_texture(all, &str);
		//get_res_n_colors(all, &str);
	//get_next_line(fd, &str);
		// if map return ? or strdup
//	free(str);//leaks without it
}

/*
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
*/

void		parse_file(t_all *all, char *file)
{
	int		fd;
	char	*tab;

	tab = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
	{
		exit_cube(all, "Failed to read map\n");
	}
	read_config(all, fd);
//	tab = read_map(fd, tab);
//	all->map = ft_split(tab, '\n');//split skips empty lines as just divider
	close(fd);
	free(tab);
}
