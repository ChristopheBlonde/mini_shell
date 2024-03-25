/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:59:27 by cblonde           #+#    #+#             */
/*   Updated: 2023/10/31 14:43:48 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			*((unsigned char *)dest + i - 1) = *((unsigned char *)src + i - 1);
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
