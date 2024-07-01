/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:21:31 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/01 13:31:41 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_fork(t_parse *parse, size_t i)
{
	if (parse->task[i]->builtin != NO_BUILTIN)
	{
		if (parse->task[i]->builtin == ECHO
			|| parse->task[i]->builtin == ENV
			|| (parse->task[i]->builtin == EXPORT && !parse->task[i]->cmd[1]))
			return (true);
		if (parse->task[i + 1] && parse->task[i + 1]->link == PIPE)
			return (true);
		else
			return (false);
	}
	return (true);
}

void	ft_exec_builtin(t_parse *parse, t_object *task)
{
	if (task->builtin == ECHO)
		ft_exec_echo(parse, task);
	if (task->builtin == CD)
		ft_cd(parse, task, task->cmd[1]);
	if (task->builtin == PWD)
		ft_pwd(parse);
	if (task->builtin == EXPORT)
		ft_exec_export(parse, task);
	if (task->builtin == UNSET)
		ft_exec_unset(parse, task);
	if (task->builtin == ENV)
		ft_env(parse);
	if (task->builtin == EXIT)
		ft_exit(parse, task);
}
