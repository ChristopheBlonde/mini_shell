/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:10:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/16 16:57:36 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	ft_cpy_env(t_parse *parse, char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		arr[i] = ft_strdup(parse->env[i]);
		if (!arr[i])
		{
			ft_free_array((void **)arr);
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_exec_export(t_parse *parse, t_object *task)
{
	size_t	i;

	i = 1;
	if (task->builtin != EXPORT)
		return ;
	if (!task->cmd[i])
		ft_putexport(parse->env);
	while (task->cmd[i])
	{
		ft_export(parse, task->cmd[i]);
		i++;
	}
}

bool	ft_syntax_env(char *env)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(env[0]) && env[0] != '_')
	{
		ft_error_env(env);
		return (false);
	}
	while (env[i] && env[i] != '=')
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
		{
			ft_error_env(env);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_replace_env(t_parse *parse, char *new)
{
	char	*name;
	size_t	i;
	size_t	len;

	i = 0;
	name = ft_getkey_env(new);
	if (!name)
		return (true);
	len = ft_strlen(name);
	while (parse->env[i])
	{
		if (!ft_strncmp(parse->env[i], name, len))
		{
			free(parse->env[i]);
			parse->env[i] = ft_strdup(new);
			if (!parse->env[i])
				ft_putendl_fd("Error export", 2);
			free(name);
			return (true);
		}
		i++;
	}
	free(name);
	return (false);
}

void	ft_export(t_parse *parse, char *new)
{
	size_t	len;
	size_t	i;
	char	**arr;

	if (!ft_syntax_env(new))
		return ;
	len = ft_arrlen((void **)parse->env);
	i = len;
	if (ft_replace_env(parse, new))
		return ;
	arr = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!arr)
		return ;
	if (!ft_cpy_env(parse, arr, len))
		return ;
	arr[i] = ft_strdup(new);
	if (!arr[i])
	{
		ft_free_array((void **)arr);
		return ;
	}
	ft_free_array((void **)parse->env);
	parse->env = arr;
}
