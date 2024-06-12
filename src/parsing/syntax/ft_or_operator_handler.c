/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_operator_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:45:50 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/12 14:18:28 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_after_spaces_without_pipe(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == ';'
		|| input[i] == '<' || input[i] == '>' || input[i] == '\n'
		|| input[i] == '\0')
		return (1);
	return (0);
}

static int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';'
		|| input[i] == '\n' || input[i] == '\0')
		return (1);
	return (0);
}

int	check_after_redirection(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '>' && input[i + 1] == '>')
		return (9);
	if (input[i] == '<' && input[i + 1] == '<')
		return (11);
	if (input[i] == '>')
		return (8);
	if (input[i] == '<')
		return (10);
	if (input[i] == '\n' || input[i] == '\0')
	{
		printf("I'm here 3\n");
		return (1);
	}
	return (0);
}

static int check_after_pipe(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i] == '<' && input[i + 1] == '<')
			if (check_after_redirection(input, i + 2))
				return (6);
		if (input[i] == '>' && input[i + 1] == '>')
			if (check_after_redirection(input, i + 2))
				return (6);
		if (check_after_redirection(input, i + 1))
			return (6);
	}
	return (0);
}

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
		{
			return (1);
		}
		if (input[i + 1] == '|')
			check = 1;
		else
			check = 2;
		i += 2;
	}
	return (check);
}
/* If input[i] == '|', skip_spaces, if input[i] == '<' || input[i] == '>', check_after_redirection */
/* If input[i] == '|', skip_spaces, if input[i] == '|', return 1, else return 2 */

static int check_line(char *input)
{
	int	i;
	int	in_quotes;
	int	code_error;

	code_error = 0;
	i = -1;
	in_quotes = -1;
	while (input[++i])
	{
		in_quote(input, &in_quotes, i);
		if (input[i] == '|' && in_quotes == -1)
		{
			if (input[i + 1] && (input[i + 1] == '\n' || input[i + 1] == '\0'))
				return (4);
			if (check_after_pipe(input, i + 1))
			{
				code_error = check_after_pipe(input, i + 1);
				return (code_error);
			}
			if (input[i + 1] == '\n' || input[i + 1] == '\0')
			{
				// printf("Here ?\n");
				return (1);
			}
			if (input[i + 1] == '|' && (input[i + 2] == '\0' || input[i + 2] == '\n'))
				return (3);
			i += 2;
		}
		if ((input[i] == '<' || input[i] == '>') && in_quotes == -1)
		{
			if (check_after_redirection(input, i + 1))
			{
				return (check_after_redirection(input, i + 1));
			}
			else
				printf("ELSE\n");
		}
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
		//printf("Error line 164\n");
		print_good_error_msg(code);
		return (1);
	}
	if (check_line(input))
	{
		code = check_line(input);
		//printf("Error line 171\n");
		print_good_error_msg(code);
		return (1);
	}
	check = ft_or_operator_handler(input);
	if (check != 0)
	{
		printf("Error 2: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
