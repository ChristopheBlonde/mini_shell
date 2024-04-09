/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:56:25 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/09 13:59:27 by cblonde          ###   ########.fr       */
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

	len = strlen(s);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != quote)
			result[j++] = s[i];
	free(s);
	return (result);
}
