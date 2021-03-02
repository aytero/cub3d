/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:25:59 by lpeggy            #+#    #+#             */
/*   Updated: 2020/11/25 15:19:45 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strchr_n(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

/*
char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (len1--)
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (len2--)
		str[i++] = s2[j++];
	str[i] = '\0';
	free((void *)s1);
	return (str);
}
*/

t_lst		*ft_lstnew_fd(int fd)
{
	t_lst	*elem;

	if (!(elem = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	if (elem)
	{
		elem->fd = fd;
		elem->reminder = NULL;
		elem->content = 1;
		elem->next = NULL;
	}
	return (elem);
}

void		ft_cleanlst_fd(t_lst **head, int fd)
{
	t_lst	*del;
	t_lst	*prev;

	del = *head;
	prev = NULL;
	while (del)
	{
		if (del->fd == fd)
		{
			if (prev)
				prev->next = del->next;
			else
				*head = del->next;
			free(del->reminder);
			free(del);
			return ;
		}
		else
			prev = del;
		del = del->next;
	}
}
