/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahbibe <bahbibe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 03:00:42 by bahbibe           #+#    #+#             */
/*   Updated: 2022/10/20 01:11:55 by bahbibe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	size_t	i;

	a = (char) c;
	i = 0 ;
	while (i <= ft_strlen(s))
	{
		if (s[i] == a)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
