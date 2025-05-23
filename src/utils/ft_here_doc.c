/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:13:03 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/05 15:23:51 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_add_value(t_parse *parse, char **var, char **str, int check)
{
	if (check == 1)
		*str = ft_strfjoin(*str, "$", 1);
	else if (*var && (*var)[0] != '\0' && ft_getenv(parse, *var))
		*str = ft_strfjoin(*str, ft_getenv(parse, *var), 1);
	free(*var);
	*var = NULL;
	if (!*str)
		return ;
}

char	*ft_replace_var(t_parse *parse, char *line, char *str, char *var)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < ft_strlen(line))
	{
		k = i;
		while (line[i] && line[i] != '$')
			i++;
		str = ft_strfjoin(str, ft_substr(line, k, i - k), 3);
		if (!str)
			return (NULL);
		j = 0;
		while (line[i] && (line[i + j + 1] != '\n' && line[i + j + 1] != '\0')
			&& line[i + j + 1] != ' ' && line[i + j + 1] != '$'
			&& line[i + j + 1] != '\'' && line[i + j] != '?')
			j++;
		var = ft_substr(line, i + 1, j);
		if (!var)
			return (NULL);
		ft_add_value(parse, &var, &str, pre_check(j, line[i]));
		i += ++j;
	}
	return (str);
}

static void	ft_write_file(t_parse *parse, char **line, int index, char **tmp)
{
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
	ft_putstr_fd(*line, parse->redirect[index]->fd);
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	close(parse->redirect[index]->fd);
}

void	ft_read_line(t_parse *parse, char *line, char *tmp, int index)
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
				line = ft_strfjoin(line, tmp, 1);
			if (!line)
				break ;
			if (!ft_check_end_of_file(tmp, line, parse->redirect[index]->file))
				ft_handle_free_heredoc(NULL, line, NULL);
			else
				break ;
		}
		else if (line[0] == '\0' || line[ft_strlen(line) - 1] == '\n')
		{
			ft_error_heredoc(0, parse->redirect[index]->file);
			break ;
		}
	}
	ft_write_file(parse, &line, index, &tmp);
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
	parse->redirect[index]->fd = ft_open_tmp(&name);
	if (parse->redirect[index]->fd < 0)
	{
		ft_free_line_tmp(&line, &tmp);
		return (ft_fail_open(name, line, tmp));
	}
	ft_fork_heredoc(parse, (char *[3]){name, line, tmp}, index);
	free(parse->redirect[index]->file);
	parse->redirect[index]->file = name;
	close(parse->redirect[index]->fd);
	parse->redirect[index]->fd = open(parse->redirect[index]->file, O_RDONLY);
	ft_free_line_tmp(&line, &tmp);
	return (parse->redirect[index]->fd);
}
