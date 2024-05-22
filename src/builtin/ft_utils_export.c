/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:25:34 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/22 17:56:29 by tsadouk          ###   ########.fr       */
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
	while (env[i] && env[i] != '=')
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
		if (arr[i][0] == '?')
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
			ft_env_trim(parse->env[i]);
			free(name);
			return (true);
		}
		i++;
	}
	free(name);
	return (false);
}

void	ft_env_trim(char *str)
{
	int		i;
	int		j;
	size_t	count;
	int		start;

	i = -1;
	j = 0;
	count = 0;
	start = 0;
	while (str[++i] != '=')
	{
		start++;
		j++;
	}
	while (str[++i] == ' ')
		start++;
	while (str[++i])
		if (str[i] != ' ' || (i != 0 && str[i + 1] != ' '
					&& str[i + 1] != '\0' && str[i + 1] != '\n'))
			count++;
	while (str[++start])
		if (str[start] != ' ' || (i != 0 && str[start + 1] != '\0'
					&& str[start + 1] != ' ' && str[start + 1] != '\n'))
			str[++j] = str[start];
	str[++j] = '\0';
}
