/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:43:17 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/05 15:21:53 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_if_exist(t_parse *parse, char *file, int index)
{
	size_t	i;

	i = 0;
	while (parse->redirect[i])
	{
		if ((int)i != index && !ft_strncmp(parse->redirect[i]->file, file,
				ft_strlen(file)))
			return (i);
		i++;
	}
	return (-1);
}

static void	handle_open(t_file_descriptor *file, t_parse *parse, int i)
{
	if (file->type == READ)
		file->fd = open(file->file, O_RDONLY);
	if (file->type == WRITE)
		file->fd = open(file->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->type == APPEND)
		file->fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file->type == HEREDOC)
		ft_here_doc(parse, i);
}

bool	ft_exec_redirect(t_parse *parse)
{
	size_t				i;
	t_file_descriptor	*file;
	int					exist;

	i = 0;
	if (!parse->redirect)
		return (true);
	while (parse->redirect[i])
	{
		file = (t_file_descriptor *)parse->redirect[i];
		exist = ft_check_if_exist(parse, file->file, i);
		if (exist != -1 && exist < (int)i
			&& file->type == parse->redirect[exist]->type && i++)
			continue ;
		handle_open(file, parse, i);
		i++;
	}
	return (true);
}
