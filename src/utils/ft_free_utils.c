/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:39:59 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/02 16:12:00 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_file_descriptor(void *ptr)
{
	t_file_descriptor	*fd;

	fd = (t_file_descriptor *)ptr;
	if (fd->fd != -1)
		close(fd->fd);
	if (fd->file)
	{
		if (!ft_strncmp(fd->file, ".tfs", 4))
			unlink(fd->file);
		free(fd->file);
		fd->file = NULL;
	}
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

void	ft_close_std_fd(void)
{
	close(0);
	close(1);
	close(2);
}

void	ft_close_fd_task(t_parse *parse, size_t index)
{
	size_t	i;

	i = 0;
	while (parse->redirect[i])
	{
		if ((size_t)parse->redirect[i]->task == index)
		{
			if (parse->redirect[i]->fd >= 0)
				close(parse->redirect[i]->fd);
		}
		i++;
	}
	if (parse->task[index]->pipe[0] >= 0)
		close(parse->task[index]->pipe[0]);
	if (parse->task[index]->pipe[1] >= 0)
		close(parse->task[index]->pipe[1]);
}
