/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:56:25 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/23 13:46:48 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quote(char *str)
{
	int	quote;
	int	i;

	i = -1;
	quote = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quote == -1)
				quote = i;
			else if (str[i] == str[quote])
				quote = -1;
		}
	}
	return (quote == -1);
}

char	*ft_strqcpy(char *s)
{
	size_t	len;
	char	*result;
	int		quote;
	size_t	i;
	size_t	j;

	len = ft_strlen(s);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = -1;
	while (s[i])
	{
		if (quote == -1 && (s[i] == '\'' || s[i] == '\"'))
			quote = i;
		if ((i == 0 && quote == -1) || (quote != (int)i && s[i] != s[quote]))
			result[j++] = s[i];
		else
			quote = -1;
		i++;
	}
	free(s);
	return (result);
}

void	ft_delete_quotes(t_parse *parse)
{
	size_t	j;
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			if (ft_quoted(parse->task[i]->cmd[j]))
				parse->task[i]->cmd[j] = ft_strqcpy(parse->task[i]->cmd[j]);
			j++;
		}
		i++;
	}
}

void	in_quote(char *input, int *quote, int i)
{
	if (input[i] == '\'' || input[i] == '"')
	{
		if (*quote == -1)
			*quote = i;
		else if (input[i] == input[*quote])
			*quote = -1;
	}
}

bool	ft_quoted(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}
