/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:40:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/24 10:06:07 by cblonde          ###   ########.fr       */
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
	if (parse->env[index][var_len] == '\0')
		return (&parse->env[index][var_len]);
	return (&parse->env[index][var_len + 1]);
}
