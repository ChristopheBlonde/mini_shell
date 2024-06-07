/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:17:45 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/07 14:04:03 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_good_error_msg(int code_error)
{
	if (code_error == 1)
		ft_putendl_fd("Error: syntax error near unexpected token `&&'", 2);
	else if (code_error == 2)
		ft_putendl_fd("Error: syntax error near unexpected token `&'", 2);
	else if (code_error == 3)
		ft_putendl_fd("Error: syntax error near unexpected token `||'", 2);
	else if (code_error == 4)
		ft_putendl_fd("Error: syntax error near unexpected token `|'", 2);
	else if (code_error == 5)
		ft_putendl_fd("Error: syntax error near unexpected token `;'", 2);
	else if (code_error == 6)
		ft_putendl_fd("Error: syntax error near unexpected token `newline'", 2);
	else if (code_error == 7)
		ft_putendl_fd("Error: syntax error near unexpected token `end of file'", 2);
}

int check_before_operator(char *input, int i)
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
