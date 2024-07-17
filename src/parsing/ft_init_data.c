/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:55:51 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/17 09:39:50 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_parse(t_parse *parse)
{
	parse->task = NULL;
	parse->env = NULL;
	parse->redirect = NULL;
	parse->input = NULL;
	parse->sub_lvl = NULL;
	parse->n_sub = 0;
}

static void	ft_init_task(t_object *task)
{
	task->infile = -1;
	task->outfile = -1;
	task->is_quoted = 0;
	task->pipe[0] = -1;
	task->pipe[1] = -1;
	task->errinfile = 0;
	task->erroutfile = 0;
	task->open = 0;
	task->close = 0;
	task->i_sub = -1;
}

static bool	need_resplit(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (need_split(cmd[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	ft_init_tasks(t_parse *parse, char **arr)
{
	size_t	i;
	size_t	len;

	i = -1;
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1,
			sizeof(t_object *));
	if (!parse->task)
		return (false);
	len = ft_arrlen((void **)arr);
	while (++i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		if (!parse->task[i])
			return (false);
		parse->task[i]->cmd = ft_split_with_quotes(arr[i], ' ');
		if (!parse->task[i]->cmd)
			return (false);
		if (need_resplit(parse->task[i]->cmd))
			parse->task[i]->cmd = new_split(parse->task[i]->cmd);
		if (!parse->task[i]->cmd)
			return (false);
		ft_init_task(parse->task[i]);
	}
	return (true);
}
