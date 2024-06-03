/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:17 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/03 10:25:14 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_exec_redirect(t_parse *parse)
{
	size_t				i;
	t_file_descriptor	*file;

	i = 0;
	if (!parse->redirect)
		return (true);
	while (parse->redirect[i])
	{
		file = (t_file_descriptor *)parse->redirect[i];
		if (file->type == READ)
			file->fd = open(file->file, O_RDONLY);
		if (file->type == WRITE)
			file->fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->type == APPEND)
			file->fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file->type == HEREDOC)
			ft_here_doc(parse, i);
		if (file->fd < 0)
			ft_putendl_fd(strerror(errno), 2);
		i++;
	}
	return (true);
}
