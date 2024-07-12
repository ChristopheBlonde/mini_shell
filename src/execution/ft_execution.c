/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:38:45 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/12 13:24:14 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_exec_or(t_parse *parse, size_t *i)
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
			while (parse->task[*i] && parse->task[*i]->link == PIPE
				&& parse->task[*i]->lvl == parse->task[*i - 1]->lvl)
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

bool	ft_exec_and(t_parse *parse, size_t *i)
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
			while (parse->task[*i] && parse->task[*i]->link == PIPE
				&& parse->task[*i]->lvl == parse->task[*i - 1]->lvl)
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

static void	ft_wait_all(t_parse *parse)
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

static void	ft_close_sub(t_parse *parse, size_t cur_sub, size_t i, int status)
{
	if (cur_sub != 0)
	{
		status = parse->task[i - 1]->status;
		ft_free_all(parse);
		exit(status);
	}
}

bool	ft_execution(t_parse *parse)
{
	size_t	i;
	pid_t	sub_lvl;
	size_t	cur_sub;

	i = 0;
	ft_sig_init(0);
	cur_sub = 0;
	ft_exec_redirect(parse, -1);
	while (parse->task && parse->task[i])
	{
		if (!ft_is_subexec(parse, &sub_lvl, &cur_sub, &i))
			return (true);
		if (cur_sub == parse->task[i]->lvl)
		{
			if (!ft_exec_cmd(parse, &i))
				break ;
		}
		else if (!parse->task[i + 1])
			i++;
	}
	ft_close_sub(parse, cur_sub, i, 0);
	ft_wait_all(parse);
	return (true);
}
