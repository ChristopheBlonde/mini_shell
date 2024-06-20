/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:31:33 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/21 00:48:45 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_he(t_he *he, t_object *task)
{
	if (!task->cmd)
		return ;
	he->size = 0;
	he->lst = NULL;
	he->cur_count = 0;
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
	pid_t	pid;
	char	pid_str[12];

	i = 0;
	tmp = NULL;
	if (!s)
		return ;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	if (s[i] == '?') {
		i++;
	}
	while (s[i] == '$') {
		i++;
	}
	if (i == 0 && s[i + 1] != '$') {
		return ;
	}
	elem->var_len = i;
	tmp = ft_substr(s, 0, i);
	if (!tmp) {
		return ;
	}
	if (s[0] == '$') {
		pid = getpid();
		snprintf(pid_str, sizeof(pid_str), "%d", pid);
		elem->env = strdup(pid_str);
		i = 1;
		while (s[i])
		{
			if (s[i] == '$' && s[i + 1] == '$')
			{
				elem->env = ft_strjoin(elem->env, pid_str);
				i += 2;
				continue ;
			}
			if (s[i] == '$' && s[i + 1] != '$')
			{
				elem->env = ft_strjoin(elem->env, "$");
				i++;
				continue ;
			}
			i++;
		}
	} else {
		elem->env = ft_getenv(parse, tmp);
		if (!elem->env) {
			elem->env = ft_calloc(1, sizeof(char));
		}
	}
	free(tmp);
}

// TODO : fix echo "$$", $ + un truc qui existe pas
