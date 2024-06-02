/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:51 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/02 11:28:08 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_heredoc(t_parse *parse, size_t i)
{
	size_t	j;

	j = i;
	if (parse->task[i] && parse->task[i]->infile != -1
		&& parse->redirect[parse->task[i]->infile]->type == HEREDOC)
		return (true);
	while (parse->task[i] && parse->task[i]->link == PIPE)
	{
		if (parse->task[i]->infile != -1
			&& parse->redirect[parse->task[i]->infile]->type == HEREDOC)
			return (true);
		i++;
	}
	while (j >= 0 && parse->task[j] && parse->task[j]->link != AND
		&& parse->task[j]->link != OR)
	{
		if (parse->task[j]->infile != -1
			&& parse->redirect[parse->task[j]->infile]->type == HEREDOC)
			return (true);
		j--;
	}
	return (false);
}

t_file_operation	ft_redirect_type(t_parse *parse, char *file, size_t i)
{
	size_t	file_len;

	file_len = ft_strlen(file);
	if (file_len >= 2 && !ft_strncmp(file, ">>", 2))
		return (APPEND);
	if (file_len >= 2 && !ft_strncmp(file, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(file, "<", 1))
		return (READ);
	if (!ft_strncmp(file, ">", 1))
	{
		if (ft_is_heredoc(parse, i))
			return (APPEND);
		return (WRITE);
	}
	return (NO_OP);
}

void	ft_redirect_task(t_object *task, char *input, size_t index)
{
	if (!ft_strncmp(input, ">>", 2))
		task->outfile = index;
	if (!ft_strncmp(input, "<<", 2))
		task->infile = index;
	if (!ft_strncmp(input, "<", 1))
		task->infile = index;
	if (!ft_strncmp(input, ">", 1))
		task->outfile = index;
}
