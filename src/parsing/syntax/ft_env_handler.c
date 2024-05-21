/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:25:46 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/21 20:13:47 by tsadouk          ###   ########.fr       */
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

static t_list	*ft_list_to_add(t_list *current, t_parse *parse)
{
	t_list	*new;
	int		z;
	int		index;
	char	*var;

	z = -1;
	while (((char *)current->content)[++z])
	{
		if (((char *)current->content)[z] == '$')
		{
			index = z + 1;
			while (((char *)current->content)[index] &&
				((char *)current->content)[index] != ' ' &&
				((char *)current->content)[index] != '"' &&
				((char *)current->content)[index] != '$' &&
				((char *)current->content)[index] != '\n')
				index++;
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
	t_list	*lst;
	t_list	*current;
	int		i;

	i = -1;
	lst = NULL;
	while (task->cmd[++i])
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(task->cmd[i])));
	current = lst;
	while (current)
	{
		if (((char *)current->content)[0] == '\'')
			current = current->next;
		if (((char *)current->content)[0] == '\'')
			continue ;
		if (((char *)current->content)[0] == '"')
			current->content = ft_strqcpy((char *)current->content);
		if (check_if_dollar(current->content))
			ft_lstinsert(&lst, ft_list_to_add(current, parse), &current);
		if (!check_if_dollar(current->content))
			current = current->next;
		else
			continue ;
	}
	return (lst);
}

void	ft_env_handler(t_parse *parse)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = -1;
	while (parse->task[++i])
	{
		list = ft_cmd_to_list(parse->task[i], parse);
		ft_lstto_arr(parse->task, list, i);
	}
}
