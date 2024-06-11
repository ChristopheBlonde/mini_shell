/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:15:30 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/11 09:44:37 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_error_msg(t_file_descriptor *file, size_t n)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(n), 2);
}

void	handle_bad_fd(t_parse *parse, t_object *task, size_t index)
{
	size_t	i;

	i = 0;
	if (task->errinfile != 0)
	{
//		if (parse->redirect[task->infile]->fd == -1)
//		{	
//			put_error_msg(parse->redirect[task->infile], task->errinfile);
//			ft_free_all(parse);
//			exit(1);
//		}
		while (parse->redirect[i])
		{
			if (parse->redirect[i]->task == (int)index 
				&& parse->redirect[i]->type == READ
				&& parse->task[i]->errinfile != 0)
			{
				put_error_msg(parse->redirect[i],
					parse->task[i]->errinfile);
				exit(1);
			}
			i++;
		}
	}
	if (task->erroutfile != 0)
	{
//		if (parse->redirect[task->outfile]->fd == -1)
//		{
//			put_error_msg(parse->redirect[task->outfile], task->outfile);
//			ft_free_all(parse);
//			exit(1);
//		}
		i = 0;
		while (parse->redirect[i])
		{
			if (parse->redirect[i]->task == (int)index 
				&& (parse->redirect[i]->type == WRITE
				|| parse->redirect[i]->type == APPEND)
				&& parse->task[i]->erroutfile != 0)
			{
				put_error_msg(parse->redirect[i],
					parse->task[i]->erroutfile);
				exit(1);
			}
			i++;
		}
	}
}
