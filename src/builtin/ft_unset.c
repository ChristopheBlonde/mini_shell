/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:24:36 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/29 16:10:30 by cblonde          ###   ########.fr       */
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
		return (ft_excmd_result(parse, 0));
	arr = (char **)ft_calloc(len, sizeof(char *));
	if (!arr)
		return (ft_excmd_result(parse, 1));
	if (!ft_cpy_env(parse, arr, index))
		return (ft_excmd_result(parse, 1));
	ft_free_array((void **)parse->env);
	parse->env = arr;
	ft_excmd_result(parse, 0);
}

static void	ft_invalid_option(t_parse *parse, char *option)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(option, 2);
	ft_putendl_fd(" :invalid option", 2);
	ft_excmd_result(parse, 2);
}

void	ft_exec_unset(t_parse *parse, t_object *task)
{
	size_t	i;
	bool	fail;

	i = 1;
	fail = false;
	if (task->builtin != UNSET)
		return ;
	if (!task->cmd || !task->cmd[i])
		return ;
	if (task->cmd[i][0] == '-')
	{
		ft_invalid_option(parse, task->cmd[i]);
		return ;
	}
	while (task->cmd[i])
	{
		ft_unset(parse, task->cmd[i]);
		if (!ft_strncmp(ft_getenv(parse, "?"), "1", -1))
			fail = true;
		i++;
	}
	if (fail)
		task->status = 1;
}
