/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:29:40 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/24 16:45:47 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_quoted(char **s, t_elem *elem, size_t *index)
{
	char	*str;
	size_t	start;

	if (!ft_isalnum((*s)[*index + 1])
		&& ((*s)[*index + 1] != '?' && (*s)[*index + 1] != '_'))
		return ;
	str = ft_calloc(1, sizeof(char));
	if (!str)
		return ;
	str = ft_strfjoin(str, ft_substr(*s, 0, *index), 3);
	if (!str)
		return ;
	str = ft_strfjoin(str, elem->env, 1);
	if (!str)
		return ;
	start = *index + 1 + elem->var_len;
	str = ft_strfjoin(str, ft_substr(*s, start, ft_strlen(&(*s)[start])), 3);
	if (!str)
		return ;
	free(*s);
	*s = str;
	*index += ft_strlen(elem->env) - 1;
}

static void	ft_join_list(t_elem *elem, char *s, size_t index)
{
	t_list	*last;
	char	*tmp;
	size_t	start;

	tmp = NULL;
	start = index + 1 + elem->var_len;
	if (index != 0)
	{
		tmp = ft_substr(s, 0, index);
		if (!tmp)
			return ;
		elem->lst->content = ft_strfjoin(tmp, (char *)elem->lst->content, 3);
	}
	if (s[start])
	{
		last = ft_lstlast(elem->lst);
		tmp = ft_substr(s, start, ft_strlen(&s[start]));
		if (!tmp)
			return ;
		if (!elem->lst)
			ft_lstadd_back(&elem->lst, ft_lstnew(tmp));
		else
			last->content = ft_strfjoin(last->content, tmp, 3);
	}
}

static void	ft_handle_unquoted(t_he *he, t_elem *elem, char *s, size_t *index)
{
	char	**arr;
	ssize_t	i;
	char	*tmp;

	i = -1;
	arr = ft_split(elem->env, ' ');
	if (!arr)
		return ;
	while (arr[++i])
	{
		tmp = ft_strdup(arr[i]);
		if (!tmp)
		{
			ft_free_array((void **)arr);
			ft_lstclear(&elem->lst, free);
			return ;
		}
		ft_lstadd_back(&elem->lst, ft_lstnew(tmp));
	}
	ft_free_array((void **)arr);
	ft_join_list(elem, s, *index);
	ft_check_insertion(he, elem);
	*index += ft_strlen(elem->env) - 1;
	if (elem->env[0] == '\0')
		free(elem->env);
}

static void	ft_handle_dollar(t_parse *parse, t_he *he, t_elem *elem)
{
	size_t	i;

	i = 0;
	while (((char *)(he->cur->content))[i])
	{
		in_quote(((char *)(he->cur->content)), &elem->quoted, (int)i);
		if (((char *)(he->cur->content))[i] == '$'
			&& (elem->quoted == -1
				|| ((char *)(he->cur->content))[elem->quoted] == '"'))
		{
			ft_get_variable(parse, &((char *)(he->cur->content))[i + 1], elem);
			if (elem->quoted != -1
				&& ((char *)(he->cur->content))[elem->quoted] == '"')
				ft_handle_quoted((char **)&he->cur->content, elem, &i);
			else
			{
				ft_handle_unquoted(he, elem, (char *)(he->cur->content), &i);
				break ;
			}
		}
		i++;
	}
}

void	ft_handle_env(t_parse *parse, int k)
{
	int		i[2];
	t_he	he;

	i[0] = k;
	i[1] = 0;
	ft_init_he(&he, parse->task[i[0]]);
	if (!he.lst)
		return ;
	while (he.cur)
	{
		ft_init_elem(&he.info[i[1]]);
		he.cur_count = ft_count_dollar(he.cur->content);
		if (he.cur_count != 0)
			ft_handle_dollar(parse, &he, &he.info[i[1]]);
		if (he.cur_count == 0 && he.cur)
		{
			he.cur = he.cur->next;
			i[1]++;
		}
	}
	ft_lstto_arr(parse->task[i[0]], he.lst);
	free(he.info);
}

