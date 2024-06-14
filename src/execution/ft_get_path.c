/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:01:00 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/07 15:36:19 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_abs_path(char *path)
{
	int	res;

	res = access(path, X_OK);
	if (res == 0)
		return (true);
	return (false);
}

static char	**ft_get_env_path(t_parse *parse)
{
	char	**paths;
	char	*env_path;
	size_t	i;

	i = 0;
	env_path = ft_getenv(parse, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		paths[i] = ft_strfjoin(paths[i], "/", 1);
		if (!paths[i])
		{
			ft_free_array((void **)paths);
			return (NULL);
		}
		i++;
	}
	return (paths);
}

static void	ft_replace_path(t_object *task, char **paths)
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (task->cmd[j] && task->cmd[j][0] == '$')
		j++;
	if (!task || !task->cmd || !task->cmd[j])
		return ;
	if (ft_abs_path(task->cmd[j]))
		return ;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], task->cmd[j]);
		if (!path)
			continue ;
		if (!access(path, X_OK))
		{
			free(task->cmd[j]);
			task->cmd[j] = path;
		}
		else
			free(path);
	}
}

void	ft_get_path(t_parse *parse)
{
	char	**paths;
	int		i;

	i = -1;
	if (!parse->task)
		return ;
	paths = ft_get_env_path(parse);
	if (!paths)
		return ;
	while (parse->task[++i])
	{
		if (parse->task[i]->builtin == NO_BUILTIN)
			ft_replace_path(parse->task[i], paths);
	}
	ft_free_array((void **)paths);
}
