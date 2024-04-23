/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:56:25 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/23 09:44:37 by tsadouk          ###   ########.fr       */
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

char	*ft_strqcpy(char *s, char quote)
{
	size_t		len;
	char		*result;
	size_t		i;
	size_t		j;

	len = ft_strlen(s);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != quote)
			result[j++] = s[i];
	free(s);
	return (result);
}

void	ft_delete_quotes(t_parse *parse, size_t i)
{
	size_t	j;

	j = -1;
	while (parse->task[i]->cmd[++j])
		if (parse->task[i]->cmd[j][0] == '\''
			|| parse->task[i]->cmd[j][0] == '"')
			parse->task[i]->cmd[j] = ft_strqcpy(parse->task[i]->cmd[j],
					parse->task[i]->cmd[j][0]);
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
