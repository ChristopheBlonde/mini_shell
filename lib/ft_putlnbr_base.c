/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:46:01 by cblonde           #+#    #+#             */
/*   Updated: 2023/12/11 10:53:57 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_nbrlen(long int n, long int len_base)
{
	long int	len;

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

static int	ft_charcmp(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			return (0);
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

size_t	ft_putlnbr_base(long int nbr, char *base)
{
	long int	base_len;
	long int	nb;
	int			num;
	size_t		len;

	nb = nbr;
	base_len = ft_strlen(base);
	len = ft_nbrlen(nb, base_len);
	if (base_len > 1 && ft_charcmp(base) == 1)
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb = -nb;
		}
		num = nb % base_len;
		if (nb >= base_len)
		{
			nb = nb / base_len;
			ft_putlnbr_base(nb, base);
		}
		write(1, &base[num], 1);
	}
	return (len);
}
