/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:40:27 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/23 09:52:55 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_errors_handler(char *input)
{
	if (ft_check_and_operator(input) || ft_check_or_operator(input) || ft_check_parenthesis(input))
		return (1);

	return (0);
}

