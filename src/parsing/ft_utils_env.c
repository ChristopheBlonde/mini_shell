/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:31:33 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/19 15:12:19 by tsadouk          ###   ########.fr       */
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
}

void	ft_get_variable(t_parse *parse, char *s, t_elem *elem)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!s)
		return ;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
		i++;
	if (i == 0)
		return ;
	elem->var_len = i;
	tmp = ft_substr(s, 0, i);
	if (!tmp)
		return ;
	elem->env = ft_getenv(parse, tmp);
	if (!elem->env)
		elem->env = ft_calloc(1, sizeof(char));
	free(tmp);
}

int	is_quoted_single(char *str)
{
	if (!str)
		return (1);
	if (str[0] == '\'' && strchr(str, '\''))
		return (0);
	return (1);
}
