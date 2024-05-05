/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:43:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 16:40:15 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_wildcard(char *args)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = '\0';
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			if (quote == args[i])
				quote = '\0';
			else
				quote = args[i];
		}
		else if (args[i] == '*' && !quote)
			return (true);
		i++;
	}
	return (false);
}

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

void	ft_lstto_arr(t_object **task, t_list *lst, int i)
{
	size_t	j;
	size_t	lst_len;
	t_list	*tmp;
	char	**n_arr;

	j = 0;
	lst_len = ft_lstsize(lst);
	n_arr = (char **)ft_calloc(lst_len + 1, sizeof(char *));
	if (!n_arr)
	{
		ft_lstclear(&lst, free);
		return ;
	}
	while (lst)
	{
		n_arr[j] = lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
		j++;
	}
	free(lst);
	ft_free_array((void **)task[i]->cmd);
	task[i]->cmd = n_arr;
}

static t_list	*ft_cmd_to_list(t_object *task)
{
	t_list	*lst;
	t_list	*current;
	int		i;
	t_wc	*wc;

	i = -1;
	lst = NULL;
	while (task->cmd[++i])
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
		current = current->next;
		i++;
	}
	return (lst);
}

t_list	*ft_suppdouble(t_list *lst)
{
	t_list	*n_lst;
	t_list	*current;
	t_list	*tmp;
	bool	present;

	n_lst = NULL;
	tmp = lst;
	present = false;
	while (tmp)
	{
		current = n_lst;
		while (current)
		{
			if (!ft_strncmp(tmp->content, current->content,
				ft_strlen(tmp->content)))
				present = true;
			current = current->next;
		}
		if (!present)
			ft_lstadd_back(&n_lst, ft_lstnew(ft_strdup(tmp->content)));
		present = false;
		tmp = tmp->next;
	}
	ft_lstclear(&lst, free);
	return (n_lst);
}

void	ft_wildcard(t_parse *parse)
{
	size_t	i;
	t_list	*lst;

	lst = NULL;
	i = 0;
	while (parse->task[i])
	{
		lst = ft_cmd_to_list(parse->task[i]);
		//lst = ft_suppdouble(lst);
		ft_lstto_arr(parse->task, lst, i);
		i++;
	}
}
