/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:51 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/24 16:38:53 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file_operation	ft_redirect_type(char *file)
{
	if (!ft_strncmp(file, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(file, "<<", 2))
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
/*
void	ft_clean_task(t_object *task, size_t i_cmd, size_t i_redirect)
{
	ft_redirect_task(task, task->cmd[i_cmd], i_redirect);

	task->cmd = ft_reduce_cmd(task->cmd, i_cmd);
	if (!task->cmd)
	{
		ft_putendl_fd("Error: reduce cmd", 2);
		return ;
	}
}
*/
