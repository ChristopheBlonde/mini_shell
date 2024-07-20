/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:58:31 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/21 00:10:59 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parenthesis_handler(char *input)
{
	int	check;
	int	quote;
	int	i;

	check = 0;
	quote = -1;
	i = -1;
	while (input[++i])
	{
		in_quote(input, &quote, i);
		if (input[i] == '(' && quote == -1)
			check++;
		if (input[i] == ')' && quote == -1)
		{
			if (check == 0)
				return ((int) ')');
			check--;
		}
	}
	if (check != 0)
		return ((int) '(');
	return (0);
}

static int	ft_empty_parenthesis(char *input)
{
	int	i;
	int	quote;
	int	index;

	i = -1;
	quote = -1;
	while (input[++i])
	{
		index = -1;
		in_quote(input, &quote, i);
		if (quote == -1 && input[i] == '(')
			index = i;
		if (index != -1)
			while (input[i] == '(')
				i++;
		while (index != -1 && input[i] == ' ')
			i++;
		if (index != -1 && index == 0 && input[i] == ')')
			return ((int) ')');
		if (index != -1 && index != 0 && input[i] == ')')
			return ((int) '(');
	}
	return (0);
}

int	ft_check_parenthesis(char *input)
{
	int	check;

	check = ft_parenthesis_handler(input);
	if (!check)
		check = ft_empty_parenthesis(input);
	if (check == (int) '(')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		return (1);
	}
	if (check == (int) ')')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
		return (1);
	}
	return (0);
}
