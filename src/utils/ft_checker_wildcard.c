/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_wildcard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:02:59 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/22 18:03:49 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_wildcard(char *args)
{
	int	i;
	int	quote;

	i = 0;
	quote = -1;
	while (args[i])
	{
		in_quote(args, &quote, i);
		if (quote == -1 && args[i] == '*')
			return (true);
		i++;
	}
	return (false);
}
