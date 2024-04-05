/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:13:03 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/05 16:03:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_error_heredoc(int n, char *limiter)
{
	if (n == 0)
	{
		ft_putstr_fd("\e[0;36mwarning: here-document\
 delimited by end-of-file (wanted `", 2);
		write(2, limiter, ft_strlen(limiter) - 1);
		ft_putendl_fd("')\e[0m", 2);
	}
	(void)limiter;
}

static bool	ft_check_end_of_file(char *tmp, char *line, char *limiter)
{
	size_t	i;
	char	*str;
	size_t	len;

	i = ft_strlen(line);
	len = ft_strlen(limiter);
	if (!ft_strncmp(limiter, tmp, len))
		return (true);
	while (i > 0 && line[i - 1] != '\n')
		i--;
	str = ft_strjoin(&line[i], tmp);
	if (!str)
		return (false);
	if (!ft_strncmp(limiter, str, len))
	{
		free(str);
		return (true);
	}
	free(str);
	return (false);
}

static char	*ft_replace_env(t_parse *parse, char *line, char *str, char *var)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (line[i])
	{
		k = i;
		while (line[i] && line[i] != '$')
			i++;
		str = ft_strfjoin(str, ft_substr(line, k, i - k), 3);
		if (!str)
			return (NULL);
		j = 0;
		while ((line[i + j + 1] != '\n' && line[i + j + 1] != '\0')
				&& line[i + j + 1] != ' ')
			j++;
		var = ft_substr(line, i + 1, j);
		if (var && var[0] != '\0' && ft_getenv(parse, var))
			str = ft_strfjoin(str, ft_getenv(parse, var), 1);
		if (!str)
			return (NULL);
		i += ++j;
	}
	return (str);
}

static void	ft_write_file(t_parse *parse, char *line, int index)
{
	char	*str;
	char	*var;

	(void)parse;
	(void)index;
	str = (char *)ft_calloc(1, sizeof(char));
	if (!str)
		return ;
	var = NULL;
	str = ft_replace_env(parse, line, str, var);
	ft_putstr_fd("\e[0;31m", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\e[m\n", 1);
}

static void	ft_read_line(t_parse *parse, char *line, char *tmp, int index)
{
	while (true)
	{
		free(tmp);
		tmp = readline("heredoc>");
		if (tmp)
		{
			tmp = ft_strfjoin(tmp, "\n", 1);
			if (!tmp)
				break ;
			if (!ft_check_end_of_file(tmp, line, parse->redirect[index]->file))
			{
				line = ft_strfjoin(line, tmp, 1);
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

	name = NULL;
	line = (char *)ft_calloc(1, sizeof(char));
	if (!line)
		return (-1);
	tmp = (char *)ft_calloc(1, sizeof(char));
	if (!tmp)
		free(line);
	if (!tmp)
		return (-1);
	parse->redirect[index]->fd = ft_open_tmp(name);
	if (parse->redirect[index]->fd < 0)
	{
		free(name);
		free(line);
		free(tmp);
		return (-1);
	}
	ft_read_line(parse, line, tmp, index);
	free(tmp);
	return (parse->redirect[index]->fd);
}
