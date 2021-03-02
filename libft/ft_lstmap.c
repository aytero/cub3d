/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeggy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:54:40 by lpeggy            #+#    #+#             */
/*   Updated: 2020/11/20 22:28:17 by lpeggy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*elem_new;

	if (!lst || !f)
		return (NULL);
	lst_new = NULL;
	while (lst)
	{
		if (!(elem_new = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_new, elem_new);
		lst = lst->next;
	}
	return (lst_new);
}
