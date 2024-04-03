/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_random.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:57:48 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/02 11:54:06 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_get_random(size_t max)
{
	int 	fd;
	size_t	count;
	char	buffer[250];
	size_t	i;

	i = 0;
	count = 0;
	fd = open("/dev/random",O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("\033[0;31mFail open file random\033[m", 2);
		return (0);
	}
	if (read(fd, buffer, 250) < 0)
		return (0);
	while (i < 250)
	{
		count += buffer[i];
		i++;
	}
	close(fd);
	return (count % max);
}
