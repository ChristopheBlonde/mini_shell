/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:17 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 15:27:06 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_open(t_file_descriptor *file, t_parse *parse, int i)
{
	if ((file->type == WRITE || file->type == APPEND)
		&& parse->task[file->task]->erroutfile != 0)
		return ;
	if (file->type == READ && parse->task[file->task]->errinfile != 0)
		return ;
	if (file->type == READ)
		file->fd = open(file->file, O_RDONLY);
	if (file->type == WRITE)
		file->fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->type == APPEND)
		file->fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file->fd == -1 && file->type != HEREDOC)
	{
		if (file->type == READ && parse->task[file->task]->errinfile == 0)
			parse->task[file->task]->errinfile = errno;
		else if (parse->task[file->task]->errinfile == 0)
			parse->task[file->task]->erroutfile = errno;
	}
	if (file->type == HEREDOC)
		ft_here_doc(parse, i);
}

bool	ft_exec_redirect(t_parse *parse)
{
	size_t				i;
	t_file_descriptor	*file;

	i = 0;
	if (!parse->redirect)
		return (true);
	ft_handle_free_heredoc(NULL, NULL, NULL);
	while (parse->redirect[i])
	{
		if (g_exit_code == 130)
			return (false);
		file = (t_file_descriptor *)parse->redirect[i];
		if (parse->task[file->task]->errinfile == 0
			&& parse->task[file->task]->erroutfile == 0)
			handle_open(file, parse, i);
		i++;
	}
	return (true);
}
