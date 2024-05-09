/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_operator_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:45:50 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/06 10:15:30 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';' \
		|| input[i] == '<' || input[i] == '>' || input[i] == '\n')
		return (1);
	return (0);
}

static int	handle_or_operator(char *input, int i, int in_quotes)
{
	int	check;

	check = 0;
	if (input[i] == '|' && in_quotes == -1)
	{
		if (input[i + 1] == '\n')
			return (1);
		if (input[i + 1] == '|')
			check = 1;
		else
			check = 2;
		i += 2;
	}
	return (check);
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
		if (check == 1 && check_after_spaces(input, i))
			return (1);
		else if (check == 2 && check_after_spaces(input, i))
			return (1);
	}
	return (0);
}

int	ft_check_or_operator(char *input)
{
	int	check;

	check = ft_or_operator_handler(input);
	if (check != 0)
	{
		printf("Error: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}
