/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:15:30 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/05 17:37:58 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_error_msg(t_file_descriptor *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(ENOENT), 2);
}

void	handle_bad_fd(t_parse *parse, t_object *task)
{
	if (task->infile != -1)
	{
		if (parse->redirect[task->infile]->fd == -1)
		{
			put_error_msg(parse->redirect[task->infile]);
			ft_free_all(parse);
			exit(1);
		}
	}
	if (task->outfile != -1)
	{
		if (parse->redirect[task->outfile]->fd == -1)
		{
			put_error_msg(parse->redirect[task->outfile]);
			ft_free_all(parse);
			exit(1);
		}
	}
}
