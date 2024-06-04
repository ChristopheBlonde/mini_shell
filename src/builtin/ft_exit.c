/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:18:42 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/04 09:39:38 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_is_number(char *str)
{
	size_t		i;
	long long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13)
		|| str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9')
			&& str[i] != '-' && str[i] != '+')
			return (false);
		nbr = nbr * 10 + (str[i] - '0');
		ft_putstr_fd("\e[0;36m", 2);
		ft_putnbr_fd(nbr, 2);
		ft_putstr_fd("\e[0;36m\n", 2);
		if ((nbr > 922337203685477580 && str[i + 1])
				|| (nbr < -922337203685477580 && str[i + 1])
				|| (nbr == 922337203685477580 && str[i] > '7')
				|| (nbr == -922337203685477580 && str[i] > '8'))
			return (false);
		i++;
	}
	return (true);
}

/*long long	ft_atol(char *str)
{
	long long	nbr;
	int			sign;
	size_t		i;

	sign = 1;
	nbr = 0;
	i = 0;
	//9223372036854775807
	while (str[i])
	{
	}
}*/

int	ft_exit(t_parse *parse, t_object *task)
{
	long long	nbr;

	nbr = 0;
	if (task->cmd && task->cmd[0] && task->cmd[1] && task->cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ft_excmd_result(parse, 1);
		return (1);
	}
	if (task->cmd[0] && task->cmd[1] && !ft_is_number(task->cmd[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(task->cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	ft_free_all(parse);
	exit(nbr);
	return (0);
}
