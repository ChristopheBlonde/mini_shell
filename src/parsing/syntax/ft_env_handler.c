/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42angouleme.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:25:46 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/21 14:46:08 by tsadouk          ###   ########.fr       */
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
			index = z;
			while (((char *)current->content)[index] &&
				((char *)current->content)[index] != ' ' &&
				((char *)current->content)[index] != '"')
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
		ft_lstadd_back(&lst, ft_lstnew((void *)ft_strdup(task->cmd[i])));
	current = lst;
	while (current)
	{
		if (((char*)current->content)[0] == '\'')
		{
			current = current->next;
			continue ;
			
		}
		current->content = ft_strqcpy((char *)current->content);
		if (check_if_dollar(current->content))
			ft_lstinsert(&lst, ft_list_to_add(current, parse), &current);
		if (!check_if_dollar(current->content))
			current = current->next;
		else
			current = current->next;
	}
	return (lst);
}

// static void	ft_lstto_arr(t_object **task, t_list *lst, int i)
// {
// 	size_t	j;
// 	size_t	lst_len;
// 	t_list	*tmp;
// 	char	**n_arr;

// 	j = 0;
// 	lst_len = ft_lstsize(lst);
// 	n_arr = (char **)ft_calloc(lst_len + 1, sizeof(char *));
// 	if (!n_arr)
// 	{
// 		ft_lstclear(&lst, free);
// 		return ;
// 	}
// 	while (lst)
// 	{
// 		n_arr[j] = lst->content;
// 		tmp = lst;
// 		lst = lst->next;
// 		free(tmp);
// 		j++;
// 	}
// 	free(lst);
// 	ft_free_array((void **)task[i]->cmd);
// 	task[i]->cmd = n_arr;
// }

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
