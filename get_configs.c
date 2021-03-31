/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_configs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:55:52 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/31 20:40:03 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_str_after(t_all *all, char *str)
{
	int		i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		exit_cube(all, "Symbols after config\n");
}

char		*get_texture_path(t_all *all, char *str)
{
	char	*texture;

	while (*str == ' ')
		str++;
	if (!(ft_strchr(".", *str)) || !(ft_strchr("/", *(str + 1))))
		exit_cube(all, "Invalid texture path\n");
	if (!(texture = ft_strdup(str)))
		exit_cube(all, "Failed to get texture path\n");
	return (texture);
}

void		get_texture(t_all *all, char *str)
{
	if (*str == 'N' && *(str + 1) == 'O' && *(str + 2) == ' ' 
					&& !all->tex_path[0])
		all->tex_path[0] = get_texture_path(all, str + 2);
	else if (*str == 'S' && *(str + 1) == 'O' && *(str + 2) == ' '
					&& !all->tex_path[1])
		all->tex_path[1] = get_texture_path(all, str + 2);
	else if (*str == 'W' && *(str + 1) == 'E' && *(str + 2) == ' '
					&& !all->tex_path[2])
		all->tex_path[2] = get_texture_path(all, str + 2);
	else if (*str == 'E' && *(str + 1) == 'A' && *(str + 2) == ' '
					&& !all->tex_path[3])
		all->tex_path[3] = get_texture_path(all, str + 2);
	else if (*str == 'S' && *(str + 1) == ' ' && !all->tex_path[4])
		all->tex_path[4] = get_texture_path(all, str + 1);
	else
		exit_cube(all, "Invalid textures configuration\n");
}

void		get_res(t_all *all, char *str)
{
	int		screen_res_x;
	int		screen_res_y;

	if (all->res_x || all->res_y)
		exit_cube(all, "Multiple resolution config\n");
	all->res_x = ft_atoi(str);
	while (*str == ' ')
		str++;
	if (*str == '+')
		exit_cube(all, "Invalid resolution config\n");
	while (ft_isdigit(*str))
		str++;
	while (*str == ' ')
		str++;
	all->res_y = ft_atoi(str);
	if (all->res_x < 10 || all->res_y < 10)
		exit_cube(all, "Invalid resolution config\n");
	mlx_get_screen_size(all->mlx, &screen_res_x, &screen_res_y);
	if (all->res_x > screen_res_x)
		all->res_x = screen_res_x;
	if (all->res_y > screen_res_y)
		all->res_y = screen_res_y;
	check_str_after(all, str);
}

int			get_fc_colors(t_all *all, char *str)
{
	int		i;
	int		c[3];
	int		hex;

	if (*str == 'F' && all->fc_color[0] >= 0)
		exit_cube(all, "Multiple floor color config\n");
	if (*str == 'C' && all->fc_color[1] >= 0)
		exit_cube(all, "Multiple ceiling color config\n");
	str++;
	i = 0;
	c[i] = ft_atoi(str);
	while (++i < 3)
	{
		while (*str == ' ')
			str++;
		while (ft_isdigit(*str))
			str++;
		while (*str == ' ' || *str == ',')//skips after last atoi - invalid
			str++;
		c[i] = ft_atoi(str);
		while (ft_isdigit(*str))//
			str++;
		if (c[i] < 0 || c[i] > 255)
			exit_cube(all, "Invalid color\n");
	}
	printf("r %d   g %d   b %d\n", c[0], c[1], c[2]);
	hex = (((c[0] & 0x0FF) << 16) | ((c[1] & 0x0FF) << 8) | (c[2] & 0x0FF));
	printf("str colors:%s:\n", str);
	if (*str)
		exit_cube(all, "Symbols after config\n");
	return (hex);
}
