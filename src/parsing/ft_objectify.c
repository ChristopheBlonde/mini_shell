/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objectify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:04 by tsadouk           #+#    #+#             */
/*   Updated: 2024/07/20 22:16:58 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_rewrite_cmd(char **arr, char *str, size_t *index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	if (str[0] == '\0')
	{
		free(str);
		i = *index - 1;
		while (arr[++i])
			arr[i] = arr[i + 1];
		return ;
	}
	(*index)++;
}

static void	ft_delete_parentheses(t_object *task)
{
	size_t	i;
	size_t	j;
	size_t	cmd_len;

	i = 0;
	while (task->cmd && task->cmd[i])
	{
		j = i;
		cmd_len = ft_strlen(task->cmd[i]);
		if (cmd_len == 1
			&& (task->cmd[i][0] == '(' || task->cmd[i][0] == ')'))
		{
			free(task->cmd[i]);
			while (task->cmd[j])
			{
				task->cmd[j] = task->cmd[j + 1];
				j++;
			}
			continue ;
		}
		else if (task->cmd[i][0] == '(' || task->cmd[i][cmd_len - 1] == ')')
			ft_rewrite_cmd(task->cmd, task->cmd[i], &i);
		else
			i++;
	}
}

void	ft_objectify(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		if (!parse->task[i]->cmd[0])
			return ;
		if (!ft_strncmp(parse->task[i]->cmd[0], "||", 2))
			parse->task[i]->link = OR;
		else if (!ft_strncmp(parse->task[i]->cmd[0], "|", 1))
			parse->task[i]->link = PIPE;
		else if (!ft_strncmp(parse->task[i]->cmd[0], "&&", 2))
			parse->task[i]->link = AND;
		else
			parse->task[i]->link = NO_LINK;
		ft_clean_operator(parse->task[i]);
		ft_delete_parentheses(parse->task[i]);
		i++;
	}
}

static size_t	ft_get_lvl_parentheses(t_object *task, size_t lvl)
{
	int	count;
	int	i;
	int	j;
	int	quote;

	count = 0;
	i = -1;
	quote = -1;
	while (task->cmd[++i])
	{
		j = -1;
		while (task->cmd[i][++j])
		{
			in_quote(task->cmd[i], &quote, j);
			if (quote == -1 && task->cmd[i][j] == '(')
				task->open++;
			if (quote == -1 && task->cmd[i][j] == '(')
				count++;
			if (quote == -1 && task->cmd[i][j] == ')')
				task->close++;
			if (quote == -1 && task->cmd[i][j] == ')')
				count--;
		}
	}
	return ((int)lvl + count);
}

void	ft_get_priority(t_parse *parse)
{
	size_t	i;
	size_t	lvl;
	size_t	prev_lvl;

	i = 0;
	lvl = 0;
	prev_lvl = 0;
	while (parse->task[i])
	{
		lvl = ft_get_lvl_parentheses(parse->task[i], lvl);
		if (lvl > prev_lvl)
			parse->task[i]->lvl = lvl;
		else
			parse->task[i]->lvl = prev_lvl;
		prev_lvl = lvl;
		i++;
	}
}
