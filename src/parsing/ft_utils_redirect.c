/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:51 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 11:19:02 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_operation	ft_redirect_type(char *file)
{
	size_t	file_len;

	file_len = ft_strlen(file);
	if (file_len >= 2 && !ft_strncmp(file, ">>", 2))
		return (APPEND);
	if (file_len >= 2 && !ft_strncmp(file, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(file, "<", 1))
		return (READ);
	if (!ft_strncmp(file, ">", 1))
		return (WRITE);
	return (NO_OP);
}

void	ft_redirect_task(t_object *task, char *input, size_t index)
{
	if (!ft_strncmp(input, ">>", 2))
		task->outfile = index;
	if (!ft_strncmp(input, "<<", 2))
		task->infile = index;
	if (!ft_strncmp(input, "<", 1))
		task->infile = index;
	if (!ft_strncmp(input, ">", 1))
		task->outfile = index;
}
