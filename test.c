/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/23 07:27:24 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include "ls.h"

#include<stdio.h>

int main (int ac, char *av[])
{
	if (ac < 2)
		affiche(".");
	else
		affiche(av[1]);
	return 0;
}

int affiche(char *dir)
{
	struct dirent *pDirent;
	DIR *pDir;
	struct stat a;
	t_slist *rec;
	t_slist *tmp;

	if (!(pDir = opendir (dir)))
		ft_erreur("Cannot open directory");
	while ((pDirent = readdir(pDir)) != NULL)
	{
		stat(pDirent->d_name, &a);
		if(S_ISDIR(a.st_mode) && *pDirent->d_name != '.')
		{
			ft_slstadd(&tmp, dir, pDirent->d_name);
			if (!rec)
				rec = tmp;
		ft_putstr(tmp->data);
		}
	//	ft_putstr(pDirent->d_name);
		write(1, "\n", 1);
	}
	while(rec)
	{
		//ft_putstr(rec->data);
		//affiche(rec->data);
		rec = rec->next;
	}
	closedir (pDir);
	return 0;
}
