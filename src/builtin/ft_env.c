/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:20:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 16:58:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	ft_check_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

int	ft_env(t_parse *parse)
{
	size_t	i;

	i = 0;
	if (!parse->env)
	{
		ft_excmd_result(parse, 1);
		return (1);
	}
	while (parse->env[i])
	{
		if (ft_strncmp(parse->env[i], "?=", 2) && ft_check_value(parse->env[i]))
			ft_putendl_fd(parse->env[i], 1);
		i++;
	}
	ft_excmd_result(parse, 0);
	return (0);
}
