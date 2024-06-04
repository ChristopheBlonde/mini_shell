/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:25:34 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/03 23:45:47 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_error_env(char *env)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(env, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

char	*ft_getkey_env(char *env)
{
	char	*key;
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=' && ft_strncmp("+=", &env[i], 2))
		i++;
	key = ft_substr(env, 0, i);
	if (!key)
		return (NULL);
	return (key);
}

void	ft_putexport(char **env)
{
	char	**arr;
	int		i;
	size_t	j;

	i = -1;
	arr = ft_strsort_arr(env);
	if (!arr)
		return ;
	while (arr[++i])
	{
		if (arr[i][0] == '?' || (arr[i][0] == '_' && arr[i][1] == '='))
			continue ;
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			j++;
		ft_putstr_fd("declare -x ", 1);
		write(1, arr[i], j + 1);
		if (arr[i][j] == '=')
			ft_putstr_fd("\"", 1);
		ft_putstr_fd(&arr[i][j + 1], 1);
		if (arr[i][j] == '=')
			ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
	}
	ft_free_array((void **)arr);
}

static bool	ft_replace_append(t_parse *parse, size_t i, char **name, char *new)
{
	if (new[ft_strlen(*name)] == '+')
	{
		parse->env[i] = ft_strfjoin(parse->env[i],
				&new[ft_strlen(*name) + 2], 1);
		if (!parse->env[i])
		{
			ft_putendl_fd("Error: export", 2);
			free(*name);
			return (false);
		}
	}
	else
	{
		free(parse->env[i]);
		parse->env[i] = ft_strdup(new);
		if (!parse->env[i])
		{
			ft_putendl_fd("Error export", 2);
			free(*name);
			return (false);
		}
		ft_env_trim(parse->env[i]);
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
		if (!ft_strncmp(parse->env[i], name, len)
			&& !ft_isalnum(parse->env[i][len]))
		{
			if (ft_replace_append(parse, i, &name, new))
			{
				free(name);
				return (true);
			}
		}
		i++;
	}
	free(name);
	return (false);
}
