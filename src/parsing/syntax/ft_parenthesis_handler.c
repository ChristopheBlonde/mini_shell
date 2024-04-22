/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:58:31 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/22 15:35:03 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


static	int	ft_parenthesis_handler(char *input)
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

int	ft_check_parenthesis(char *input)
{
	int		check;
	char	*tmp;

	tmp = ft_strdup(input);
	check = ft_parenthesis_handler(tmp);
	if (check == (int) '(')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		free(tmp);
		return (1);
	}
	if (check == (int) ')')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
