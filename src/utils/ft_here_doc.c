/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:13:03 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/08 14:00:39 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_add_value(t_parse *parse, char **var, char **str)
{
	if (*var && (*var)[0] != '\0' && ft_getenv(parse, *var))
		*str = ft_strfjoin(*str, ft_getenv(parse, *var), 1);
	free(*var);
	*var = NULL;
	if (!*str)
		return ;
}

static char	*ft_replace_env(t_parse *parse, char *line, char *str, char *var)
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
			&& line[i + j + 1] != ' ')
			j++;
		var = ft_substr(line, i + 1, j);
		if (!var)
			return (NULL);
		ft_add_value(parse, &var, &str);
		i += ++j;
	}
	return (str);
}

static void	ft_write_file(t_parse *parse, char *line, int index, char *tmp)
{
	char	*str;
	char	*var;

	free(tmp);
	str = (char *)ft_calloc(1, sizeof(char));
	if (!str)
		return ;
	var = NULL;
	if (parse->redirect[index]->file[0] != '\''
		&& parse->redirect[index]->file[0] != '"')
	{
		str = ft_replace_env(parse, line, str, var);
		ft_putstr_fd(str, parse->redirect[index]->fd);
		free(str);
	}
	else
	{
		free(str);
		ft_putstr_fd(str, parse->redirect[index]->fd);
	}
	free(line);
	if (var)
		free(var);
	close(parse->redirect[index]->fd);
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
	ft_write_file(parse, line, index, tmp);
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
	parse->redirect[index]->fd = ft_open_tmp(&name);
	if (parse->redirect[index]->fd < 0)
		return (ft_fail_open(name, line, tmp));
	ft_read_line(parse, line, tmp, index);
	free(parse->redirect[index]->file);
	parse->redirect[index]->file = name;
	return (parse->redirect[index]->fd);
}
