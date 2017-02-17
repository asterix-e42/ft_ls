/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 23:02:45 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/17 04:25:40 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/include/libft.h"
#include <stdlib.h>

t_slist		*ft_slstremp(char *dir, char *ct)
{
	t_slist		*ret;
//	char		*s;
	char 		sep;
	int			data_siz;
	int			dir_size;

	dir_size = 0;
	sep = 0;
	if (dir && (dir_size = ft_strlen(dir)) != 0)
		sep = 1;
	data_siz = ft_strlen(ct);
	if (!(ret = (t_slist *)malloc(sizeof(t_slist))))
		return (NULL);
	if (!(ret->data = malloc(dir_size + data_siz + sep + 1)))
		return (NULL);
	ret->sizeofdir = dir_size;
	//(char *)ret->data;
	*((char *)ret->data + data_siz + dir_size + sep) = 0;
	while (--data_siz + 1)
		*(ret->data + data_siz + dir_size + sep) = *(char *)(ct + data_siz);
	if (sep)
		*(ret->data + dir_size) = '/';
	while (--dir_size + 1)
		*(ret->data + dir_size) = *(char *)(dir + dir_size);
	ret->next = NULL;
	return(ret);
}

int			ft_slstadd(t_slist **lst, char *dir, char *ct)
{
	t_slist		*cel;

	if (!(cel = ft_slstremp(dir, ct)))
		return(1);
	if (*lst)
		(*lst)->next = cel;
	*lst = cel;
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
			free(((*adlst)->data));
		(*adlst)->data = NULL;
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
