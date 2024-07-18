/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:56:25 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/18 09:56:31 by cblonde          ###   ########.fr       */
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

void	ft_strqcpy(char *s)
{
	char	*read;
	char	*write;
	char	quote;

	printf("passe la\n");
	if (!s)
		return ;
	read = s;
	write = s;
	quote = '\0';
	while (read && *read)
	{
		if (!quote && (*read == '\'' || *read == '"'))
		{
			quote = *read;
			read++;
		}
		if (!quote || (*read != quote))
		{
			*write = *read;
			write++;
		}
		else
			quote = '\0';
		read++;
	}
	*write = '\0';
	printf("str: %s$\n", s);
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
