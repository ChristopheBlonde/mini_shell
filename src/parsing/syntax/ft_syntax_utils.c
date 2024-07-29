/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:17:45 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/29 16:45:02 by cblonde          ###   ########.fr       */
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
		" ambiguous redirect",
		"minishell: .: filename argument required\n\
.: usage: . filename [arguments]"
	};

	if (code_error >= 1 && code_error <= 13)
		ft_putendl_fd((char *)error_messages[code_error], 2);
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

	index = i - 1;
	double_pipe = (input[index] == '|' && input[i] == '|');
	double_ampersand = (input[index] == '&' && input[i] == '&');
	if (double_pipe || double_ampersand)
		index--;
	while (index >= 0 && ft_isspace(input[index]))
		index--;
	if (index >= 0 && (input[index] == '<' || input[index] == '>'
			|| (input[index] == '|' && input[index + 1] == '|')
			|| input[index] == ';' || double_ampersand))
	{
		if (double_pipe)
			return (3);
		return (4);
	}
	return (0);
}
