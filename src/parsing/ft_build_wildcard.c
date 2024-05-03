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
typedef struct s_wc
{
	char	*start;
	char	*end;
	t_list	*middle;
	int		i;
	int		quote;
	size_t	len;
}	t_wc;

t_wc	*ft_init_wc(void)
{
	t_wc	*wc;

	wc = (t_wc *)ft_calloc(1, sizeof(t_wc));
	if (!wc)
		return (NULL);
	wc->start = NULL;
	wc->middle = NULL;
	wc->end	= NULL;
	wc->i = -1;
	wc->quote = -1;
	wc->len = 0;
	return (wc);
}

bool	ft_check_wildcard(char *args)
{
	size_t	i;
	char quote;

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

size_t	ft_getsize(char *str)
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

t_wc	*ft_wc_template(char *str)
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

void	ft_print_wc(t_wc *wc)
{
	t_list	*current;

	current = wc->middle;
	ft_putstr_fd("start: ", 1);
	if (wc->start)
		ft_putendl_fd(wc->start, 1);
	else
		ft_putendl_fd("NULL", 1);
	while (current)
	{
		ft_putstr_fd("middle: ", 1);
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
	ft_putstr_fd("end: ", 1);
	if (wc->end)
		ft_putendl_fd(wc->end, 1);
	else
		ft_putendl_fd("NULL", 1);
}

void	ft_unquote(t_wc *wc)
{
	t_list *current;

	current = wc->middle;
	if (wc->start && ft_quoted(wc->start))
		wc->start = ft_strqcpy(wc->start);
	if (wc->end && ft_quoted(wc->end))
		wc->end = ft_strqcpy(wc->end);
	while (current)
	{
		if (ft_quoted(current->content))
			current->content = ft_strqcpy(current->content);
		current = current->next;
	}
}

t_list	*ft_cmd_to_list(t_object *task)
{
	t_list	*lst;
	t_list	*current;
	int		i;
	t_wc	*wc;

	i = -1;
	lst = NULL;
	while (task->cmd[++i])
		ft_lstadd_back(&lst, ft_lstnew((void *)task->cmd[i]));
	current = lst;
	while (current)
	{
		if (ft_check_wildcard((char *)current->content))
		{
			wc = ft_wc_template((char *)current->content);
			//ft_unquote(wc);
			ft_print_wc(wc);
		}
		current = current->next;
	}
	return (lst);
}

void	ft_wildcard(t_parse *parse)
{
	ft_cmd_to_list(parse->task[0]);

}
