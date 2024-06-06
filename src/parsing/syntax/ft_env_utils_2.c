/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:29:31 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/06 13:46:09 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	case_if_0(t_cmd_lst *s)
{
	if (s->nb_dollar == 0)
	{
		s->nb_dollar = -1;
		s->current = s->current->next;
		return (true);
	}
	return (false);
}

static bool	case_if_1_or_2(t_cmd_lst *s, t_object *task, size_t *k)
{
	if (task->is_quoted == 1)
	{
		task->unquoted[*k] = false;
		s->nb_dollar = 0;
		return (true);
	}
	else if (task->is_quoted == 2)
	{
		task->unquoted[*k] = true;
		s->nb_dollar = 0;
		return (true);
	}
	return (false);
}

static void	handle_new_unquoted(t_cmd_lst s, t_object *task, size_t j,
	t_list *new_lst)
{
	bool	*new_unquoted;

	new_unquoted = (bool *)ft_calloc(s.i + ft_lstsize(new_lst), sizeof(bool));
	if (!new_unquoted)
		return ;
	while (task->unquoted[j])
	{
		new_unquoted[j] = task->unquoted[j];
		j--;
	}
	while (j < (s.i + (size_t)ft_lstsize(new_lst)))
		new_unquoted[j++] = true;
	free(task->unquoted);
	task->unquoted = new_unquoted;
}

static void	process_nb_dollar(t_cmd_lst *s, t_object *task, t_parse *parse,
	size_t j)
{
	t_list	*new_lst;

	if (s->nb_dollar == -1)
		s->nb_dollar = count_dollar(s->current->content);
	if (s->nb_dollar > 0)
	{
		new_lst = ft_list_to_add(s->current, parse, s->nb_dollar, 0);
		handle_new_unquoted(*s, task, j, new_lst);
		ft_lstinsert(&s->lst, new_lst, &s->current);
		s->nb_dollar -= 1;
	}
}

t_list	*ft_cmd_to_list_env(t_object *task, t_parse *parse)
{
	t_cmd_lst	s;
	size_t		j;
	size_t		k;

	j = 0;
	k = 0;
	ft_init_cmd_lst(&s, task);
	while (s.current)
	{
		if (case_if_0(&s))
			continue ;
		if (s.current != s.current_tmp)
			s.current_tmp = s.current;
		ft_cmd_quoted(parse, task, &s);
		if (case_if_1_or_2(&s, task, &k))
			continue ;
		process_nb_dollar(&s, task, parse, j);
		k++;
	}
	return (s.lst);
}
