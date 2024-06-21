/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:17:45 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/19 10:22:12 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_good_error_msg(int code_error)
{
	const char	*error_messages[] = {
		"",
		" syntax error near unexpected token `&&'",
		" syntax error near unexpected token `&'",
		" syntax error near unexpected token `||'",
		" syntax error near unexpected token `|'",
		" syntax error near unexpected token `;'",
		" syntax error near unexpected token `newline'",
		" syntax error near unexpected token `end of file'",
		" syntax error near unexpected token `>'",
		" syntax error near unexpected token `>>'",
		" syntax error near unexpected token `<'",
		" syntax error near unexpected token `<<'",
		" ambiguous redirect"
	};

	if (code_error >= 1 && code_error <= 12)
		ft_putendl_fd((char *)error_messages[code_error], 2);
}

int	check_redirection(char *input, int i)
{
	if (input[i + 1] == '>')
	{
		if (input[i + 2])
		{
			i += 2;
			skip_spaces(input, &i);
			if (input[i] == '*')
				return (12);
			if (input[i] == '>')
				return (8);
			if (input[i] == '\0' || input[i] == '\n')
				return (6);
		}
	}
	if (input[i + 1] == '<')
	{
		if (input[i + 2])
		{
			i += 2;
			skip_spaces(input, &i);
			if (input[i] == '*')
				return (12);
			if (input[i] == '<')
				return (10);
			if (input[i] == '\0' || input[i] == '\n')
				return (6);
		}
	}
	if (input[i] == '>')
	{
		i++;
		skip_spaces(input, &i);
		if (input[i] == '\0' || input[i] == '\n')
			return (6);
		if (input[i] == '*')
			return (12);
	}
	if (input[i] == '<')
	{
		i++;
		skip_spaces(input, &i);
		if (input[i] == '\0' || input[i] == '\n')
			return (6);
		if (input[i] == '*')
			return (12);
	}
	return (6);
}

int	check_before_operator(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '\0')
		return (7);
	if ((input[i] == '&' && input[i + 1] == '&')
		|| (input[i] == '|' && input[i + 1] == '|'))
	{
		if (input[i] == '&')
			return (1);
		return (3);
	}
	if (input[i] == '&')
		return (2);
	if (input[i] == '|')
		return (4);
	if (input[i] == ';')
		return (5);
	if (input[i] == '\n')
		return (6);
	if (input[i] == '>' || input[i] == '<')
	{
		check_redirection(input, i);
		if (check_redirection(input, i) != 0)
			return (check_redirection(input, i));
	}
	return (0);
}

int	check_before_pipe(char *input, int i)
{
	int	index;
	int	double_pipe;
	int	double_ampersand;

	double_pipe = 0;
	if (input[i] == '|' && input[i + 1] == '|')
		double_pipe = 1;
	double_ampersand = 0;
	if (input[i] == '&' && input[i + 1] == '&')
		double_ampersand = 1;
	index = i - 1;
	while (ft_isspace(input[index]))
		index--;
	if (input[index] == '<' || input[index] == '>'
		|| (input[index] == '|' && input[index + 1] == '|')
		|| input[index] == ';' || double_ampersand == 1)
	{
		if (double_pipe == 1)
			return (3);
		return (4);
	}
	return (0);
}
