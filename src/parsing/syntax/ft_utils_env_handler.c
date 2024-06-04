/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:01:18 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/03 23:03:07 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cmd_lst(t_cmd_lst *s, t_object *task)
{
	s->nb_dollar = -1;
	s->i = 0;
	s->lst = NULL;
	while (task->cmd[s->i])
	{
		ft_lstadd_back(&s->lst, ft_lstnew(ft_strdup(task->cmd[s->i])));
		s->i += 1;
	}
	s->current = s->lst;
	s->current_tmp = s->lst;
}

void	ft_cmd_quoted(t_parse *parse, t_object *task, t_cmd_lst *s)
{
	char	*str;
	char	*var;

	var = NULL;
	if (((char *)s->current->content)[0] == '\'')
	{
		task->is_quoted = 1;
		s->current = s->current->next;
		return ;
	}
	if (((char *)s->current->content)[0] == '"')
	{
		task->is_quoted = 2;
		s->current->content = ft_strqcpy((char *)s->current->content);
		str = (char *)ft_calloc(1, sizeof(char));
		if (!str)
			return ;
		str = ft_replace_var(parse, s->current->content, str, var);
		free(s->current->content);
		s->current->content = str;
	}
}

void	ft_skip_envchar(t_list *current, int *i)
{
	while (((char *)current->content)[*i] &&
		((char *)current->content)[*i - 1] != '?' &&
		((char *)current->content)[*i] != ' ' &&
		((char *)current->content)[*i] != '"' &&
		((char *)current->content)[*i] != '$' &&
		((char *)current->content)[*i] != '\'' &&
		((char *)current->content)[*i] != '\n')
		*i += 1;
}
