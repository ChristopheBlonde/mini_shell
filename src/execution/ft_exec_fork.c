/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:24:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/05 15:55:39 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_befor_exec(t_parse *parse, size_t i)
{
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
	{
		ft_handle_heredoc_var(parse, parse->redirect[parse->task[i]->infile]);
		parse->redirect[parse->task[i]->infile]->fd
			= open(parse->redirect[parse->task[i]->infile]->file, O_RDONLY);
	}
	return (true);
}

bool	ft_is_subexec(t_parse *parse, pid_t *sub_lvl,
			size_t *cur_sub, size_t *i)
{
	if (*cur_sub != 0 && (!parse->task[*i + 1]
			|| parse->task[*i]->lvl < *cur_sub))
		exit(parse->task[*i - 1]->status);
	if (*cur_sub < parse->task[*i]->lvl)
	{
		*sub_lvl = fork();
		if (*sub_lvl < 0)
			perror("minishell");
		else if (*sub_lvl == 0)
		{
			ft_putendl_fd("in fork", 1);
			*cur_sub = parse->task[*i]->lvl;
		}
		else
			waitpid(*sub_lvl, &parse->task[*i]->status, 0);
	}
	while (parse->task[*i] && parse->task[*i]->lvl > *cur_sub && parse->task[*i + 1])
		(*i)++;
	if (*cur_sub != 0 && (!parse->task[*i + 1]
			|| parse->task[*i]->lvl < *cur_sub))
		exit(parse->task[*i - 1]->status);
	if (parse->task[*i] && parse->task[*i]->cmd[0]
		&& parse->task[*i]->cmd[0][0] == '\0')
		return (false);
	return (true);
}

bool	ft_exec_cmd(t_parse *parse, size_t *i)
{
	if (!ft_is_fork(parse, *i))
	{
		ft_parse_befor_exec(parse, *i);
		ft_exec_builtin(parse, parse->task[(*i)++]);
	}
	else
	{
		if (parse->task[*i] && parse->task[*i]->cmd && parse->task[*i]->cmd[0])
		{
			ft_exec_pipe(parse, i);
			if (!ft_exec_or(parse, i))
				return (false);
			if (!ft_exec_and(parse, i))
				return (false);
		}
		(*i)++;
	}
	return (true);
}
