/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:47:46 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/29 14:28:03 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_rand_str(size_t size)
{
	char	*base;
	char	*str;
	size_t	i;

	i = 4;
	if (size < 5)
		return (NULL);
	base = ft_strdup("abcdefghijklmnopqrstuvwxyz0123456789");
	if (!base)
		return (NULL);
	str = ft_strdup(".tfs");
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = base[ft_get_random(37)];
		i++;
	}
	str = ft_strfjoin(str, ".tmp", 1);
	return (str);
}
