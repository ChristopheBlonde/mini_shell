/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:40:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/05 16:04:05 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_getenv(t_parse *parse, char *var)
{
	size_t	arr_len;
	size_t	var_len;
	int		index;

	var_len = ft_strlen(var);
	arr_len = ft_arrlen((void **)parse->env);
	index = ft_get_index_env(parse->env, var, arr_len);
	if (index < 0)
		return (NULL);
	return (&parse->env[index][var_len + 1]);
}
