/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:20:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/23 15:07:07 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_parse *parse)
{
	size_t	i;

	i = 0;
	if (!parse->env)
		return (ft_excmd_result(parse, 1));
	while (parse->env[i])
	{
		ft_putendl_fd(parse->env[i], 1);
		i++;
	}
	ft_excmd_result(parse, 0);
}
