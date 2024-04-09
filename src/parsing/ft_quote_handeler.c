/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handeler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:17:21 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/05 15:49:12 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_quote(char *str)
{
	int quote;
	int i;

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


char	*ft_strjoin_char(char *s, char c)
{
	char	*new_str;
	int		i;

	if (!s || !c)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2)); // Allocate memory for the new string
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i]) // Copy the original string
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = c; // Add the new character
	new_str[i + 1] = '\0'; // Null-terminate the new string
	free(s); // Free the original string
	return (new_str);
}

char	*ft_quote_handeler(char *cmd)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = ft_strdup(""); // Initialize new_cmd with an empty string
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"') // Check if the character is a quote
		{
			i++; // Skip the quote
			while (cmd[i] && cmd[i] != '\'' && cmd[i] != '\"') // Copy until the closing quote
			{
				char *temp = ft_strjoin_char(new_cmd, cmd[i]);
				free(new_cmd);
				new_cmd = temp;
				i++;
			}
			if (cmd[i])
				i++; // Skip the closing quote
		}
		else
		{
			char *temp = ft_strjoin_char(new_cmd, cmd[i]);
			free(new_cmd);
			new_cmd = temp;
			i++;
		}
		// Add a space after each command except the last one
		if (cmd[i])
		{
			char *temp = ft_strjoin(new_cmd, " ");
			free(new_cmd);
			new_cmd = temp;
		}
	}
	return (new_cmd);
}


// TOK _> 