/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/14 20:03:03 by tdumouli         ###   ########.fr       */
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
			return(-1);
		perror(err);
		free(err);
		return(-1);
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
		if (lstat(av[i], &a) < 0)
		{
			while (!(err = ft_strjoin("ft_ls: ", av[i])))
				;
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

	if(!(flag = init_flag_ls()))
		return(3);
	i = 0;
	if (ac < 2)
	{
		dossier(".", flag);
		return (0);
	}
	while (ac != i + 1 && *av[i + 1] == '-' && ++i)
		if ((def(flag, av[i])) == 1)
			return(ft_flag_lstdelone(&flag) + 1);
	if (ac ==  i + 1)
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
	{
		perror(" stat");
		return (-1);
	}
	if (lstat(((t_slist *)t2)->data, &a2) < 0)
	{
		perror(" stat");
		return (-1);
	}
	return (a1.st_mtime - a2.st_mtime);
}

static void	name(const char *lien)
{
	char	buf[1024];
	int		len;

	write(1, " -> ", 4);
	if ((len = readlink(lien, buf, sizeof(buf) - 1)) != -1)
		buf[len] = '\0';
	ft_putstr(buf);
}

int			fichier(char *dir, t_flag_ls *flag, t_slist **tmp, t_slist *ite)
{
	struct stat	a;
	char 		*namef;

	namef = dir;
	if (ite)
		namef = ite->data;
	if (lstat(namef, &a) < 0)
	{
		perror(" stat");
		return (1);
	}
	if (ite && flag->mr && S_ISDIR(a.st_mode) &&
			ft_strcmp((char *)(ite->data + ite->sizeofdir + 1), ".") &&
			ft_strcmp((char *)(ite->data + ite->sizeofdir + 1), ".."))
		ft_slstadd(tmp, dir, ite->data + ite->sizeofdir + 1);
	if (flag->l)
		option_l(a);
	if (ite)
		ft_putstr(ite->data + ite->sizeofdir + 1);
	else
		ft_putstr(namef);
	if (flag->l && S_ISLNK(a.st_mode))
		name(namef);
	write(1, "\n", 1);
	return (0);
}

static void fichiers(t_slist *ite, t_flag_ls *flag, char *dir, t_slist **rec)
{
	t_slist			*tmp;

	tmp = NULL;
	while (ite)
	{
		if (flag->a || *(char *)(ite->data + ite->sizeofdir + 1) != '.')
		{
			fichier(dir, flag, &tmp, ite);
			if (!*rec)
				*rec = tmp;
		}
		ite = ite->next;
	}
}

int			parcourtrep(char *dir, t_flag_ls *flag, DIR	*p_dir, t_slist **rec)
{
	struct dirent	*p_dirent;
	t_slist			*ite;
	t_slist			*tmp;

	tmp = NULL;
	ite = NULL;
	while ((p_dirent = readdir(p_dir)) != NULL)
	{
		if (ft_slstadd(&tmp, dir, p_dirent->d_name))
		{
			ft_slstdel(&ite);
			return (-1);
		}
		if (!ite)
			ite = tmp;
	}
	closedir(p_dir);
	//tmp->next = NULL;
	if (flag->l && (ite->next->next || flag->a))
		total(ite);
	if (flag->t)
		ite = ft_slstsort(&ite, sorttime);
	if (flag->r)
		ite = ft_slstreverse(&ite);
	fichiers(ite, flag, dir, rec);
	ft_slstdel(&ite);
	return(0);	
}

int			dossier(char *dir, t_flag_ls *flag)
{
	t_slist			*rec;
	DIR				*p_dir;
	char			*err;

	rec = NULL;
	if ((p_dir = opendir(dir)) == NULL)
	{
		while (!(err = ft_strjoin("ft_ls: ", ft_strrchr(dir, '/') + 1)))
			;
		perror(err);
		free(err);
		return (-1);
	}
	parcourtrep(dir, flag, p_dir, &rec);
	if (flag->mr)
		recu(rec, flag);
	ft_slstdel(&rec);
	return (0);
}
