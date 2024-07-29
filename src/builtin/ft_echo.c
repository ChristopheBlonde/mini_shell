/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/29 10:14:27 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	ft_check_option(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] != '-')
		return (false);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	if (i == 1)
		return (false);
	return (true);
}

static int	ft_echo(t_parse *parse, t_object *task)
{
	int		i;
	int		option;
	char	*str;

	i = 1;
	option = 0;
	while (task->cmd[i] && task->cmd[i][0] != '\0'
		&& ft_check_option(task->cmd[i]))
	{
		option = 1;
		i++;
	}
	while (task->cmd[i])
	{
		str = task->cmd[i];
		ft_putstr_fd(str, 1);
		if (task->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	ft_excmd_result(parse, 0);
	return (0);
}

void	ft_exec_echo(t_parse *parse, t_object *task)
{
	if (task->builtin != ECHO)
		return ;
	if (!task->cmd)
		return ;
	ft_echo(parse, task);
}
