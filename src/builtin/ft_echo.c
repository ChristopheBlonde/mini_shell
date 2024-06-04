/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/04 16:19:07 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_echo(t_parse *parse, t_object *task, int fd)
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
		ft_putstr_fd(str, fd);
		if (task->cmd[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", fd);
	ft_excmd_result(parse, 0);
}

void	ft_exec_echo(t_parse *parse, t_object *task, int index)
{
	int	fd;

	fd = 1;
	if (task->builtin != ECHO)
		return ;
	if (!task->cmd)
		return ;
	if ((parse->task[index + 1] && parse->task[index + 1]->link == PIPE)
		|| task->outfile != -1)
		fd = task->pipe[0];
	ft_echo(parse, task, fd);
}
