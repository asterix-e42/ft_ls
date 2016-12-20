/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 22:40:59 by tdumouli          #+#    #+#             */
/*   Updated: 2016/11/11 12:55:28 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*deb;

	if (!lst || !f)
		return (NULL);
	ret = f(lst);
	deb = ret;
	while (lst->next)
	{
		lst = lst->next;
		if (!(ret->next = f(lst)))
		{
			free(ret);
			return (NULL);
		}
		ret = ret->next;
	}
	return (deb);
}
