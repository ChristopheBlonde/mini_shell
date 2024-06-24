/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:36:10 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/24 11:49:54 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_line_tmp(char *line, char *tmp)
{
	if (line)
		free(line);
	if (tmp)
		free(tmp);
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

	p = NULL;
	l = NULL;
	t = NULL;
	if (parse)
	{
		p = parse;
		l = line;
		t = tmp;
	}
	else
	{
		free(line);
		free(tmp);
		ft_free_all(p);
		p = NULL;
	}
}
