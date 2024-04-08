/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tmp_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:47:46 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/08 14:05:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_rand_str(size_t size)
{
	char	*base;
	char	*str;
	size_t	i;
	char	rand[2];

	i = 4;
	rand[1] = '\0';
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
		rand[0] = base[ft_get_random(36)];
		str = ft_strfjoin(str, rand, 1);
		i++;
	}
	free(base);
	str = ft_strfjoin(str, ".tmp", 1);
	return (str);
}

int	ft_open_tmp(char **name)
{
	int		fd;

	*name = ft_rand_str(52);
	if (!*name)
		return (-1);
	if (!access(*name, F_OK))
	{
		free(*name);
		ft_open_tmp(name);
	}
	fd = open(*name, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
	{
		free(*name);
		ft_open_tmp(name);
	}
	return (fd);
}
