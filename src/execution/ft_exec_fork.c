/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:24:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/23 07:44:19 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skip_task(t_parse *parse, size_t *cur_sub, size_t *i, int n)
{
	size_t	tmp;

	tmp = *i;
	while (parse->task[*i] && parse->task[*i + 1]
		&& parse->task[*i]->lvl > *cur_sub)
	{
		if (n == 0)
		{
			if (*i != tmp && parse->task[*i]->lvl == *cur_sub + 1
				&& (parse->sub_lvl[parse->task[*i]->i_sub].after - 1)
				== (int)*i)
				break ;
		}
		else
		{
			if (*i != tmp && parse->task[*i]->open != 0
				&& (parse->sub_lvl[parse->task[*i]->i_sub].befor + 1)
				== (int)*i)
				break ;
		}
		(*i)++;
	}
}

static void	ft_handle_subparent(t_parse *parse, pid_t *sub_lvl,
	size_t *cur_sub, size_t *i)
{
	ft_skip_task(parse, cur_sub, i, 0);
	waitpid(*sub_lvl, &parse->task[*i]->status, 0);
	ft_handle_exit_parent(parse, parse->task[*i]);
	parse->sub_lvl[parse->task[*i]->i_sub].status
		= parse->task[*i]->status;
}

bool	ft_is_subexec(t_parse *parse, pid_t *sub_lvl,
			size_t *cur_sub, size_t *i)
{
	ft_exit_forks(parse, *i, 2, *cur_sub);
	if (parse->task[*i]->lvl > *cur_sub)
	{
		ft_exit_forks(parse, *i, 1, *cur_sub);
		*sub_lvl = fork();
		if (*sub_lvl < 0)
			perror("minishell");
		else if (*sub_lvl == 0)
		{
			(*cur_sub)++;
			if (*cur_sub < parse->task[*i]->lvl)
				return (true);
		}
		else
			ft_handle_subparent(parse, sub_lvl, cur_sub, i);
	}
	ft_skip_task(parse, cur_sub, i, 1);
	ft_exit_forks(parse, *i, 2, *cur_sub);
	if (parse->task[*i] && parse->task[*i]->cmd[0]
		&& parse->task[*i]->cmd[0][0] == '\0')
		return (false);
	return (true);
}

bool	ft_exec_cmd(t_parse *parse, size_t *i, size_t cur_sub)
{
	if (!ft_is_fork(parse, *i))
	{
		if (!parse->task[*i]->parsed)
			if (!ft_parse_befor_exec(parse, *i))
				return (true);
		parse->task[*i]->parsed = false;
		ft_exec_builtin(parse, parse->task[(*i)++]);
	}
	else
	{
		if (parse->task[*i] && parse->task[*i]->cmd)
		{
			if (!ft_exec_pipe(parse, i))
				parse->task[*i]->parsed = true;
			if (!parse->task[*i]->parsed && !ft_exec_or(parse, i))
				return (false);
			if (!parse->task[*i]->parsed && !ft_exec_and(parse, i))
				return (false);
		}
		ft_exit_forks(parse, *i, 0, cur_sub);
		if (!parse->task[*i]->parsed)
			(*i)++;
	}
	return (true);
}

bool	ft_exec_pipe(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link != OR
		&& parse->task[*i]->link != AND)
	{
		if (!ft_exec_while_pipe(parse, i))
			return (false);
	}
	return (true);
}
