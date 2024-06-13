/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:21:47 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/13 15:25:57 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

void	update_quotes_status(t_list *current, size_t i, char *quote)
{
	if (is_quote(((char *)current->content)[i]))
	{
		if (*quote == '\0')
			*quote = ((char *)current->content)[i];
		else if (*quote == ((char *)current->content)[i])
			*quote = '\0';
	}
}

void	handle_quotes(t_list *current, int index, char *quote)
{
	if (is_quote(((char *)current->content)[index]))
		update_quotes_status(current, index, quote);
}
