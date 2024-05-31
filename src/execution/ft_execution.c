/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:38:45 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/31 14:17:39 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_builtin(t_parse *parse, t_object *task)
{
	if (task->builtin == ECHO)
		ft_exec_echo(parse, task);
	if (task->builtin == CD)
		ft_cd(parse, task->cmd[1]);
	if (task->builtin == PWD)
		ft_pwd(parse);
	if (task->builtin == EXPORT)
		ft_exec_export(parse, task);
	if (task->builtin == UNSET)
		ft_exec_unset(parse, task);
	if (task->builtin == ENV)
		ft_env(parse);
	if (task->builtin == EXIT)
	{
		ft_free_all(parse);
		exit(0);
	}
}

void	ft_close_fds(t_parse *parse, size_t index)
{
	size_t	i;

	i = 0;
	while (parse->redirect && parse->redirect[i])
	{
		if (parse->redirect[i]->fd != -1)
		{
			close(parse->redirect[i]->fd);
		}
		i++;
	}
	i = 0;
	while (i <= index)
	{
		if (parse->task[i]->pipe[0] > 0)
			close(parse->task[i]->pipe[0]);
		if (parse->task[i]->pipe[1] > 0)
			close(parse->task[i]->pipe[1]);
		i++;
	}
}

void	ft_exec(t_parse *parse, t_object *task, size_t i)
{
	pipe(task->pipe);
	task->pid = fork();
	if (task->pid < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (task->pid == 0)
	{
		if (task->infile != -1)
			dup2(parse->redirect[task->infile]->fd, 0);
		else if (task->link == PIPE)
			dup2(parse->task[i - 1]->pipe[0], 0);
		if (!parse->task[i + 1] || parse->task[i + 1]->link != PIPE)
		{
			if (task->outfile != -1)
				dup2(parse->redirect[task->outfile]->fd, 1);
		}
		else
			dup2(task->pipe[1], 1);
		ft_close_fds(parse, i);
		execve(task->cmd[0], task->cmd, parse->env);
		exit(0);
	}
	else
	{
		close(task->pipe[1]);
		if (task->link == PIPE)
			close(parse->task[i - 1]->pipe[0]);
		if (!parse->task[i + 1] || parse->task[i + 1]->link != PIPE)
		{
			close(task->pipe[0]);
			waitpid(task->pid, &task->status, 0);
		}
	}
}

bool	ft_execution(t_parse *parse)
{
	size_t	i;

	i = 0;
	ft_exec_redirect(parse);
	ft_get_path(parse);
	while (parse->task && parse->task[i])
	{
		if (parse->task[i]->builtin != NO_BUILTIN)
			ft_exec_builtin(parse, parse->task[i]);
		else
		{
			if (parse->task[i]->cmd && parse->task[i]->cmd[0])
				ft_exec(parse, parse->task[i], i);
		}
		i++;
	}
	i = 0;
	while (parse->task[i])
	{
		waitpid(parse->task[i]->pid, &parse->task[i]->status, 0);
		i++;
	}
	return (true);
}
