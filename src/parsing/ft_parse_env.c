/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:32:29 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/25 17:01:40 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_free_tmp_env(char **tmp_env)
{
	if (!tmp_env)
		return ;
	if (tmp_env[0])
	{
		free(tmp_env[0]);
		tmp_env[0] = NULL;
	}
	if (tmp_env[1])
	{
		free(tmp_env[1]);
		tmp_env[1] = NULL;
	}
	free(tmp_env);
}

static void	ft_build_env(int fd)
{
	char	**tmp_env;
	t_env	*current;

	current = ft_calloc(1, sizeof(t_env *));
	if (!current)
		return ;
	current->full_env = ft_get_next_line(fd);
	current->full_env[ft_strlen(current->full_env) - 1] = '\0';
	tmp_env = ft_split(current->full_env, '=');
	if (!tmp_env)
		return ;
	current->name = ft_strdup(tmp_env[0]);
	if (!current->name)
		return ;
	tmp_env[1][ft_strlen(tmp_env[1]) - 1] = '\0';
	current->value = ft_strdup(tmp_env[1]);
	if (!current->value)
		return ;
	ft_free_tmp_env(tmp_env);
	tmp_env = NULL;
	ft_putendl_fd(current->name, 1);
	ft_putendl_fd(current->value, 1);
	ft_putendl_fd(current->full_env, 1);
}

char	**ft_parse_env(char *env[])
{
	char	**arr_env;
	//size_t	len;
	int		tube[2];
	pid_t	id;
	//char	*str;

	//len = 0;
	arr_env = env;
	pipe(tube);
	//str = NULL;
	//while (arr_env[len])
	//	len++;
	if (access("/bin/env", X_OK))
		return (NULL);
	id = fork();
	if (id < 0)
		ft_putendl_fd("Error: parsing env", 2);
	if (id == 0)
	{
		close(tube[0]);
		dup2(tube[1], 1);
		close(tube[1]);
		execve("/bin/env", env, NULL);
	}
	close(tube[1]);
	ft_build_env(tube[0]);
	//str = ft_get_next_line(tube[0]);
	//ft_putstr_fd(str, 1);
	//while (str)
	//{
	//	free(str);
	//	str = ft_get_next_line(tube[0]);
	//	if (str)
	//	{
	//		ft_putstr_fd("bien la ", 1);
	//		ft_putstr_fd(str, 1);
	//	}
	//}
	return (arr_env);
}
