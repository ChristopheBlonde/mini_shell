/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:18:42 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 10:20:17 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_number(char *str)
{
	size_t		i;
	long long	n;
	int			s;

	i = 0;
	n = 0;
	s = 1;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9') && str[i] != '-' && str[i] != '+')
			return (false);
		if (str[i] == '-')
			s *= -1;
		else
			n = n * 10 + (str[i] - '0');
		if ((n > 922337203685477580 && str[i + 1])
			|| (n * s < -922337203685477580 && str[i + 1])
			|| (n * s == 922337203685477580 && str[i] && str[i + 1] > '7')
			|| (n * s == -922337203685477580 && str[i] && str[i + 1] > '8'))
			return (false);
		i++;
	}
	return (true);
}

static long long	ft_atol_exit(char *str)
{
	long long	nbr;
	int			sign;
	size_t		i;

	sign = 1;
	nbr = 0;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (str[i] == '-')
			sign = -1;
		while (str[i] == '-' || str[i] == '+')
			i++;
		if (nbr == 922337203685477580 && str[i] == '8')
			return (-1);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

static void	ft_get_exit_code(long long *nbr)
{
	if (*nbr < 0)
		*nbr = 256 + (*nbr % 256);
	else
		*nbr = *nbr % 256;
}

int	ft_exit(t_parse *parse, t_object *task)
{
	long long	nbr;

	nbr = 0;
	if (task->cmd[1] && !ft_is_number(task->cmd[1]))
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(task->cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (task->cmd[1] && task->cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_excmd_result(parse, 1);
		return (1);
	}
	if (task->cmd[1])
		nbr = ft_atol_exit(task->cmd[1]);
	ft_get_exit_code(&nbr);
	if (nbr == 0 && !task->cmd[1])
		nbr = ft_atoi(ft_getenv(parse, "?"));
	ft_free_all(parse);
	exit(nbr);
	return (0);
}
