/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/14 16:50:30 by tdumouli         ###   ########.fr       */
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


static void	permission(mode_t m)
{
	ft_putchar(m & S_IRUSR ? 'r' : '-');
	ft_putchar(m & S_IWUSR ? 'w' : '-');
	if (m & S_ISUID)
		ft_putchar(m & S_IXUSR ? 's' : 'S');
	else
		ft_putchar(m & S_IXUSR ? 'x' : '-');
	ft_putchar(m & S_IRGRP ? 'r' : '-');
	ft_putchar(m & S_IWGRP ? 'w' : '-');
	if (m & S_ISGID)
		ft_putchar(m & S_IXGRP ? 's' : 'S');
	else
		ft_putchar(m & S_IXGRP ? 'x' : '-');
	ft_putchar(m & S_IROTH ? 'r' : '-');
	ft_putchar(m & S_IWOTH ? 'w' : '-');
	if (m & S_ISVTX)
		ft_putchar(m & S_IXOTH ? 't' : 'T');
	else
		ft_putchar(m & S_IXOTH ? 'x' : '-');
}

static void	print(struct stat filestat)
{
	if (S_ISDIR(filestat.st_mode))
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
	else if (S_ISREG(filestat.st_mode))
		write(1, "-", 1);
	else
		write(1, "?", 1);
	permission(filestat.st_mode);
}

void		ft_major(struct stat a)
{
	ft_putnbr(a.st_rdev / 16777216);
	ft_putstr(",\t");
	ft_putnbr(a.st_rdev % 16777216);
}

void		option_l(struct stat a, t_flag_ls *flag)
{
	struct passwd		*pwd;
	struct group		*grp;
	char				*timer;

	print(a);
	write(1, "            ", 2 + flag->max_lnk - ft_intlen(a.st_nlink));
	ft_putnbr(a.st_nlink);
	write(1, " ", 1);
	pwd = getpwuid(a.st_uid);
	ft_putstr(pwd->pw_name);
	write(1, "            ", 2 + flag->max_uid - ft_strlen(pwd->pw_name));
	grp = getgrgid(a.st_gid);
	ft_putstr(grp->gr_name);
	write(1, "             ", 2 + flag->max_gid - ft_strlen(grp->gr_name));
	write(1, "             ", flag->max_siz - ft_intlen(a.st_size));
	if (S_ISCHR(a.st_mode) || S_ISBLK(a.st_mode))
		ft_major(a);
	else
		ft_putnbr(a.st_size);
	write(1, " ", 1);
	timer = ctime(&(a.st_mtime));
	write(1, timer + 4, 12);
	write(1, " ", 1);
}

void		max(struct stat a, t_flag_ls *flag)
{
	struct passwd		*pwd;
	struct group		*grp;

	flag->max_lnk = (ft_intlen(a.st_nlink) > flag->max_lnk) ?
		ft_intlen(a.st_nlink) : flag->max_lnk;
	if ((pwd = getpwuid(a.st_uid)))
		flag->max_uid = (ft_strlen(pwd->pw_name) > flag->max_uid) ?
			ft_strlen(pwd->pw_name) : flag->max_uid;
	if ((grp = getgrgid(a.st_gid)))
		flag->max_gid = (ft_strlen(grp->gr_name) > flag->max_gid) ?
			ft_strlen(grp->gr_name) : flag->max_gid;
	flag->max_siz = (ft_intlen(a.st_size) > flag->max_siz) ?
		ft_intlen(a.st_size) : flag->max_siz;
}

int			total(t_slist *ite, t_flag_ls *flag)
{
	int				stk;
	struct stat		a;

	stk = 0;
	ft_putstr("total ");
	flag->max_lnk = 0;
	flag->max_uid = 0;
	flag->max_gid = 0;
	flag->max_siz = 0;
	while (ite)
	{
		if (stat(ite->data, &a) < 0)
		{
			ft_putnbr(stk);
			write(1, "\n", 1);
			return (1);
		}
		max(a, flag);
		stk += a.st_blocks;
		ite = ite->next;
	}
	ft_putnbr(stk);
	write(1, "\n", 1);
	return (0);
}
