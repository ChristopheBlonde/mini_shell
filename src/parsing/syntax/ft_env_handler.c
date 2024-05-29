/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:25:46 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/29 13:54:53 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_list_to_split(char *var, t_parse *parse,
	t_list *cur, int z)
{
	t_env_handler	e;
	t_stuff			*stuff;
	t_list			*new_list;

	stuff = (t_stuff *)malloc(sizeof(t_stuff));
	stuff->z = z;
	stuff->k = -1;
	stuff->var = var;
	new_list = NULL;
	e.env = ft_getenv(parse, var);
	e.var_end_size = ft_strlen(&((char *)cur->content)[z + 1 + ft_strlen(var)]);
	e.new_env = ft_split(e.env, ' ');
	e.new_env_len = ft_arrlen((void **)e.new_env);
	if (e.new_env_len > 1)
		while (++stuff->k < e.new_env_len)
			add_env_to_list(&new_list, cur, stuff, e);
	else if (e.new_env_len == 1)
		add_env_to_new_list(&new_list, cur, stuff, &e);
	ft_free_array((void **)e.new_env);
	free(stuff);
	return (new_list);
}

static t_list	*ft_list_to_add(t_list *current, t_parse *parse, int nb_dollar,
		int random)
{
	t_list	*new;
	int		z;
	int		index;
	char	*var;
	int		cur_dollar;

	cur_dollar = count_dollar(current->content) - nb_dollar + 1;
	z = -1;
	new = NULL;
	while (((char *)current->content)[++z])
	{
		if (((char *)current->content)[z] == '$' && (bool)++random)
		{
			if (random != cur_dollar)
				continue ;
			index = z + 1;
			ft_skip_envchar(current, &index);
			var = ft_substr(current->content, z + 1, index - z - 1);
			new = ft_list_to_split(var, parse, current, z);
			free(var);
			break ;
		}
	}
	return (new);
}

static t_list	*ft_cmd_to_list(t_object *task, t_parse *parse)
{
	t_cmd_lst	s;

	ft_init_cmd_lst(&s, task);
	while (s.current)
	{
		if (s.nb_dollar == 0)
		{
			s.nb_dollar = -1;
			s.current = s.current->next;
			continue ;
		}
		if (s.current != s.current_tmp)
			s.current_tmp = s.current;
		ft_cmd_quoted(parse, task, &s);
		if (task->is_quoted == 1)
			continue ;
		if (s.nb_dollar == -1)
			s.nb_dollar = count_dollar(s.current->content);
		if (s.nb_dollar > 0)
			ft_lstinsert(&s.lst, ft_list_to_add(s.current,
					parse, s.nb_dollar, 0), &s.current);
		if (s.nb_dollar > 0)
			s.nb_dollar -= 1;
	}
	return (s.lst);
}

void	ft_process_env(t_object *task, t_parse *parse)
{
	t_list	*list;

	list = NULL;
	list = ft_cmd_to_list(task, parse);
	ft_lstto_arr(task, list);
}

void	ft_env_handler(t_parse *parse)
{
	int		i;

	i = -1;
	while (parse->task[++i])
		ft_process_env(parse->task[i], parse);
}
