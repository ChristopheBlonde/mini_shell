/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:25:46 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/07 14:13:03 by tsadouk          ###   ########.fr       */
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

t_list	*get_new(char *var, t_parse *parse, t_list *current, int z)
{
	if (var && var[0] == '\0')
		return (ft_list_to_split("$", parse, current, z));
	else
		return (ft_list_to_split(var, parse, current, z));
}

void	ft_process_env(t_object *task, t_parse *parse)
{
	t_list	*list;
	size_t	arr_len;

	list = NULL;
	arr_len = ft_arrlen((void **)task->cmd);
	task->unquoted = (bool *)ft_calloc(arr_len + 1, sizeof(bool));
	if (!task->unquoted)
		return ;
	list = ft_cmd_to_list_env(task, parse);
	ft_lstto_arr(task, list);
}

void	ft_env_handler(t_parse *parse)
{
	int		i;

	i = -1;
	while (parse->task[++i])
	{
		ft_process_env(parse->task[i], parse);
	}
}
