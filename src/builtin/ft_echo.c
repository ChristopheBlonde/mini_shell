/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/05 09:31:12 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_echo(t_parse *parse, t_object *task)
{
	int		i;
	int		option;
	char	*str;

	i = 1;
	option = 0;
	if (task->cmd[1] && task->cmd[1][0] != '\0'
		&& !ft_strncmp(task->cmd[1], "-n", ft_strlen(task->cmd[1])))
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
}

void	ft_exec_echo(t_parse *parse, t_object *task)
{
	if (task->builtin != ECHO)
		return ;
	if (!task->cmd)
		return ;
	ft_echo(parse, task);
}
