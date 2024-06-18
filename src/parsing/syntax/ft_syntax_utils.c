/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:17:45 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/18 17:15:50 by tsadouk          ###   ########.fr       */
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
		" syntax error near unexpected token `<<'"
	};

	if (code_error >= 1 && code_error <= 11)
		ft_putendl_fd((char *)error_messages[code_error], 2);
}

int	check_before_operator(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&')
	{
		if (input[i + 1] == '&')
			return (1);
		return (2);
	}
	else if (input[i] == '|')
	{
		if (input[i + 1] == '|')
			return (3);
		return (4);
	}
	else if (input[i] == ';')
		return (5);
	else if (input[i] == '\n')
		return (6);
	else if (input[i] == '>' || input[i] == '<')
	{
		if (input[i + 1] == '>')
		{
			if (input[i + 2])
			{
				i += 2;
				skip_spaces(input, &i);
				if (input[i] == '>')
					return (8);
				if (input[i] == '\0' || input[i] == '\n')
					return (6);
				return (0);
			}
		}
		else if (input[i + 1] == '<')
		{
			if (input[i + 2])
			{
				i += 2;
				skip_spaces(input, &i);
				if (input[i] == '<')
					return (10);
				if (input[i] == '\0' || input[i] == '\n')
					return (6);
				return (0);
			}
		}
		return (6);
	}	
	else if (input[i] == '\0')
		return (7);
	return (0);
}


int	check_before_pipe(char *input, int i)
{
	int index;
	int double_pipe;
	int double_ampersand;

	double_pipe = 0;
	if (input[i] == '|' && input[i + 1] == '|')
		double_pipe = 1;
	double_ampersand = 0;
	if (input[i] == '&' && input[i + 1] == '&')
		double_ampersand = 1;
	index = i - 1;
	while (ft_isspace(input[index]))
		index--;
	if (input[index] == '<' || input[index] == '>' || (input[index] == '|' && input[index + 1] == '|')
		|| input[index] == ';' || double_ampersand == 1)
	{
		if (double_pipe == 1)
			return (3);
		return (4);
	}
	return (0);
}
