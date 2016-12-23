/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:30:55 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/22 20:06:29 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include <string.h>

typedef struct	s_slist
{
	void			*data;
	struct s_slist	*next;
}				t_slist;

int 	ft_slstadd(t_slist **q, const void *i, const void *c);
void	ft_slstdelone(t_slist **q);
void	ft_slstdel(t_slist **q);
int		affiche(char *c);

#endif
