/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:36:33 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/04 14:31:28 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_close_fds(t_parse *parse, size_t index)
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

static void	ft_handle_child(t_parse *parse, t_object *task, size_t i)
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
}

static void	ft_handle_parent(t_parse *parse, t_object *task, size_t i)
{
	close(task->pipe[1]);
	if (task->link == PIPE)
		close(parse->task[i - 1]->pipe[0]);
	if (!parse->task[i + 1] || parse->task[i + 1]->link != PIPE)
	{
		close(task->pipe[0]);
		waitpid(task->pid, &task->status, 0);
		ft_excmd_result(parse, task->status);
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
		ft_handle_child(parse, task, i);
		execve(task->cmd[0], task->cmd, parse->env);
		exit(0);
	}
	else
		ft_handle_parent(parse, task, i);
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
