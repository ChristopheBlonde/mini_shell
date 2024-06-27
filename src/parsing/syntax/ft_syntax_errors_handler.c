/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_errors_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:40:27 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/13 15:39:01 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_syntax_errors_handler(t_parse *parse, char *input)
{
	if (ft_check_or_operator(input) || ft_check_and_operator(input)
		||ft_check_parenthesis(input))
	{
		ft_excmd_result(parse, 2);
		return (1);
	}
	if (check_empty_quote(input))
	{
		ft_putendl_fd("Command '' not found", 2);
		ft_excmd_result(parse, 2);
		return (1);
	}
	if (!check_quote(input))
	{
		ft_putendl_fd("Error: unmatched quote", 2);
		ft_excmd_result(parse, 2);
		return (1);
	}
	return (0);
}
