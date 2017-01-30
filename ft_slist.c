/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 23:02:45 by tdumouli          #+#    #+#             */
/*   Updated: 2017/01/30 00:13:00 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/include/libft.h"
#include <stdlib.h>

int			ft_slstadd(t_slist **adlst, const void *dir, const void *conten)
{
	t_slist		*ret;
	char		*s;
	int			data_siz;
	int			dir_size;

	data_siz = ft_strlen(conten) + 2;
	dir_size = ft_strlen(dir);
	if (!(ret = (t_slist *)malloc(sizeof(t_slist))))
		return (1);
	if (!(ret->data = malloc(dir_size + data_siz)))
		return (1);
	ret->sizeofdir = dir_size;
	s = (char *)ret->data;
	*(s + data_siz + dir_size) = 0;
	while (--data_siz + 1)
		*(s + data_siz + dir_size) = *(char *)(conten + data_siz - 1);
	*(s + dir_size) = '/';
	while (--dir_size + 1)
		*(s + dir_size) = *(char *)(dir + dir_size);
	ret->next = NULL;
	if (*adlst)
		(*adlst)->next = ret;
	*adlst = ret;
	return (0);
}

t_slist		*ft_slstreverse(t_slist **adlst)
{
	t_slist		*tmp;
	t_slist		*def;

	if (!adlst || !*adlst)
		return (NULL);
	if (!((*adlst)->next))
		return (*adlst);
	tmp = *adlst;
	(*adlst) = ft_slstreverse(&((*adlst)->next));
	def = *adlst;
	while (def->next)
		def = def->next;
	tmp->next = NULL;
	def->next = tmp;
	return (*adlst);
}

void		ft_slstdelone(t_slist **adlst)
{
	if (*adlst)
	{
		free((*adlst)->data);
		free(*adlst);
		*adlst = NULL;
	}
}

void		ft_slstdel(t_slist **adlst)
{
	if (*adlst)
	{
		ft_slstdel(&((*adlst)->next));
		ft_slstdelone(adlst);
	}
}
