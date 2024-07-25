/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:12:11 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/25 11:02:57 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol_exit(char *str)
{
	long long	nbr;
	int			sign;
	size_t		i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (nbr == 922337203685477580 && str[i] == '8' && sign == -1)
			return (0);
		if (nbr == 922337203685477580 && str[i] == '8')
			return (-1);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

int	ft_usage(char **argv)
{
	if (argv[1])
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is not option !\n", 2);
	}
	ft_putendl_fd("\033[1;34mUsage: [ minishell ]\033[m", 2);
	return (1);
}
