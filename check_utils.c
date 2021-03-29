/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:08:15 by lpeggy            #+#    #+#             */
/*   Updated: 2021/03/24 21:10:41 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(t_all *all, int argc, char **argv)
{
	int		len;

	if (argc < 2 || argc > 3)
		exit_cube(all, "Invalid number of arguments\n");
	len = ft_strlen(argv[1]);
	if (!((argv[1][len - 1] == 'b' && argv[1][len - 2] == 'u'
			&& argv[1][len - 3] == 'c' && argv[1][len - 4] == '.')))
		exit_cube(all, "Invalid map file extension\n");
	if (argc == 3)
	{
		len = ft_strlen(argv[2]);
		if (ft_strncmp("--save", argv[2], len) || len != 6)
			exit_cube(all, "Invalid third argument\n");
		all->save = 1;
	}
}
