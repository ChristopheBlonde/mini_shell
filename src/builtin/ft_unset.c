/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:24:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/17 13:08:43 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	ft_cpy_env(t_parse *parse, char **arr, int index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (parse->env[i])
	{
		if (i != (size_t)index)
		{
			arr[j] = ft_strdup(parse->env[i]);
			if (!arr[j])
			{
				ft_free_array((void **)arr);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static void	ft_unset(t_parse *parse, char *var)
{
	size_t	len;
	char	**arr;
	int		index;

	len = ft_arrlen((void **)parse->env);
	index = ft_get_index_env(parse->env, var, len);
	if (index < 0)
		return (ft_excmd_result(parse, 1));
	arr = (char **)ft_calloc(len, sizeof(char *));
	if (!arr)
		return (ft_excmd_result(parse, 1));
	if (!ft_cpy_env(parse, arr, index))
		return (ft_excmd_result(parse, 1));
	ft_free_array((void **)parse->env);
	parse->env = arr;
	ft_excmd_result(parse, 0);
}

void	ft_exec_unset(t_parse *parse, t_object *task)
{
	size_t	i;

	i = 1;
	if (task->builtin != UNSET)
		return ;
	if (!task->cmd || !task->cmd[i])
		return ;
	while (task->cmd[i])
	{
		ft_unset(parse, task->cmd[i]);
		i++;
	}
}
