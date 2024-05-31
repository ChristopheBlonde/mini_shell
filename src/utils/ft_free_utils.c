/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:39:59 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/31 11:53:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_file_descriptor(void *ptr)
{
	t_file_descriptor	*fd;

	fd = (t_file_descriptor *)ptr;
	if (fd->file)
		free(fd->file);
	fd->file = NULL;
	if (fd->fd != -1)
		close(fd->fd);
	free(fd);
}

void	ft_free_arrstruct(void **arr, void (*f)(void *))
{
	size_t	i;

	if (!arr || !f)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i])
		{
			f((void *)arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}
