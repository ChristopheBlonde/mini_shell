/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:18:42 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/25 10:22:37 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skip_until(char *str, int *s, size_t *i)
{
	while (str[*i] == 32 || (9 <= str[*i] && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-')
		*s *= -1;
	if (str[*i] == '-' || str[*i] == '+')
		(*i)++;
}

static bool	ft_is_number(char *str)
{
	size_t		i;
	long long	n;
	int			s;
	long long	max;

	i = 0;
	n = 0;
	s = 1;
	max = 922337203685477580;
	ft_skip_until(str, &s, &i);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (false);
		else
			n = n * 10 + (str[i] - '0');
		if ((n > max && str[i + 1]) || (n * s < -(max) && str[i + 1])
			|| (n * s == max && str[i] && str[i + 1] > '7')
			|| (n * s == -(max) && str[i] && str[i + 1] > '8'))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_get_exit_code(long long *nbr)
{
	if (*nbr < 0)
		*nbr = 256 + (*nbr % 256);
	else
		*nbr = *nbr % 256;
}

static void	ft_display_error(t_object *task)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(task->cmd[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(t_parse *parse, t_object *task)
{
	long long	nbr;

	nbr = 0;
	if (task->cmd[1] && !ft_is_number(task->cmd[1]))
	{
		ft_display_error(task);
		ft_free_all(parse);
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
