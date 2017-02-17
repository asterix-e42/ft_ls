/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 18:24:15 by tdumouli          #+#    #+#             */
/*   Updated: 2017/01/29 18:29:57 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strsjoin(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	if (!s1 || !s2 || !s3)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = ft_strlen(s3);
	if (!(ret = (char *)malloc(sizeof(char) * (i + j + k + 1))))
		return (NULL);
	*(ret + i + j + k) = '\0';
	while (k--)
		*(ret + i + j + k) = *(s3 + k);
	while (j--)
		*(ret + i + j) = *(s2 + j);
	while (i--)
		*(ret + i) = *(s1 + i);
	return (ret);
}
