/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:54:32 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/20 16:50:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_forks(t_parse *parse, size_t i, int status, size_t cur_sub)
{
	if (status == 1)
	{
		if (cur_sub != parse->task[i]->lvl)
			return ;
		if (i == 0)
			status = 0;
		else
			status = parse->task[i - 1]->status;
		ft_free_all(parse);
		exit(status);
	}
	if (status == 0 && cur_sub != 0
		&& parse->task[i] && parse->task[i]->close != 0)
	{
		status = parse->task[i]->status;
		ft_free_all(parse);
		exit(status);
	}
	if (status == 2 && i != 0 && cur_sub > parse->task[i]->lvl)
	{
		status = parse->task[i - 1]->status;
		ft_free_all(parse);
		exit(status);
	}
}

void	ft_handle_exit_parent(t_parse *parse, t_object *task)
{
	int	res;

	res = task->status;
	if (WIFEXITED(task->status))
	{
		res = WEXITSTATUS(task->status);
		ft_excmd_result(parse, res);
	}
	if (WIFSIGNALED(task->status))
	{
		res = 128 + WTERMSIG(task->status);
		ft_excmd_result(parse, res);
	}
	if (WIFSTOPPED(task->status))
	{
		res = WSTOPSIG(task->status);
		ft_excmd_result(parse, res);
	}
	if (WIFCONTINUED(task->status))
	{
		res = 0;
		ft_excmd_result(parse, 0);
	}
	task->status = res;
}

int	ft_and_sublvl(t_parse *parse, size_t *i)
{
	if (parse->sub_lvl[parse->task[*i - 1]->i_sub].status == -1)
		return (2);
	if (parse->sub_lvl[parse->task[*i - 1]->i_sub].status == 0)
	{
		if (ft_exec_while_pipe(parse, i))
			return (0);
		else
			return (3);
	}
	else
		return (1);
	return (2);
}

int	ft_or_sublvl(t_parse *parse, size_t *i)
{
	if (parse->sub_lvl[parse->task[*i - 1]->i_sub].status == -1)
		return (2);
	if (parse->sub_lvl[parse->task[*i - 1]->i_sub].status > 0)
	{
		if (ft_exec_while_pipe(parse, i))
			return (0);
		else
			return (3);
	}
	else
		return (1);
	return (2);
}

bool	ft_exec_while_pipe(t_parse *parse, size_t *i)
{
	if (!ft_exec(parse, parse->task[*i], *i))
		return (false);
	if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
		*i += 1;
	else
		return (true);
	while (parse->task[*i] && parse->task[*i]->link == PIPE
		&& parse->task[*i]->lvl == parse->task[*i - 1]->lvl)
	{
		ft_exec(parse, parse->task[*i], *i);
		if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
			*i += 1;
		else
			return (true);
	}
	return (true);
}
