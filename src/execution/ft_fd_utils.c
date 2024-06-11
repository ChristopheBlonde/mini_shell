/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:15:30 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/11 12:04:39 by cblonde          ###   ########.fr       */
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

void	handle_bad_fd(t_parse *parse, t_object *task, size_t index)
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
		exit(1);
	}
}
