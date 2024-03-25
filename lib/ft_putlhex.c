/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:14:17 by cblonde           #+#    #+#             */
/*   Updated: 2023/12/11 10:48:35 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(unsigned long int n, unsigned long int len_base)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= len_base;
		len++;
	}
	return (len);
}

size_t	ft_putlhex(unsigned long int nbr, char *base)
{
	unsigned long int	base_len;
	unsigned long int	nb;
	int					num;
	size_t				len;

	nb = nbr;
	base_len = ft_strlen(base);
	len = ft_nbrlen(nb, base_len);
	num = nb % base_len;
	if (nb >= (unsigned long int)base_len)
	{
		nb = nb / base_len;
		ft_putlnbr_base(nb, base);
	}
	write(1, &base[num], 1);
	return (len);
}
