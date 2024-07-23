/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:50:00 by cblonde           #+#    #+#             */
/*   Updated: 2023/11/08 08:31:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (n >= 9223372036854775807)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		if (s1_len > s2_len)
			n = s1_len;
		else
			n = s2_len;
	}
	i = 0;
	while (*((unsigned char *)s1 + i) == *((unsigned char *)s2 + i)
		&& i + 1 < n && s1[i] && s2[i])
	{
		i++;
	}
	if (n == i)
		return (0);
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}
