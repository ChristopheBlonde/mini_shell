/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:09:23 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/04 10:55:16 by cblonde          ###   ########.fr       */
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

static void	ft_del_operator(char **arr,char *cmd, size_t j)
{
	if (!ft_strncmp(cmd, "||", -1)
		|| !ft_strncmp(cmd, "&&", -1)
		|| !ft_strncmp(cmd, "|", -1))
	{
		while(arr[j])
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

void	ft_clean_operator(t_parse *parse)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			ft_del_operator(parse->task[i]->cmd, parse->task[i]->cmd[j], j);
			ft_rewrite_operator(parse->task[i]->cmd[j]);
			j++;
		}
		i++;
	}
}
