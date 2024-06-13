/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:17:45 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/13 17:20:42 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_good_error_msg(int code_error)
{
	const char	*error_messages[] = {
		"",
		"syntax error near unexpected token `&&'",
		"syntax error near unexpected token `&'",
		"syntax error near unexpected token `||'",
		"syntax error near unexpected token `|'",
		"syntax error near unexpected token `;'",
		"syntax error near unexpected token `newline'",
		"syntax error near unexpected token `end of file'",
		"syntax error near unexpected token `>`",
		"syntax error near unexpected token `>>'",
		"syntax error near unexpected token `<'",
		"syntax error near unexpected token `<<'"
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
	else if (input[i] == '\n' || input[i] == '>' || input[i] == '<')
		return (6);
	else if (input[i] == '\0')
		return (7);
	return (0);
}
