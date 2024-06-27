/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:36:10 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/27 09:49:45 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_line_tmp(char **line, char **tmp)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
}

void	ft_free_end_of_file(char *str, char *delimiter)
{
	if (str)
		free(str);
	if (delimiter)
		free(delimiter);
}

void	ft_handle_free_heredoc(t_parse *parse, char *line, char *tmp)
{
	static t_parse	*p;
	static char		*l;
	static char		*t;

	if (parse)
	{
		p = parse;
		l = line;
		t = tmp;
	}
	else
	{
		if (l)
			free(l);
		if (t)
			free(t);
		if (p)
			ft_free_all(p);
		p = NULL;
		l = NULL;
		t = NULL;
	}
}
