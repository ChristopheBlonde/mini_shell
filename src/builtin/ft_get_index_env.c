/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:10:27 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/20 09:40:31 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_get_index_env(char **arr, char *var, int arr_len)
{
	int		i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (i < arr_len)
	{
		if (ft_strlen(arr[i]) >= len && !ft_isalnum(arr[i][len])
			&& !ft_strncmp(arr[i], var, len))
			return (i);
		i++;
	}
	return (-1);
}
