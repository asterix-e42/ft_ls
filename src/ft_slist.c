/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 23:02:45 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/12 19:05:49 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/include/libft.h"
#include <stdlib.h>
/*
static int	ft_slstfind(void *content, t_slist *lstf)
{
	while (lstf && lstf->next)
	{
		if (!ft_strcmp(content, lstf->data))
			return (1);
		lstf = lstf->next;
	}
	return (0);
}*/

int			ft_slstadd(t_slist **lst, void *dir, void *ct, t_slist *lstf)
{
	t_slist		*ret;
	char		*s;
	int			data_siz;
	int			dir_size;

	(void)lstf;
	//if (ft_slstfind(ct, lstf))
	//	return (2);
	dir_size = ft_strlen(dir);
	data_siz = ft_strlen(ct) + 2 * !(dir == NULL) - (dir_size == 1);
	if (!(ret = (t_slist *)malloc(sizeof(t_slist))))
		return (1);
	if (!(ret->data = malloc(dir_size + data_siz)))
		return (1);
	ret->sizeofdir = dir_size;
	s = (char *)ret->data;
	*(s + data_siz + dir_size) = 0;
	while (--data_siz + 1)
		*(s + data_siz + dir_size) = *(char *)(ct + data_siz - !(!dir));
	if (dir)
		*(s + dir_size) = '/';
	while (--dir_size + 1)
		*(s + dir_size) = *(char *)(dir + dir_size);
	ret->next = NULL;
	if (*lst)
		(*lst)->next = ret;
	*lst = ret;
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
		if ((*adlst)->data)
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
