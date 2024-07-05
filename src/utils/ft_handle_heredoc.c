/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:41:22 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/05 16:05:43 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_heredoc_fd(t_parse *parse, t_file_descriptor *rfd,
		char *str, char *var)
{
	char	*tmp;
	int		tmp_fd;

	tmp = NULL;
	tmp = ft_calloc(1, sizeof(char));
	if (!tmp)
	{
		free(str);
		return ;
	}
	tmp = ft_replace_var(parse, str, tmp, var);
	if (str)
		free(str);
	close(rfd->fd);
	unlink(rfd->file);
	tmp_fd = open(rfd->file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	write(tmp_fd, tmp, ft_strlen(tmp));
	close(tmp_fd);
	ft_putendl_fd(tmp, 1);
	//rfd->fd = open(rfd->file, O_RDONLY);
	free(tmp);
}

void	ft_handle_heredoc_var(t_parse *parse, t_file_descriptor *rfd)
{
	char	*str;
	char	*var;
	char	*tmp;

	var = NULL;
	tmp = NULL;
	if (!rfd || rfd->in_quote || rfd->type != HEREDOC)
		return ;
	str = ft_calloc(1, sizeof(char));
	if (!str)
		return ;
	tmp = ft_get_next_line(rfd->fd);
	if (!tmp)
	{
		free(str);
		return ;
	}
	while (tmp)
	{
		str = ft_strfjoin(str, tmp, 3);
		tmp = ft_get_next_line(rfd->fd);
	}
	ft_handle_heredoc_fd(parse, rfd, str, var);
}
