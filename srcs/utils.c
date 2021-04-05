/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:29:33 by lpeggy            #+#    #+#             */
/*   Updated: 2021/04/05 17:08:36 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		atoi_res(const char *str)
{
	int		res;

	if (ft_strchr(str, ','))
		return (-1);
	res = 0;
	while (*str && (*str == ' '))
		str++;
	if (*str == '-' || *str == '+' || *str == '0')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > 21474836)
			break ;
		str++;
	}
	return (res);
}

int		atoi_color(const char *str)
{
	int		color;

	color = 0;
	while (*str && (*str == ' '))
		str++;
	if (*str == '-' || *str == '+' || (*str == '0' && *(str + 1) == '0'))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		color = color * 10 + *str - '0';
		if (color > 21474836)
			break ;
		str++;
	}
	if (color > 255)
		return (-1);
	return (color);
}
