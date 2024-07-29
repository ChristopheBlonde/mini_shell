/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:15:30 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/29 19:16:00 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_error_msg(t_file_descriptor *file, size_t n)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file->file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(n), 2);
}

static void	ft_errinfile(t_parse *parse, t_object *task, size_t index, int *s1)
{
	size_t	i;

	i = 0;
	if (task->errinfile != 0)
	{
		while (parse->redirect[i])
		{
			if (parse->redirect[i]->task == (int)index
				&& parse->redirect[i]->type == READ
				&& parse->task[index]->errinfile != 0)
			{
				if (*s1 == -1)
					*s1 = i;
			}
			i++;
		}
	}
}

static void	ft_erroutfile(t_parse *parse, t_object *task, size_t index, int *s2)
{
	size_t	i;

	i = 0;
	if (task->erroutfile != 0)
	{
		i = 0;
		while (parse->redirect[i])
		{
			if (parse->redirect[i]->task == (int)index
				&& (parse->redirect[i]->type == WRITE
					|| parse->redirect[i]->type == APPEND)
				&& parse->task[index]->erroutfile != 0)
			{
				if (*s2 == -1)
					*s2 = i;
			}
			i++;
		}
	}
}

bool	handle_bad_fd(t_parse *parse, t_object *task, size_t index, int n)
{
	int	stock_1;
	int	stock_2;

	stock_1 = -1;
	stock_2 = -1;
	ft_errinfile(parse, task, index, &stock_1);
	ft_erroutfile(parse, task, index, &stock_2);
	if (stock_1 != -1 || stock_2 != -1)
	{
		if (stock_1 != -1 && (stock_1 < stock_2 || stock_2 == -1))
			put_error_msg(parse->redirect[stock_1],
				parse->task[index]->errinfile);
		else if (stock_2 != -1 && (stock_2 < stock_1 || stock_1 == -1))
			put_error_msg(parse->redirect[stock_2],
				parse->task[index]->erroutfile);
		ft_close_fd_task(parse, index);
		if (n == 0)
			ft_excmd_result(parse, 1);
		if (n == 0)
			return (true);
		ft_free_all(parse);
		ft_close_std_fd();
		exit(1);
	}
	return (true);
}

void	ft_handle_error_exec(t_parse *parse, char *str)
{
	int	fd;
	DIR	*folder;

	if (!ft_strncmp(str, ".", -1))
		ft_exit_dot(parse);
	fd = open(str, O_WRONLY);
	folder = opendir(str);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (!ft_strchr(str, '/'))
		ft_putendl_fd(": command not found", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": Is a directory", 2);
	if (folder)
		closedir(folder);
	if (fd != -1)
		close(fd);
}
