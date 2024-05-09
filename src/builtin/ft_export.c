/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:10:47 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/27 09:56:34 by cblonde          ###   ########.fr       */
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

void	ft_export(t_parse *parse, char *new)
{
	size_t	len;
	size_t	i;
	char	**arr;

	len = ft_arrlen((void **)parse->env);
	i = len;
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

void	ft_putexport(char **env)
{
	char	**arr;
	size_t	i;

	i = 0;
	arr = ft_strsort_arr(env);
	if (!arr)
		return ;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(arr[i], 1);
		i++;
	}
	ft_free_array((void **)arr);
}
