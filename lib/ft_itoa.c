/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 08:57:13 by cblonde           #+#    #+#             */
/*   Updated: 2023/11/06 10:37:56 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(long int nbr)
{
	size_t	i;

	i = 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	ft_implement_str(char *str, long int nbr, size_t nlen)
{
	while (nbr)
	{
		str[nlen - 1] = nbr % 10 + '0';
		nbr /= 10;
		nlen--;
	}
}

char	*ft_itoa(int n)
{
	size_t		sign;
	size_t		nlen;
	long int	nbr;
	char		*str;

	sign = 0;
	nbr = n;
	if (n < 0)
	{
		sign = 1;
		nbr *= -1;
	}
	nlen = ft_nbrlen(nbr) + sign;
	if (n == 0)
		nlen++;
	str = ft_calloc(nlen + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (sign == 1)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	ft_implement_str(str, nbr, nlen);
	return (str);
}
