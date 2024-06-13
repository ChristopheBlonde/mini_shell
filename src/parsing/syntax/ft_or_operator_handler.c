/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_operator_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:45:50 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/13 22:43:51 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_or_operator(char *input, int i, int in_quotes)
{
	int	check;
	int	code_error;

	code_error = 0;
	check = 0;
	if (input[i] == '|' && in_quotes == -1)
	{
		if (check_after_pipe(input, i + 1))
		{
			code_error = check_after_pipe(input, i + 1);
			return (code_error);
		}
		if (input[i + 1] == '\n' || input[i + 1] == '\0')
			return (1);
		if (input[i + 1] == '|')
			check = 1;
		else
			check = 2;
		i += 2;
	}
	return (check);
}

static int	check_line(char *input)
{
	int	i;
	int	in_quotes;

	i = -1;
	in_quotes = -1;
	while (input[++i])
	{
		in_quote(input, &in_quotes, i);
		if (in_quotes != -1)
			continue ;
		if (input[i] == '|')
		{
			if (input[i + 1] && (input[i + 1] == '\n' || input[i + 1] == '\0'))
				return (4);
			if (check_after_pipe(input, i + 1))
				return (check_after_pipe(input, i + 1));
			if (input[i + 1] == '|')
				return (3);
			i += 1;
		}
		else if (input[i] == '<' || input[i] == '>')
			if (check_after_redirection(input, i + 1))
				return (check_after_redirection(input, i + 1));
	}
	return (0);
}

static int	ft_or_operator_handler(char *input)
{
	int	i;
	int	check;
	int	in_quotes;

	i = -1;
	in_quotes = -1;
	while (input[++i])
	{
		check = 0;
		in_quote(input, &in_quotes, i);
		check = handle_or_operator(input, i, in_quotes);
		if (check == 1 && check_after_spaces_without_pipe(input, i + 1))
			return (1);
		else if (check == 2 && check_after_spaces(input, i + 1))
			return (1);
	}
	return (0);
}

int	ft_check_or_operator(char *input)
{
	int	check;
	int	code;

	code = check_before_operator(input, 0);
	if (code > 0)
	{
		print_good_error_msg(code);
		return (1);
	}
	if (check_line(input))
	{
		code = check_line(input);
		print_good_error_msg(code);
		return (1);
	}
	check = ft_or_operator_handler(input);
	if (check != 0)
	{
		print_good_error_msg(4);
		return (1);
	}
	return (0);
}
