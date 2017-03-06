/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slistsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 19:36:57 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/02 20:17:35 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/include/libft.h"
#include <stdlib.h>

static t_slist	*swap(t_slist *t1, t_slist *t2, t_slist **nlst)
{
	(*nlst) = (*nlst)->next;
	t1->next = t2;
	return (t1);
}

int				ft_slst_strcmp(void *s1, void *s2)
{
	return (~ft_strcmp(((t_slist *)s1)->data, ((t_slist *)s2)->data));
}

void			*ft_slstsort(t_slist **nlst, int (*f)(void *, void *))
{
	t_slist *pivot;
	t_slist *start;
	t_slist *next;
	t_slist *tmp;

	if (!(start = NULL) && !ft_slstreverse(nlst))
		return (NULL);
	next = NULL;
	pivot = *nlst;
	(*nlst) = (*nlst)->next;
	pivot->next = NULL;
	while ((tmp = *nlst))
		if (f((void *)pivot, (void *)tmp) <= 0)
			start = swap(tmp, start, nlst);
		else
			next = swap(tmp, next, nlst);
	if (!ft_slstsort(&start, f))
		start = pivot;
	ft_slstsort(&next, f);
	*nlst = start;
	while (start->next)
		start = start->next;
	start->next = pivot;
	pivot->next = next;
	return (*nlst);
}
