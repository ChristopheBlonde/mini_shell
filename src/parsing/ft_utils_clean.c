/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:09:23 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/08 08:58:36 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_envvar(t_parse *parse, t_object *task, size_t index)
{
	char	*env;

	if (task->cmd[index] && task->cmd[index][0] == '$')
	{
		env = ft_getenv(parse, &task->cmd[index][1]);
		if ((index == 0 || task->cmd[index - 1] == NULL) && env == NULL)
		{
			free(task->cmd[index]);
			task->cmd[index] = NULL;
			return (true);
		}
	}
	return (false);
}

static void	ft_del_operator(char **arr, char *cmd, size_t j)
{
	if (!ft_strncmp(cmd, "||", -1)
		|| !ft_strncmp(cmd, "&&", -1)
		|| !ft_strncmp(cmd, "|", -1))
	{
		free(arr[j]);
		while (arr[j])
		{
			arr[j] = arr[j + 1];
			j++;
		}
	}
}

static void	ft_rewrite_operator(char *cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!ft_strncmp(cmd, "||", 2)
			&& cmd[2])
		|| (!ft_strncmp(cmd, "&&", 2)
			&& cmd[2])
		|| (!ft_strncmp(cmd, "|", 1)
			&& cmd[1] && cmd[1] != '|'))
	{
		while (cmd[i] == '&' || cmd[i] == '|')
			i++;
		while (cmd[i])
		{
			cmd[j] = cmd[i];
			i++;
			j++;
		}
		cmd[j] = '\0';
	}
}

void	ft_clean_operator(t_object *task)
{
	size_t	j;

	j = 0;
	while (task->cmd[j])
	{
		ft_del_operator(task->cmd, task->cmd[j], j);
		ft_rewrite_operator(task->cmd[j]);
		j++;
	}
}
