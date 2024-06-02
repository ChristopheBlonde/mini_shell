/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:01:13 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/02 11:27:22 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file_descriptor	*ft_create_redirect(t_parse *parse, char *op,
		char *file, size_t i)
{
	t_file_descriptor	*fd;

	if (!file)
		return (NULL);
	fd = (t_file_descriptor *)ft_calloc(1, sizeof(t_file_descriptor));
	if (!fd)
		return (NULL);
	fd->file = file;
	fd->in_quote = ft_quoted(file);
	fd->fd = -1;
	fd->type = ft_redirect_type(parse, op, i);
	if (fd->in_quote)
		fd->file = ft_strqcpy(file);
	return (fd);
}

static t_file_descriptor	**ft_realloc_redirect(t_file_descriptor **arr,
		size_t n)
{
	t_file_descriptor	**new_arr;
	size_t				i;

	new_arr = (t_file_descriptor **)ft_calloc(n + 2,
			sizeof(t_file_descriptor *));
	if (!new_arr)
		return (NULL);
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			new_arr[i] = arr[i];
			i++;
		}
		free(arr);
	}
	return (new_arr);
}

static char	*ft_getfile_name(char **cmd, size_t index)
{
	size_t	i;

	i = 0;
	while (cmd[index][i] == '<' || cmd[index][i] == ' ' || cmd[index][i] == '>')
		i++;
	if (cmd[index][i])
		return (ft_strdup(&cmd[index][i]));
	return (ft_strdup(cmd[index + 1]));
}

bool	ft_redirect_end(t_parse *parse, size_t *i, size_t *j, size_t *k)
{
	while (parse->task[*i]->cmd[*j])
	{
		if (ft_redirect_type(parse, parse->task[*i]->cmd[*j], *i) != NO_OP)
		{
			parse->redirect = ft_realloc_redirect(parse->redirect, *k);
			if (!parse->redirect)
			{
				ft_free_arrstruct((void **)parse->redirect,
					ft_free_file_descriptor);
				return (false);
			}
			parse->redirect[*k] = ft_create_redirect(parse,
					parse->task[*i]->cmd[*j],
					ft_getfile_name(parse->task[*i]->cmd, *j), *i);
			ft_redirect_task(parse->task[*i], parse->task[*i]->cmd[*j],
				(*k)++);
		}
		(*j)++;
	}
	return (true);
}

void	ft_redirection(t_parse *parse)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	parse->redirect = NULL;
	while (parse->task[i])
	{
		j = 0;
		if (!ft_redirect_end(parse, &i, &j, &k))
			return ;
		ft_reduce_cmd(parse, parse->task[i], i);
		i++;
	}
	i = 0;
	while (parse->task[i])
	{
		if (parse->task[i]->outfile != -1)
			parse->redirect[parse->task[i]->outfile]->type = APPEND;
		i++;
	}
}
