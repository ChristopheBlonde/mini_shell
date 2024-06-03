/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:55:51 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/03 20:20:01 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_parse(t_parse *parse)
{
	parse->task = NULL;
	parse->env = NULL;
	parse->redirect = NULL;
	parse->input = NULL;
}

bool	ft_init_tasks(t_parse *parse, char **arr)
{
	size_t	i;
	size_t	len;

	i = 0;
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1,
			sizeof(t_object *));
	if (!parse->task)
		return (false);
	len = ft_arrlen((void **)arr);
	while (i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		if (!parse->task[i])
			return (false);
		parse->task[i]->cmd = ft_split_with_quotes(arr[i], ' ');
		if (!parse->task[i]->cmd)
			return (false);
		parse->task[i]->unquoted = NULL;
		parse->task[i]->infile = -1;
		parse->task[i]->outfile = -1;
		parse->task[i]->is_quoted = 0;
		parse->task[i]->pipe[0] = -1;
		parse->task[i]->pipe[1] = -1;
		i++;
	}
	return (true);
}
