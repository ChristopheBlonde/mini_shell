/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:09:23 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/09 15:05:54 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	need_split(char *cmd)
{
	int	i;
	int	quote;

	i = 0;
	quote = -1;
	while (cmd[i])
	{
		in_quote(cmd, &quote, i);
		if (quote == -1 && i != 0 && ((cmd[i] == '>' || cmd[i] == '<')
				|| (cmd[i] == '(' || cmd[i] == ')')))
			return (true);
		i++;
	}
	return (false);
}

static size_t	new_size_arg(char *cmd)
{
	size_t	i;
	size_t	count;
	int		quote;
	int		sign;

	i = 0;
	count = 0;
	quote = -1;
	while (cmd[i])
	{
		in_quote(cmd, &quote, i);
		if (quote == -1 && (cmd[i] == '<' || cmd[i] == '>'
				|| cmd[i] == '(' || cmd[i] == ')'))
		{
			count++;
			sign = i;
			while (cmd[++i] && cmd[i] == cmd[sign])
				;
			if (!cmd[i])
				break ;
		}
		else
			i++;
	}
	return (count);
}

static size_t	new_size(char **cmd)
{
	size_t	arr_len;
	size_t	i;

	arr_len = ft_arrlen((void **)cmd);
	i = 0;
	while (cmd[i])
	{
		if (need_split(cmd[i]))
			arr_len += new_size_arg(cmd[i]);
		i++;
	}
	return (arr_len);
}

static int	handle_no_split(char **cmd, char **new_cmd, int *index, int i)
{
	if (cmd[i])
	{
		new_cmd[*index] = ft_strdup(cmd[i]);
		if (!new_cmd[*index])
		{
			ft_free_array((void **)new_cmd);
			return (0);
		}
		(*index)++;
	}
	else
		cmd[*index] = NULL;
	return (1);
}

char	**new_split(char **cmd)
{
	char		**new_cmd;
	int			i;
	int			index;

	index = 0;
	new_cmd = (char **)ft_calloc(new_size(cmd) + 1, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	i = -1;
	while (cmd[++i])
	{
		if (!need_split(cmd[i]) && !handle_no_split(cmd, new_cmd, &index, i))
			return (NULL);
		else
			if (!ft_split_args(cmd[i], new_cmd, &index))
				return (NULL);
	}
	ft_free_array((void **)cmd);
	return (new_cmd);
}
