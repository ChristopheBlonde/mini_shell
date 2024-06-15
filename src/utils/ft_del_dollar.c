/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:00:50 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/15 18:35:00 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_new_arr(char **arr)
{
	size_t	i;
	size_t	count;
	size_t	arr_len;
	char	**n_arr;

	i = 0;
	count = 0;
	n_arr = NULL;
	arr_len = ft_arrlen((void **)arr);
	if (arr_len <= 1)
		return (n_arr);
	while (arr[i])
	{
		if (arr[i][0] == '$' && arr[i][1] && ft_isalnum(arr[i][1]))
			count++;
		i++;
	}
	if (count != 0)
		n_arr = ft_calloc(arr_len - count + 1, sizeof(char *));
	return (n_arr);
}

static void	ft_args_dollar(t_object *task)
{
	char	**n_arr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	n_arr = ft_new_arr(task->cmd);
	if (!n_arr)
		return ;
	while (task->cmd[i])
	{
		if (task->cmd[i][0] != '$'
			|| (task->cmd[i][0] == '$'
			&& (!task->cmd[i][1] || !ft_isalnum(task->cmd[i][1]))))
		{
			n_arr[j] = task->cmd[i];
			j++;
		}
		else
			free(task->cmd[i]);
		i++;
	}
	free(task->cmd);
	task->cmd = n_arr;
}

void	ft_del_dollar(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		ft_args_dollar(parse->task[i]);
		i++;
	}
}

static void	ft_handle_str(char *s)
{
	size_t	i;
	size_t	j;
	int		inquote;

	i = 0;
	inquote = -1;
	while (s[i])
	{
		j = i;
		in_quote(s, &inquote, (int)i);
		if (s[i] == '$' && s[i + 1] && inquote == -1
			&& (s[i + 1] == '\'' || s[i + 1] == '"'))
		{
			while (s[j])
			{
				s[j] = s[j + 1];
				j++;
			}
			continue ;
		}
		i++;
	}
}

void	ft_clean_dollar(t_parse *parse)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd && parse->task[i]->cmd[j])
		{
			ft_handle_str(parse->task[i]->cmd[j]);
			j++;
		}
		i++;
	}
}
