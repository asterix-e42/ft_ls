/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 07:25:19 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/20 09:10:55 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/stat.h>

#include<stdio.h>

int main (int ac, char *av[]) {
	int len;
	struct dirent *pDirent;
	DIR *pDir;
	struct stat a;

	if (ac < 2) {
		pDir = opendir (".");
	}
	else
		pDir = opendir (av[1]);
	if (pDir == NULL) {
		ft_erreur("Cannot open directory");
		return 1;
	}

	while ((pDirent = readdir(pDir)) != NULL) {
		stat(pDirent->d_name, &a);
		//printf("%u\n", a.st_uid);
		ft_putstr(pDirent->d_name);
		write(1, "\n", 1);
	}
	closedir (pDir);
	return 0;
}
