/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:36:33 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/10 12:06:45 by cblonde          ###   ########.fr       */
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
		if (parse->task[i]->pipe[0] >= 0)
			close(parse->task[i]->pipe[0]);
		if (parse->task[i]->pipe[1] >= 0)
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
	{
		if (task->outfile != -1)
			dup2(parse->redirect[task->outfile]->fd, 1);
		else
			dup2(task->pipe[1], 1);
	}
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
		if (WIFEXITED(task->status))
			ft_excmd_result(parse, WEXITSTATUS(task->status));
		if (WIFSIGNALED(task->status))
			ft_excmd_result(parse, 128 + WTERMSIG(task->status));
		if (WIFSTOPPED(task->status))
			ft_excmd_result(parse, WSTOPSIG(task->status));
		if (WIFCONTINUED(task->status))
		{
			ft_excmd_result(parse, 0);
		}
	}
}

static void	ft_handle_status(t_parse *parse, t_object *task)
{
	int	status;
	DIR	*dir;

	status = 0;
	dir = NULL;
	if (!task->cmd || !task->cmd[0])
		exit(127);
	if (access(task->cmd[0], F_OK) == -1)
		status = 127;
	else if (access(task->cmd[0], X_OK) == -1)
		status = 126;
	if (access(task->cmd[0], X_OK) == -1
		&& task->cmd[0][0] != '.' && task->cmd[0][0] != '/')
		status = 127;
	dir = opendir(task->cmd[0]);
	if (dir)
		status = 127;
	if (dir && (task->cmd[0][0] == '.' || task->cmd[0][0] == '/'))
		status = 126;
	if (dir)
		closedir(dir);
	ft_handle_error_exec(task->cmd[0]);
	ft_free_all(parse);
	ft_close_std_fd();
	exit(status);
}

void	ft_exec(t_parse *parse, t_object *task, size_t i)
{
	if (!ft_parse_befor_exec(parse, i))
		return ;
	pipe(task->pipe);
	task->pid = fork();
	if (task->pid < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		return ;
	}
	if (task->pid == 0)
	{
		handle_bad_fd(parse, task, i);
		ft_handle_child(parse, task, i);
		if (task->builtin == NO_BUILTIN)
			if (execve(task->cmd[0], task->cmd, parse->env) == -1)
				ft_handle_status(parse, task);
		ft_exec_builtin(parse, task);
		ft_close_std_fd();
		ft_free_all(parse);
		exit(0);
	}
	else
		ft_handle_parent(parse, task, i);
}
