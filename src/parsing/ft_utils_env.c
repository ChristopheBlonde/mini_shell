/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:31:33 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/24 11:09:54 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_he(t_he *he, t_object *task)
{
	if (!task->cmd)
		return ;
	he->size = 0;
	he->lst = NULL;
	while (task->cmd[he->size])
	{
		ft_lstadd_back(&he->lst, ft_lstnew(ft_strdup(task->cmd[he->size])));
		he->size += 1;
	}
	if (!he->lst)
		return ;
	he->cur = he->lst;
	he->info = ft_calloc(he->size, sizeof(t_elem));
	if (!he->info)
	{
		ft_lstclear(&he->lst, free);
		return ;
	}
}

void	ft_init_elem(t_elem *elem)
{
	elem->lst = NULL;
	elem->env = NULL;
	elem->quoted = -1;
	elem->var_len = 0;
	elem->must_free = false;
}

void	ft_get_variable(t_parse *parse, char *s, t_elem *elem)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!s)
		return ;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_') && s[i] != '*')
		i++;
	if (s[i] == '?')
		i++;
	if (i == 0)
		return ;
	elem->var_len = i;
	tmp = ft_substr(s, 0, i);
	if (!tmp)
		return ;
	elem->env = ft_getenv(parse, tmp);
	if (!elem->env)
	{
		elem->env = ft_calloc(1, sizeof(char));
		elem->must_free = true;
	}
	free(tmp);
}

size_t	ft_count_dollar(char *s)
{
	size_t	i;
	int		quote;
	size_t	count;

	i = 0;
	quote = -1;
	count = 0;
	while (s && s[i])
	{
		in_quote(s, &quote, (int)i);
		if (s[i] == '$' && (quote == -1 || s[quote] == '"')
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '?'))
			count++;
		i++;
	}
	return (count);
}

void	ft_check_insertion(t_he *he, t_elem *elem)
{
	t_list	*prev;
	t_list	*tmp;

	tmp = he->cur;
	if (elem->lst)
		ft_lstinsert(&he->lst, elem->lst, &he->cur);
	else
	{
		if (he->lst == he->cur)
		{
			he->lst = he->lst->next;
		}
		else
		{
			prev = he->lst;
			while (prev->next != he->cur)
				prev = prev->next;
			prev->next = he->cur->next;
		}
		he->cur = he->cur->next;
		free(tmp->content);
		free(tmp);
	}
}
