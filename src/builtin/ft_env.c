/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:20:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/04 15:21:37 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		if (ft_strncmp(parse->env[i], "?=", 2))
			ft_putendl_fd(parse->env[i], 1);
		i++;
	}
	ft_excmd_result(parse, 0);
	return (0);
}
