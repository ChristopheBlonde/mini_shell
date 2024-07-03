/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:25:34 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 11:53:10 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	}
	return (true);
}

static bool	ft_del_append(t_parse *parse, char *name, char *new, size_t i)
{
	size_t	len;

	len = ft_strlen(name);
	if (new[len] && new[len] == '=' && !new[len + 1])
	{
		parse->env[i][len + 1] = '\0';
		free(name);
		return (true);
	}
	if (!new[len] && parse->env[i][len] == '=')
	{
		free(name);
		return (true);
	}
	if (ft_replace_append(parse, i, &name, new))
	{
		free(name);
		return (true);
	}
	return (false);
}

bool	ft_replace_env(t_parse *parse, char *new)
{
	char	*name;
	size_t	i;
	size_t	len;	

	name = ft_getkey_env(new);
	if (!name)
		return (true);
	len = ft_strlen(name);
	i = 0;
	while (parse->env[i])
	{
		if (!ft_strncmp(parse->env[i], name, len)
			&& !ft_isalnum(parse->env[i][len]))
		{
			if (ft_del_append(parse, name, new, i))
				return (true);
		}
		i++;
	}
	free(name);
	return (false);
}
