/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/14 17:36:50 by tdumouli         ###   ########.fr       */
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

void		major(struct stat a)
{
	ft_putnbr(a.st_rdev / 16777216);
	ft_putstr(",  ");
	ft_putnbr(a.st_rdev % 16777216);
}

void		option_l(struct stat a)
{
	struct passwd		*pwd;
	struct group		*grp;
	char				*timer;

	print(a);
	write(1, "  ", 2);
	ft_putnbr(a.st_nlink);
	write(1, "  ", 2);
	if ((pwd = getpwuid(a.st_uid)))
		ft_putstr(pwd->pw_name);
	write(1, "  ", 2);
	if ((grp = getgrgid(a.st_gid)))
		ft_putstr(grp->gr_name);
	write(1, " ", 1);
	if (S_ISCHR(a.st_mode) || S_ISBLK(a.st_mode))
		major(a);
	else
		ft_putnbr(a.st_size);
	write(1, " ", 1);
	timer = ctime(&(a.st_mtime));
	write(1, timer + 4, 12);
	write(1, " ", 1);
}

int			total(t_slist *ite)
{
	int				stk;
	struct stat		a;

	stk = 0;
	ft_putstr("total ");
	while (ite)
	{
		if (lstat(ite->data, &a) < 0)
		{
			perror(" stat");
			return (1);
		}
		stk += a.st_blocks;
		ite = ite->next;
	}
	ft_putnbr(stk);
	write(1, "\n", 1);
	return (0);
}
