/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:24:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/18 11:41:01 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_befor_exec(t_parse *parse, size_t i)
{
	if (!ft_exec_redirect(parse, i))
		return (false);
	ft_handle_env(parse, i);
	ft_wildcard(parse, i);
	if (!parse->task[i]->cmd
		|| (parse->task[i]->cmd && !parse->task[i]->cmd[0]))
		return (false);
	if (parse->task[i]->cmd[0] && parse->task[i]->cmd[0][0] == '\0')
	{
		ft_putendl_fd("minishell: Command '' not found", 2);
		ft_excmd_result(parse, 127);
		return (false);
	}
	ft_get_path(parse);
	if (parse->task[i]->infile != -1)
		ft_handle_heredoc_var(parse, parse->redirect[parse->task[i]->infile]);
	ft_check_builtin(parse->task[i],
		parse->task[i]->cmd[0], ft_strlen(parse->task[i]->cmd[0]));
	return (true);
}

static void	ft_skip_task(t_parse *parse, size_t *cur_sub, size_t *i)
{
	size_t	tmp;

	tmp = *i;
	while (parse->task[*i] && parse->task[*i + 1]
		&& parse->task[*i]->lvl > *cur_sub)
	{
		if (*i != tmp && parse->task[*i]->lvl == *cur_sub + 1
			&& parse->sub_lvl[parse->task[*i]->i_sub].befor + 1 == (int)*i)
			break ;
		(*i)++;
	}
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
			waitpid(*sub_lvl, &parse->task[*i]->status, 0);
	}
	ft_skip_task(parse, cur_sub, i);
	ft_exit_forks(parse, *i, 2, *cur_sub);
	if (parse->task[*i] && parse->task[*i]->cmd[0]
		&& parse->task[*i]->cmd[0][0] == '\0')
		return (false);
	return (true);
}

bool	ft_exec_cmd(t_parse *parse, size_t *i, size_t cur_sub)
{
	if (!ft_parse_befor_exec(parse, *i))
		return (true);
	if (!ft_is_fork(parse, *i))
		ft_exec_builtin(parse, parse->task[(*i)++]);
	else
	{
		if (parse->task[*i] && parse->task[*i]->cmd)
		{
			ft_exec_pipe(parse, i);
			if (!ft_exec_or(parse, i))
				return (false);
			if (!ft_exec_and(parse, i))
				return (false);
		}
		ft_exit_forks(parse, *i, 0, cur_sub);
		(*i)++;
	}
	return (true);
}

void	ft_exec_pipe(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link != OR
		&& parse->task[*i]->link != AND)
	{
		ft_exec(parse, parse->task[*i], *i);
		if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
			*i += 1;
		else
			return ;
		while (parse->task[*i] && parse->task[*i]->link == PIPE
			&& parse->task[*i]->lvl == parse->task[*i - 1]->lvl)
		{
			ft_exec(parse, parse->task[*i], *i);
			if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
				*i += 1;
			else
				return ;
		}
	}
}
