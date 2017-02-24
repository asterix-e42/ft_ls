/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 19:33:05 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/24 06:54:56 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdlib.h>
#include <unistd.h>

t_flag_ls	*init_flag_ls(void)
{
	t_flag_ls *tmp;

	tmp = (t_flag_ls *)malloc(sizeof(t_flag_ls));
	tmp->mr = 0;
	tmp->r = 0;
	tmp->a = 0;
	tmp->l = 0;
	tmp->t = 0;
	tmp->max_lnk = 0;
	tmp->max_uid = 0;
	tmp->max_gid = 0;
	tmp->max_siz = 0;
	return (tmp);
}

int			def(t_flag_ls *flag, char *chain)
{
	while (*(++chain))
	{
		if (*chain == 'l')
			flag->l = 1;
		else if (*chain == 'R')
			flag->mr = 1;
		else if (*chain == 'r')
			flag->r = 1;
		else if (*chain == 't')
			flag->t = 1;
		else if (*chain == 'a')
			flag->a = 1;
		else
		{
			write(2, "ft_ls: illegal option -- ", 25);
			write(2, chain, 1);
			write(2, "\nusage: ft_ls[-Ralrt] [file ...]\n", 33);
			return (1);
		}
	}
	return (0);
}

int			ft_flag_lstdelone(t_flag_ls **adlst)
{
	if (*adlst)
	{
		free(*adlst);
		*adlst = NULL;
	}
	return (1);
}
