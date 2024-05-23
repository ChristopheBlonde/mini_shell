/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:10:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/23 17:20:57 by cblonde          ###   ########.fr       */
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

static bool	ft_syntax_env(char *env)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(env[0]) && env[0] != '_')
	{
		ft_error_env(env);
		return (false);
	}
	while (env[i] && env[i] != '=' && ft_strncmp(&env[i], "+=", 2))
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

void	ft_add_env(char **arr, size_t index, char *new)
{
	char	*name;
	size_t	i;
	size_t	len;

	name = ft_getkey_env(new);
	len = ft_strlen(name);
	i = len;
	if (new[len] == '+')
	{
		while (new[i])
		{
			new[i] = new[i + 1];
			i++;
		}
	}
	arr[index] = ft_strdup(new);
	free(name);
}

void	ft_export(t_parse *parse, char *new)
{
	size_t	len;
	size_t	i;
	char	**arr;

	if (!ft_syntax_env(new))
		return (ft_excmd_result(parse, 1));
	len = ft_arrlen((void **)parse->env);
	i = len;
	if (ft_replace_env(parse, new))
		return (ft_excmd_result(parse, 0));
	arr = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!arr)
		return (ft_excmd_result(parse, 1));
	if (!ft_cpy_env(parse, arr, len))
		return (ft_excmd_result(parse, 1));
	ft_add_env(arr, i, new);
	if (!arr[i])
	{
		ft_free_array((void **)arr);
		return (ft_excmd_result(parse, 1));
	}
	ft_free_array((void **)parse->env);
	parse->env = arr;
	ft_excmd_result(parse, 0);
}

void	ft_excmd_result(t_parse *parse, int n)
{
	char	*env;
	size_t	i;
	char	**arr;
	size_t	len;

	env = ft_strfjoin(ft_strdup("?="), ft_itoa(n), 3);
	if (!env)
		return ;
	len = ft_arrlen((void **)parse->env);
	i = len;
	if (ft_replace_env(parse, env))
	{
		free(env);
		return ;
	}
	arr = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!arr)
		return ;
	if (!ft_cpy_env(parse, arr, len))
		return ;
	arr[i] = env;
	ft_free_array((void **)parse->env);
	parse->env = arr;
}
