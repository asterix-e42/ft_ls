/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 06:42:48 by tdumouli          #+#    #+#             */
/*   Updated: 2016/12/26 17:12:01 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*parcourt;

	if ((*alst) == NULL)
		(*alst) = new;
	else
	{
		parcourt = *alst;
		while ((parcourt->next))
			parcourt = parcourt->next;
		parcourt->next = new;
	}
}
