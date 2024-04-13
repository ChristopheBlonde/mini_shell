/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:58:31 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/13 15:11:25 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	in_quote(char *input, int *quote, int i)
{
	if (input[i] == '\'' || input[i] == '"')
	{
		if (*quote == -1)
			*quote = i;
		else if (input[i] == input[*quote])
			*quote = -1;
	}
}

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

void	ft_check_parenthesis(char *input)
{
	int		check;
	char	*tmp;

	tmp = ft_strdup(input);
	check = ft_parenthesis_handler(tmp);
	if (check == (int) '(')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		free(tmp);
		exit(0);
	}
	if (check == (int) ')')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `)'\n", 2);
		free(tmp);
		exit(0);
	}
	free(tmp);
}
