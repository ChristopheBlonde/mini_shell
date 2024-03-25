/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:39:28 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/22 13:29:22 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_putendl_fd(const char *str, int fd)
{
	int	len;

	if (!str || !fd)
		return ;
	len = ft_strlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
}
