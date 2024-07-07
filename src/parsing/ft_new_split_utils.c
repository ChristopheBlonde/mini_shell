/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:23:04 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/07 18:10:34 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_start(char *cmd, char **new_cmd, int *index, int *j)
{
	if (*j != 0)
	{
		new_cmd[*index] = ft_strndup(cmd, *j);
		if (!new_cmd[*index])
		{
			free_new_cmd(new_cmd);
			return (0);
		}
		(*index)++;
	}
	return (1);
}

static int	dup_middle(char *cmd, char **new_cmd, int *index, int *j)
{
	if (j != 0)
		new_cmd[*index] = ft_strndup(&cmd[*j], 1);
	if (!new_cmd[*index])
	{
		free_new_cmd(new_cmd);
		return (0);
	}
	(*index)++;
	return (1);
}

static int	dup_end(char *cmd, char **new_cmd, int *index, int *j)
{
	new_cmd[*index] = ft_strdup(&cmd[*j + 1]);
	if (!new_cmd[*index])
	{
		free_new_cmd(new_cmd);
		return (0);
	}
	(*index)++;
	return (1);
}

static int	dup_double(char *cmd, char **new_cmd, int *index, int *j)
{
	new_cmd[*index] = ft_strndup(&cmd[*j], 2);
	if (!new_cmd[*index])
	{
		free_new_cmd(new_cmd);
		return (0);
	}
	(*index)++;
	(*j)++;
	return (1);
}

int	split_redirections(char *cmd, char **new_cmd, int *index, int *j)
{
	if (!dup_start(cmd, new_cmd, index, j))
		return (0);
	if (cmd[*j + 1] == '>' || cmd[*j + 1] == '<')
	{
		if (!dup_double(cmd, new_cmd, index, j))
			return (0);
	}
	else
	{
		if (!dup_middle(cmd, new_cmd, index, j))
			return (0);
	}
	if (cmd[*j + 1])
	{
		if (!dup_end(cmd, new_cmd, index, j))
			return (0);
	}
	return (1);
}
