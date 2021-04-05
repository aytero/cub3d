/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_configs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 20:55:52 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/05 17:24:55 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (*str != ' ' || all->res_x || all->res_y)
		exit_cube(all, "Invalid resolution config\n");
	all->res_x = atoi_res(str);
	while (*str == ' ')
		str++;
	while (ft_isdigit(*str))
		str++;
	all->res_y = atoi_res(str);
	while (*str == ' ')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str || all->res_x < 1 || all->res_y < 1)
		exit_cube(all, "Invalid resolution config\n");
	mlx_get_screen_size(all->mlx, &screen_res_x, &screen_res_y);
	if (all->res_x > screen_res_x)
		all->res_x = screen_res_x;
	if (all->res_y > screen_res_y)
		all->res_y = screen_res_y;
}

int			get_fc_colors(t_all *all, char *str)
{
	int		i;
	int		c[3];
	int		hex;

	if (*str == 'F' && (all->fc_color[0] >= 0 || *(str + 1) != ' '))
		exit_cube(all, "Invalid floor color config\n");
	if (*str == 'C' && (all->fc_color[1] >= 0 || *(str + 1) != ' '))
		exit_cube(all, "Invalid ceiling color config\n");
	str++;
	i = -1;
	while (++i < 3)
	{
		c[i] = atoi_color(str);
		while (*str == ' ')
			str++;
		while (ft_isdigit(*str))
			str++;
		if (*str == ',' && (*(str + 1) == ' ' || ft_isdigit(*(str + 1))))
			str++;
	}
	if (*str || c[0] < 0 || c[1] < 0 || c[2] < 0)
		exit_cube(all, "Invalid color config\n");
	hex = (((c[0] & 0x0FF) << 16) | ((c[1] & 0x0FF) << 8) | (c[2] & 0x0FF));
	return (hex);
}
