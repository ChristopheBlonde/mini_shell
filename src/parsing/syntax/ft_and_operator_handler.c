/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_operator_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:28:07 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/13 15:40:22 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *input, int *i)
{
	while (input[*i] == ' ' && input[*i] >= 9 && input[*i] <= 13)
		(*i)++;
}

static int	check_after_spaces(char *input, int i)
{
	skip_spaces(input, &i);
	if (input[i] == '&' || input[i] == '|' || input[i] == ';' \
		|| input[i] == '<' || input[i] == '>')
		return (1);
	return (0);
}

static int	ft_and_operator_handler(char *input)
{
	int	i;
	int	check;
	int	in_quotes;

	i = -1;
	check = 0;
	in_quotes = -1;
	while (input[++i])
	{
		in_quote(input, &in_quotes, i);
		if (input[i] == '&' && in_quotes == -1)
		{
			if (input[i + 1] != '&')
				return (1);
			check++;
			i += 2;
		}
		if (check && check_after_spaces(input, i))
			return (1);
	}
	return (0);
}

void	ft_check_and_operator(char *input)
{
	int	check;

	check = ft_and_operator_handler(input);
	if (check != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
		exit(0);
	}
}
