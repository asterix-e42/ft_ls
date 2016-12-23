/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 23:02:45 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/23 07:27:17 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include <stdlib.h>

int		ft_slstadd(t_slist **adlst, const void *dir, const void *conten)
{
	t_slist	*ret;
	char	*s;
	int		data_siz;
	int		dir_size;

	if (!conten)
		return (2);
	data_siz = ft_strlen(conten) + 1;
	dir_size = ft_strlen(dir) + 1;
	if (!(ret = (t_slist *)malloc(sizeof(t_slist))))
		return (1);
	if (!(ret->data = malloc(dir_size + data_siz)))
		return (1);
	s = (char *)ret->data;
	*(s + data_siz + 2) = 0;
	while (--data_siz)
		*(s + data_siz + dir_size - 1) = *(char *)(conten + data_siz - 1);
	*(s + dir_size) = '/';
	while (--dir_size)
		*(s + dir_size - 1) = *(char *)(dir + dir_size - 1);
	ret->next = NULL;
	if (*adlst)
		(*adlst)->next = ret;
	*adlst = ret;
	return (0);
}

void	ft_slstdelone(t_slist **adlst)
{
	if (*adlst)
	{
		free((*adlst)->data);
		free(*adlst);
		*adlst = NULL;
	}
}

void	ft_slstdel(t_slist **adlst)
{
	if (*adlst)
	{
		ft_slstdel(&((*adlst)->next));
		ft_slstdelone(adlst);
	}
}
