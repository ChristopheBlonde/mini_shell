/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:13:34 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/20 22:55:06 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_redirection(char *input, int *i, char symbol, int return_value)
{
	*i += 2;
	skip_spaces(input, i);
	if (input[*i] == '*' && symbol != '<')
		return (12);
	if (input[*i] == symbol)
		return (return_value);
	if (input[*i] == '\0' || input[*i] == '\n')
		return (6);
	return (0);
}

int	check_single_redirection(char *input, int *i)
{
	(*i)++;
	skip_spaces(input, i);
	if (input[*i] == '\0' || input[*i] == '\n')
		return (6);
	if (input[*i] == '*')
		return (12);
	return (0);
}

int	check_redirection(char *input, int i)
{
	if (input[i + 1] == '>')
		return (check_double_redirection(input, &i, '>', 8));
	if (input[i + 1] == '<')
		return (check_double_redirection(input, &i, '<', 10));
	if (input[i] == '>')
		return (check_single_redirection(input, &i));
	if (input[i] == '<')
		return (check_single_redirection(input, &i));
	return (0);
}
