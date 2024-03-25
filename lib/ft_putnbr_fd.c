/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:32:26 by cblonde           #+#    #+#             */
/*   Updated: 2023/11/03 11:13:51 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		num = n % 10 + '0';
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
			ft_putnbr_fd(n, fd);
		}
		else if (n > 9)
		{
			n /= 10;
			ft_putnbr_fd(n, fd);
			ft_putchar_fd(num, fd);
		}
		else
			ft_putchar_fd(num, fd);
	}
}
