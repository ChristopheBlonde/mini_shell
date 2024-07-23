/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/22 17:29:23 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_getsize(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (str[i] == quote)
				quote = '\0';
			else
				quote = str[i];
		}
		if (!quote && str[i] == '*')
			return (i);
		i++;
	}
	return (i);
}

static t_wc	*ft_wc_template(char *str)
{
	t_wc	*wc;

	wc = ft_init_wc();
	while (str[++wc->i])
	{
		in_quote(str, &wc->quote, wc->i);
		if (wc->i == 0 && str[wc->i] != '*')
		{
			wc->len = ft_getsize(&str[wc->i]);
			wc->start = ft_substr(str, 0, wc->len);
		}
		else if (wc->quote == -1 && str[wc->i] == '*')
		{
			while (str[wc->i] == '*')
				wc->i++;
			wc->len = ft_getsize(&str[wc->i]);
			if (str[wc->i + wc->len] == '\0' && wc->len > 0)
				wc->end = ft_substr(str, wc->i, wc->len);
			else if (wc->len > 0)
				ft_lstadd_back(&wc->middle,
					ft_lstnew(ft_substr(str, wc->i, wc->len)));
			wc->i += wc->len - 1;
		}
	}
	return (wc);
}

static t_list	*ft_cmd_to_list(t_object *task)
{
	t_list	*lst;
	t_list	*current;
	int		i;
	t_wc	*wc;

	i = -1;
	lst = NULL;
	while (task->cmd[++i] && task->cmd[i][0])
		ft_lstadd_back(&lst, ft_lstnew((void *)ft_strdup(task->cmd[i])));
	current = lst;
	i = 0;
	while (current)
	{
		if (ft_check_wildcard((char *)current->content))
		{
			wc = ft_wc_template((char *)current->content);
			ft_unquote(wc);
			ft_lstinsert(&lst, ft_listdir(wc), &current);
		}
		else
			ft_strqcpy((char *)current->content);
		current = current->next;
		i++;
	}
	return (lst);
}

void	ft_wildcard(t_parse *parse, int i)
{
	t_list	*lst;

	lst = NULL;
	lst = ft_cmd_to_list(parse->task[i]);
	ft_lstto_arr(parse->task[i], lst);
}
