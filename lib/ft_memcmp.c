/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:05:49 by cblonde           #+#    #+#             */
/*   Updated: 2023/11/08 08:26:08 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*((unsigned char *)s1 + i) == *((unsigned char *)s2 + i)
		&& i + 1 < n)
	{
		i++;
	}
	if (n == i)
		return (0);
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}
