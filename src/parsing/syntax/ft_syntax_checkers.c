/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_checkers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:44:09 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/18 14:25:09 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_after_spaces_without_pipe(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == ';'
		|| input[i] == '<' || input[i] == '>' || input[i] == '\n'
		|| input[i] == '\0')
		return (1);
	return (0);
}

int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';'
		|| input[i] == '\n' || input[i] == '\0')
		return (1);
	return (0);
}

//TODO : FIX FOR THE HEREDOC BECAUSE << * shou
int	check_after_redirection(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '*')
		return (12);
	if (input[i] == '>' && input[i + 1] == '>' && input[i + 2]
		&& (input[i + 2] == '\n' || input[i + 2] == '\0'))
		return (9);
	if (input[i] == '<' && input[i + 1] == '<' && input[i + 2]
		&& (input[i + 2] == '\n' || input[i + 2] == '\0'))
		return (11);
	if (input[i] == '>' && input[i + 1] && (input[i + 1] == '\n'
			|| input[i + 1] == '\0'))
		return (8);
	if (input[i] == '<' && input[i + 1] && (input[i + 1] == '\n'
			|| input[i + 1] == '\0'))
		return (10);
	if (input[i] == '\n' || input[i] == '\0')
		return (6);
	return (0);
}

int	check_after_pipe(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '|')
		return (4);
	else if (input[i] == '&')
		return (2);
	else if (input[i] == ';')
		return (5);
	else if (input[i] == '\n' || input[i] == '\0')
		return (6);
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i] == '<' && input[i + 1] == '<'
			&& input[i + 2] && (input[i + 2] == '\n' || input[i + 2] == '\0'))
			if (check_after_redirection(input, i + 2))
				return (check_after_redirection(input, i + 2));
		if (input[i] == '>' && input[i + 1] == '>')
			if (check_after_redirection(input, i + 2) && input[i + 2]
				&& (input[i + 2] == '\n' || input[i + 2] == '\0'))
				return (check_after_redirection(input, i + 2));
		if (check_after_redirection(input, i + 1))
			return (check_after_redirection(input, i + 2));
	}
	return (0);
}
