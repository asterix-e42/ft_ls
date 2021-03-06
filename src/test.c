/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/14 16:44:51 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "libft/include/libft.h"
#include <sys/stat.h>
#include "ls.h"
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

int			onething(char *av, t_flag_ls *flag)
{
	char			*err;
	struct stat		a;

	if (lstat(av, &a) < 0)
	{
		if (!(err = ft_strjoin("ft_ls: ", av)))
			return (-1);
		perror(err);
		free(err);
		return (-1);
	}
	else if (S_ISDIR(a.st_mode))
		dossier(av, flag);
	else
		fichier(av, flag, NULL, NULL);
	return (0);
}

int			morething(char **av, t_flag_ls *flag, int i, int ac)
{
	char			*err;
	struct stat		a;
	t_slist			*rep;
	t_slist			*tmp;

	rep = NULL;
	tmp = NULL;
	while (ac != ++i)
		if (stat(av[i], &a) < 0)
		{
			(err = ft_strjoin("ft_ls: ", av[i]));
			perror(err);
			free(err);
		}
		else if (S_ISDIR(a.st_mode))
		{
			ft_slstadd(&tmp, NULL, av[i]);
			if (!rep)
				rep = tmp;
		}
		else
			fichier(av[i], flag, NULL, NULL);
	recu(rep, flag);
	ft_slstdel(&rep);
	return (0);
}

int			main(int ac, char *av[])
{
	int				i;
	t_flag_ls		*flag;

	if (!(flag = init_flag_ls()))
		return (3);
	i = 0;
	if (ac < 2)
	{
		dossier(".", flag);
		return (0);
	}
	while (ac != i + 1 && *av[i + 1] == '-' && ++i)
		if ((def(flag, av[i])) == 1)
			return (ft_flag_lstdelone(&flag));
	if (ac == (i + 1))
		dossier(".", flag);
	else if (ac == i + 2)
		onething(av[i + 1], flag);
	else
		morething(av, flag, i, ac);
	ft_flag_lstdelone(&flag);
	return (0);
}

void		recu(t_slist *rec, t_flag_ls *flag)
{
	while (rec)
	{
		write(1, "\n", 1);
		ft_putstr((((rec)->data)));
		write(1, ":\n", 2);
		dossier((rec)->data, flag);
		rec = rec->next;
	}
}

int			sorttime(void *t1, void *t2)
{
	struct stat		a1;
	struct stat		a2;

	if (lstat(((t_slist *)t1)->data, &a1) < 0)
		return (0);
	if (lstat(((t_slist *)t2)->data, &a2) < 0)
		return (0);
	return (a1.st_mtime - a2.st_mtime);
}
