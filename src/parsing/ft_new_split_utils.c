/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 23:23:04 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/09 15:05:05 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_search_end(char *cmd, int *end, int sign)
{
	while (cmd[++(*end)] && cmd[*end] == cmd[sign])
		;
	while (cmd[*end] && cmd[*end] != '<' && cmd[*end] != '>'
		&& cmd[*end] != '(' && cmd[*end] != ')')
		(*end)++;
}

static bool	ft_add_str(char **n_cmd, char *cmd, int *index, int range[3])
{
	n_cmd[*index] = ft_substr(cmd, range[0], range[1] - range[0]);
	ft_putendl_fd(n_cmd[*index], 1);
	if (!n_cmd[*index])
		return (false);
	(*index)++;
	return (true);
}

static bool	ft_add_start(char **new_cmd, char *cmd, int *index, int range[3])
{
	if (range[1] == 0 && range[2] != 0)
	{
		range[1] = range[2];
		if (!ft_add_str(new_cmd, cmd, index, range))
			return (true);
		range[2] = range[1] - 1;
		return (true);
	}
	return (false);
}

bool	ft_split_args(char *cmd, char **new_cmd, int *index)
{
	int	sign;
	int	quote;
	int	range[3];

	quote = -1;
	range[0] = 0;
	range[1] = 0;
	range[2] = -1;
	while (cmd[++(range[2])])
	{
		in_quote(cmd, &quote, range[2]);
		if (quote == -1 && (cmd[range[2]] == '<' || cmd[range[2]] == '>'
				|| cmd[range[2]] == '(' || cmd[range[2]] == ')'))
		{
			sign = range[2];
			if (ft_add_start(new_cmd, cmd, index, range))
				continue ;
			range[0] = range[2];
			ft_search_end(cmd, &range[1], sign);
			if (!ft_add_str(new_cmd, cmd, index, range))
				return (false);
			range[2] = range[1] - 1;
		}
	}
	return (true);
}
