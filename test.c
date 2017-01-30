/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/01/30 05:53:31 by tdumouli         ###   ########.fr       */
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

#include<stdio.h>

int			main(int ac, char *av[])
{
	if (ac < 2)
		affiche(".");
	else
		affiche(av[1]);
	return (0);
}

static void	print(struct stat filestat)
{
	if (S_ISREG(filestat.st_mode))
		write(1, "-", 1);
	else if (S_ISDIR(filestat.st_mode))
		write(1, "d", 1);
	else if (S_ISCHR(filestat.st_mode))
		write(1, "c", 1);
	else if (S_ISLNK(filestat.st_mode))
		write(1, "l", 1);
	else if (S_ISSOCK(filestat.st_mode))
		write(1, "s", 1);
	else if (S_ISFIFO(filestat.st_mode))
		write(1, "p", 1);
	else if (S_ISBLK(filestat.st_mode))
		write(1, "b", 1);
	else
		write(1, "?", 1);
	write(1, (filestat.st_mode & S_IRUSR) ? "r" : "-", 1);
	write(1, (filestat.st_mode & S_IWUSR) ? "w" : "-", 1);
	write(1, (filestat.st_mode & S_IXUSR) ? "x" : "-", 1);
	write(1, (filestat.st_mode & S_IRGRP) ? "r" : "-", 1);
	write(1, (filestat.st_mode & S_IWGRP) ? "w" : "-", 1);
	write(1, (filestat.st_mode & S_IXGRP) ? "x" : "-", 1);
	write(1, (filestat.st_mode & S_IROTH) ? "r" : "-", 1);
	write(1, (filestat.st_mode & S_IWOTH) ? "w" : "-", 1);
	write(1, (filestat.st_mode & S_IXOTH) ? "x" : "-", 1);
}

static void	recu(t_slist *rec)
{
	while (rec)
	{
		write(1, "\n", 1);
		ft_putstr(((rec->data)));
		write(1, ":\n", 2);
		affiche(rec->data);
		rec = rec->next;
	}
}

void major(struct stat a)
{
	ft_putstr(ft_itoabase(a.st_rdev));
}

void		option_l(struct stat a)
{
	struct stat			statbuf;
	struct passwd		*pwd;
	struct group		*grp;
	char				*timer;

	print(a);
	write(1, "  ", 2);
	ft_putnbr(a.st_nlink);
	write(1, " ", 1);
	if ((pwd = getpwuid(a.st_uid)))
		ft_putstr(pwd->pw_name);
	write(1, "  ", 2);
	if ((grp = getgrgid(a.st_gid)))
		ft_putstr(grp->gr_name);
	write(1, " ", 1);
	if (a.st_mode & S_IFCHR || a.st_mode & S_IFBLK)
		major(a);
	else
		ft_putnbr(a.st_size);
	write(1, " ", 1);
	timer = ctime(&(a.st_mtime));
	write(1, timer + 4, 12);
	write(1, " ", 1);
}

void		total(t_slist *ite)
{
	int				stk;
	struct stat		a;

	stk = 0;
	ft_putstr("total ");
	while (ite)
	{
		if (stat(ite->data, &a) < 0)
			perror(" stat");
		stk += a.st_blocks;
		ite = ite->next;
	}
	ft_putnbr(stk);
	write(1, "\n", 1);
}

int			affiche(char *dir)
{
	struct dirent	*p_dirent;
	DIR				*p_dir;
	struct stat		a;
	char			*err;
	t_slist			*rec = NULL;
	t_slist			*ite = NULL;
	t_slist			*tmp = NULL;

	if (!(p_dir = opendir(dir)))
	{
		err = ft_strjoin("ft_ls: ", ft_strrchr(dir, '/') + 1);
		perror(err);
		return (-1);
	}
	while ((p_dirent = readdir(p_dir)) != NULL)
	{
		ft_slstadd(&tmp, dir, p_dirent->d_name);
		if (!ite)
			ite = tmp;
	}
	ite = ite->next->next;
	if (ite)
		total(ite);
	ft_slstreverse(&ite);
	tmp = NULL;
	while (ite)
	{
		if (stat(ite->data, &a) < 0)
		{
			perror(" stat");
			return (-1);
		}
		if (S_ISDIR(a.st_mode))// && *(char *)(ite->data + ite->sizeofdir + 1) != '.')
		{
			ft_slstadd(&tmp, dir, ite->data + ite->sizeofdir + 1);
			if (!rec)
				rec = tmp;
		}
		option_l(a);
		ft_putstr(ite->data + ite->sizeofdir + 1);
		write(1, "\n", 1);
		ite = ite->next;
	}
	ft_slstdel(&ite);
	if (closedir(p_dir))
		return (-1);
	recu(rec);
	return (0);
}
