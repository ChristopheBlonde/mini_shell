/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:32:29 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/27 09:59:26 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_build_env(void)
{
	char	**arr_env;

	arr_env = (char **)ft_calloc(4, sizeof(char *));
	if (!arr_env)
		return (NULL);
	arr_env[0] = ft_strdup("SHLVL=1");
	if (!arr_env[0])
	{
		ft_free_array((void **)arr_env);
		return (NULL);
	}
	arr_env[1] = ft_strfjoin("PWD=", getcwd(NULL, 4096), 2);
	if (!arr_env[1])
	{
		ft_free_array((void **)arr_env);
		return (NULL);
	}
	arr_env[2] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin");
	if (!arr_env[2])
	{
		ft_free_array((void **)arr_env);
		return (NULL);
	}
	return (arr_env);
}

static char	**ft_cpy_env(char **env, size_t len)
{
	char	**arr;
	size_t	i;

	i = 0;
	arr = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = ft_strdup(env[i]);
		if (!arr[i])
		{
			ft_free_array((void **)arr);
			return (NULL);
		}
		i++;
	}
	return (arr);
}

void	ft_parse_env(t_parse *parse, char *env[])
{
	char	**arr_env;
	size_t	len;

	len = 0;
	while (env[len])
		len++;
	if (len == 0)
	{
		arr_env = ft_build_env();
		if (!arr_env)
			return ;
	}
	else
	{
		arr_env = ft_cpy_env(env, len);
		if (!arr_env)
			return ;
	}
	parse->env = arr_env;
	ft_export(parse, "OLDPWD");
}
