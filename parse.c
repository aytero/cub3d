/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 04:23:17 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/22 23:29:41 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char 	*get_texture(t_all *all, char **str)
{
	char	*texture;

	while (ft_isalpha(**str))
		(*str)++;
	while (**str == ' ')
		(*str)++;
	if (!(ft_strchr(".", **str)) && !(ft_strchr("/", **str + 1)))
		exit_cube(all, "tex\n");
	if (!(texture = ft_strdup(*str)))
		exit_cube(all, "mess\n");
	return (texture);
}

static void		parse_texture(t_all *all, char **str)
{
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
		//if (all->res_x < 0 || all->res_x > max)
		while (**str == ' ' || **str == '\n' || **str == ',')
			(*str)++;
		while (ft_isdigit(**str))
			(*str)++;
		(*str)++;
		all->res_y = ft_atoi(*str);
	}
	else if (**str == 'F')// || **str == 'C')
	{
		(*str)++;
		i = -1;
		while(++i < 3)
		{
			color[i] = ft_atoi(*str);
			if (color[i] < 0 || color[i] > 255)
				exit_cube(all, "Invalid color\n");
			while (**str == ' ' || **str == '\n')
				(*str)++;
			while (ft_isdigit(**str) || **str == ',')
				(*str)++;
		}
		all->fc_color[0] = rgb_to_hex(color[0], color[1], color[2]);
	}
	else if (**str == 'C')
	{
		(*str)++;
		i = -1;
		while (++i < 3)
		{
			color[i] = ft_atoi(*str);
			if (color[i] < 0 || color[i] > 255)
				exit_cube(all, "Invalid color\n");
			while (**str == ' ' || **str == '\n')
				(*str)++;
			while (ft_isdigit(**str) || **str == ',')
				(*str)++;
		}
		all->fc_color[1] = rgb_to_hex(color[0], color[1], color[2]);
	}
		//else if ()
		//error
}

static int		is_map(t_all *all, char *str)
{
	if (*str == '1' || *str == '0' || *str == ' ')
	{
		if (all->res_x && all->res_y && all->fc_color[0] >= 0
			&& all->fc_color[1] >= 0 && all->tex_path[0] && all->tex_path[1]
			&& all->tex_path[2] && all->tex_path[3] && all->tex_path[4])
			return (1);
	}
	return (0);
}

static void		count_map_lines(t_all *all, char **str)
{
	int 	i;

	if (is_map(all, *str))
	{
		all->map_lines++;//doesnt get spaces and \n
		i = 0;
		while ((*str)[i])
			i++;
		if (i > all->max_line_len)
			all->max_line_len = i;
	}
}

static void		map(t_all *all, char **str)
{
	int		i;

	i = 0;
	all->cntr++;
	all->map[all->cntr] = malloc(sizeof(char) * (ft_strlen(*str) + 1));
//	printf("str to map     %s\n", *str);
	while (i < all->max_line_len && (*str)[i])
	{
		all->map[all->cntr][i] = (*str)[i];
		i++;
	}
	all->map[all->cntr][i] = '\0';
//	all->cntr++;
//	all->map[all->cntr] = ft_strdup(*str);
	printf("cntr %d     map %s\n", all->cntr, all->map[all->cntr]);
}

static void		read_map(t_all *all, int fd)
{
	char	*str;

	str = 0;
	printf("lines    %d\n", all->map_lines);
	printf("max len  %d\n", all->max_line_len);

	if (!(all->map = malloc(sizeof(char *) * all->map_lines)))//num of lines
		exit_cube(all, "Memory allocation failed\n");
	while (get_next_line(fd, &str))
	{
		if (is_map(all, str))
			map(all, &str);
		free(str);
	}
	free(str);
}

static void read_config(t_all *all, int fd)
{
	char 	*str;

	all->cntr = -1;
	all->fc_color[0] = -1;
	all->fc_color[1] = -1;

	str = 0;
	while (get_next_line(fd, &str))
	{
		//printf("gnl str %s\n", str);
		get_res_n_colors(all, &str);
		//printf("str %s\n", str);
		parse_texture(all, &str);
		count_map_lines(all, &str);
		str = 0;
		free(str);
	}
	free(str);

	//skip empty lines
		//parse_texture(all, &str);
		//get_res_n_colors(all, &str);
	//get_next_line(fd, &str);
		// if map return ? or strdup
//	free(str);//leaks without it
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

	plr(all);
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
