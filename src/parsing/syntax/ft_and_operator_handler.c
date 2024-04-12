/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and_operator_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:28:07 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/12 17:36:53 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_and_operator_handler(char *input)
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
		if (input[i] == '&' && quote == -1)
		{
			check++;
			i++;
			if (input[i] != '&')
				return (1);
			else if (input[i] == '&')
				check++;
		}
	}
	return (check % 2);

}

void	ft_check_and_operator(char *input)
{
	int		check;
	char	*tmp;
	
	tmp = ft_strdup(input);
	check = ft_and_operator_handler(tmp);
	if (check != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
		free(tmp);
		exit(0);
	}
	free(tmp);
}
