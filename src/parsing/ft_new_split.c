/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:09:23 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/07 18:45:01 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_size(char **cmd)
{
	int	arr_len;
	int	i;
	int	j;

	arr_len = ft_arrlen((void **)cmd);
	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '>' || cmd[i][j] == '<')
			{
				arr_len++;
				if (cmd[i][j + 1] == '>' || cmd[i][j + 1] == '<')
					j++;
				if (cmd[i][j + 1])
					arr_len++;
			}
			j++;
		}
		i++;
	}
	return (arr_len);
}

static bool	need_split(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '>' || cmd[i] == '<')
			return (true);
		i++;
	}
	return (false);
}

static int	handle_no_split(char **cmd, char **new_cmd, int *index, int i)
{
	if (cmd[i])
	{
		new_cmd[*index] = ft_strdup(cmd[i]);
		if (!new_cmd[*index])
		{
			free_new_cmd(new_cmd);
			return (0);
		}
		(*index)++;
	}
	else
		cmd[*index] = NULL;
	return (1);
}

void	free_new_cmd(char **new_cmd)
{
	int	i;

	i = 0;
	while (new_cmd[i])
	{
		free(new_cmd[i]);
		new_cmd[i] = NULL;
		i++;
	}
	free(new_cmd);
}

char	**new_split(char **cmd)
{
	char		**new_cmd;
	int			i;
	int			j;
	int			index;

	index = 0;
	new_cmd = (char **)ft_calloc(new_size(cmd) + 1, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		if (!need_split(cmd[i]) && !handle_no_split(cmd, new_cmd, &index, i))
			return (NULL);
		else if (need_split(cmd[i]))
			while (cmd[i][++j])
				if (cmd[i][j] == '>' || cmd[i][j] == '<')
					if (!split_redirections(cmd[i], new_cmd, &index, &j))
						return (NULL);
	}
	free_new_cmd(cmd);
	return (new_cmd);
}
