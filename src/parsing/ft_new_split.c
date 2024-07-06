/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:09:23 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/06 22:13:59 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_size(char **cmd)
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

char	*ft_strndup(char *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)ft_calloc(n + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

// On va re split pour chaque redirection
// From cmd[0] = echo, cmd[1] = a>oui
// to cmd[0] = echo, cmd[1] = a, cmd[2] = >, cmd[3] = oui

void	free_new_cmd(char **new_cmd)
{
	int	i;

	i = 0;
	while (new_cmd[i])
	{
		free(new_cmd[i]);
		i++;
	}
	free(new_cmd);
}

bool	need_split(char *cmd)
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

int	handle_no_split(char **cmd, char **new_cmd, int *index)
{
	new_cmd[*index] = ft_strdup(cmd[*index]);
	if (!new_cmd[*index])
	{
		free_new_cmd(new_cmd);
		return (0);
	}
	(*index)++;
	return (1);
}

int	dup_start(char *cmd, char **new_cmd, int *index, int *j)
{
	new_cmd[*index] = ft_strndup(cmd, *j);
	if (!new_cmd[*index])
	{
		free_new_cmd(new_cmd);
		return (0);
	}
	(*index)++;
	return (1);
}

int	dup_middle(char *cmd, char **new_cmd, int *index, int *j)
{
	new_cmd[*index] = ft_strndup(&cmd[*j], 1);
	if (!new_cmd[*index])
	{
		free_new_cmd(new_cmd);
		return (0);
	}
	(*index)++;
	return (1);
}

int	dup_end(char *cmd, char **new_cmd, int *index, int *j)
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

int	dup_double(char *cmd, char **new_cmd, int *index, int *j)
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

char	**new_split(char **cmd)
{
	char	**new_cmd;
	int		i;
	int		j;
	int		index;

	index = 0;
	new_cmd = (char **)ft_calloc(new_size(cmd) + 1, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		j = -1;
		if (!need_split(cmd[i]) && !handle_no_split(cmd, new_cmd, &index))
			if (!handle_no_split(cmd, new_cmd, &index))
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
