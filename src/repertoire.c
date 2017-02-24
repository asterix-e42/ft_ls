/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repertoire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:38:41 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/23 16:42:00 by tdumouli         ###   ########.fr       */
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
	struct stat		a;
	char			*namef;

	namef = dir;
	if (ite)
		namef = ite->data;
	if (lstat(namef, &a) < 0)
		return (1);
	if (ite && flag->mr && S_ISDIR(a.st_mode) &&
			ft_strcmp((char *)(ite->data + ite->sizeofdir + 1), ".") &&
			ft_strcmp((char *)(ite->data + ite->sizeofdir + 1), ".."))
		ft_slstadd(tmp, dir, ite->data + ite->sizeofdir + 1);
	if (flag->l)
		option_l(a, flag);
	if (ite)
		ft_putstr(ite->data + ite->sizeofdir + 1);
	else
		ft_putstr(namef);
	if (flag->l && S_ISLNK(a.st_mode))
		name(namef);
	write(1, "\n", 1);
	return (0);
}

void		fichiers(t_slist *ite, t_flag_ls *flag, char *dir, t_slist **rec)
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

int			parcourtrep(char *dir, t_flag_ls *flag, DIR *p_dir, t_slist **rec)
{
	struct dirent	*p_dirent;
	t_slist			*ite;
	t_slist			*tmp;

	tmp = NULL;
	ite = NULL;
	while ((p_dirent = readdir(p_dir)) != NULL)
	{
		if (ft_slstadd(&tmp, dir, p_dirent->d_name))
			ft_slstdel(&ite);
		if (!tmp)
			return (-1);
		if (!ite)
			ite = tmp;
	}
	closedir(p_dir);
	if (flag->l && (ite->next->next || flag->a))
		total(ite, flag);
	if (flag->t)
		ite = ft_slstsort(&ite, sorttime);
	if (flag->r)
		ite = ft_slstreverse(&ite);
	fichiers(ite, flag, dir, rec);
	ft_slstdel(&ite);
	return (0);
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
