/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:46:24 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/12 10:58:44 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_errors_handler(char *input)
{
	if (ft_strlen(input) == 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		//g_mini.status = 258;
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(input[0], 2);
		ft_putstr_fd("'\n", 2);
		//g_mini.status = 258;
	}
}