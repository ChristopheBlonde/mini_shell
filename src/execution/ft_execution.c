/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:38:45 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/25 10:19:57 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_pipe(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link != OR
		&& parse->task[*i]->link != AND)
	{
		ft_exec(parse, parse->task[*i], *i);
		if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
			*i += 1;
		else
			return ;
		while (parse->task[*i] && parse->task[*i]->link == PIPE)
		{
			ft_exec(parse, parse->task[*i], *i);
			if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
				*i += 1;
			else
				return ;
		}
	}
}

static bool	ft_exec_or(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link == OR)
	{
		if (parse->task[*i - 1]->status > 0)
		{
			ft_exec(parse, parse->task[*i], *i);
			if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
				*i += 1;
			else
				return (true);
			while (parse->task[*i] && parse->task[*i]->link == PIPE)
			{
				ft_exec(parse, parse->task[*i], *i);
				if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
					*i += 1;
				else
					return (true);
			}
		}
		else
			return (false);
	}
	return (true);
}

static bool	ft_exec_and(t_parse *parse, size_t *i)
{
	if (parse->task[*i] && parse->task[*i]->link == AND)
	{
		if (parse->task[*i - 1]->status == 0)
		{
			ft_exec(parse, parse->task[*i], *i);
			if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
				*i += 1;
			else
				return (true);
			while (parse->task[*i] && parse->task[*i]->link == PIPE)
			{
				ft_exec(parse, parse->task[*i], *i);
				if (parse->task[*i + 1] && parse->task[*i + 1]->link == PIPE)
					*i += 1;
				else
					return (true);
			}
		}
		else
			return (false);
	}
	return (true);
}

void	ft_wait_all(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		waitpid(parse->task[i]->pid, &parse->task[i]->status, 0);
		i++;
	}
	ft_sig_init(1);
}

bool	ft_execution(t_parse *parse)
{
	size_t	i;

	i = 0;
	ft_exec_redirect(parse);
	ft_get_path(parse);
	ft_sig_init(0);
	while (parse->task && parse->task[i])
	{
		if (!ft_is_fork(parse, i))
			ft_exec_builtin(parse, parse->task[i++]);
		else
		{
			if (parse->task[i] && parse->task[i]->cmd && parse->task[i]->cmd[0])
			{
				ft_exec_pipe(parse, &i);
				if (!ft_exec_or(parse, &i))
					break ;
				if (!ft_exec_and(parse, &i))
					break ;
			}
			i++;
		}
	}
	ft_wait_all(parse);
	return (true);
}
