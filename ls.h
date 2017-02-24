/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:30:55 by tdumouli          #+#    #+#             */
/*   Updated: 2017/02/23 16:40:16 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include <string.h>
# include <sys/stat.h>

typedef struct	s_flag_ls
{
	char			mr;
	char			r;
	char			a;
	char			l;
	char			t;
	size_t			max_lnk;
	size_t			max_uid;
	size_t			max_gid;
	size_t			max_siz;
}				t_flag_ls;

t_flag_ls		*init_flag_ls(void);
int				def(t_flag_ls *f, char *s);
int				ft_flag_lstdelone(t_flag_ls **adlst);

typedef struct	s_slist
{
	char			*data;
	int				sizeofdir;
	struct s_slist	*next;
}				t_slist;

int				ft_slstadd(t_slist **q, char *i, char *c);
void			ft_slstdelone(t_slist **q);
void			ft_slstdel(t_slist **q);
t_slist			*ft_slstreverse(t_slist **q);
void			*ft_slstsort(t_slist **adlst, int (*f)(void *, void *));
int				sorttime(void *t1, void *t2);

void			option_l(struct stat a, t_flag_ls *flag);
int				total(t_slist *ite, t_flag_ls *flag);
int				dossier(char *c, t_flag_ls *f);
int				fichier(char *dir, t_flag_ls *f, t_slist **t, t_slist *i);
void			recu(t_slist *rec, t_flag_ls *flag);
int				morething(char **av, t_flag_ls *flag, int i, int ac);
int				onething(char *av, t_flag_ls *flag);

#endif
