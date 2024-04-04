/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:13:03 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/04 16:14:06 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_error_heredoc(int n, char *limiter)
{
	if (n == 0)
	{
		ft_putstr_fd("\e[0;36m\nwarning: here-document\
 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putendl_fd("')\e[0m", 2);
	}
	(void)limiter;
}

static bool	ft_check_end_of_file(char *tmp, char *line, char *limiter)
{
	size_t	i;
	char	*str;

	i = ft_strlen(line);
	if (!ft_strncmp(limiter, tmp, ft_strlen(limiter)))
		return (true);
	while (i > 0 && line[i - 1] != '\n')
		i--;
	str = ft_strjoin(&line[i], tmp);
	if (!str)
		return (false);
	if (!ft_strncmp(limiter, str, ft_strlen(limiter)))
	{
		free(str);
		return (true);
	}
	free(str);
	return (false);
}

static void	ft_write_file(t_parse *parse, char *line, int index)
{
	size_t	i;
	size_t	j;
	char	*start;
	//char	*end;
	//char	*var;

	(void)parse;
	(void)index;
	i = 0;
	j = 0;
	while (line[i] != '$')
		i++;
	start = (char *)ft_calloc(i + 1, sizeof(char));
	if (!start)
		return ;
	ft_memcpy(start, line, i);
	while (line[i + j + 1] != ' ')
		j++;
	//ft_putstr_fd("\e[0;31m", 1);
	//ft_putstr_fd(var, 1);
	//ft_putstr_fd("\e[m\n", 1);
	//&line[i + 1];
}

static void	ft_read_line(t_parse *parse, char *line, char *tmp, int index)
{
	while (true)
	{
		free(tmp);
		tmp = readline("heredoc>");
		if (tmp)
		{
			if (!ft_check_end_of_file(tmp, line, parse->redirect[index]->file))
			{
				line = ft_strfjoin(line, tmp, 1);
				if (!line)
					break ;
				line = ft_strfjoin(line, "\n", 1);
				if (!line)
					break ;
			}
			else
				break ;
		}
		else if (line[0] == '\0' || line[ft_strlen(line) - 1] == '\n')
		{
			ft_error_heredoc(0, parse->redirect[index]->file);
			break ;
		}
	}
	ft_write_file(parse, line, index);
}

int	ft_here_doc(t_parse *parse, int index)
{
	char	*tmp;
	char	*line;
	char	*name;
	int		fd;

	name = NULL;
	fd = -1;
	line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (fd);
	tmp = (char *)ft_calloc(1, sizeof(char));
	if (!tmp)
	{
		free(line);
		return (fd);
	}
	if (ft_open_tmp(name) < 0)
	{
		free(line);
		free(tmp);
		return (fd);
	}
	ft_read_line(parse, line, tmp, index);
	free(tmp);
	return (fd);
}
