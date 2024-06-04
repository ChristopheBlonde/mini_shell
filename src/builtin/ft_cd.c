/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:17:26 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/04 14:37:31 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_handle_cd_error(t_parse *parse, char *path, char **pwd,
		char **n_path)
{
	free(*pwd);
	*pwd = NULL;
	ft_excmd_result(parse, 1);
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	if (*n_path && ft_strncmp(*n_path, path, ft_strlen(*n_path)))
		free(*n_path);
}

void	ft_getcd_path(bool *modified, char **n_path, char **pwd, int *res)
{
	*modified = true;
	while (*n_path[0] == '/')
		*n_path += 1;
	*pwd = ft_strfjoin(*pwd, "/", 1);
	*n_path = ft_strfjoin(*pwd, *n_path, 0);
	*res = chdir(*n_path);
}

static void	ft_update_env(t_parse *parse, char *n_path,
		char *path, bool modified)
{
	char	*pwd;
	char	*result;

	if (modified)
		result = n_path;
	else
		result = path;
	pwd = ft_getenv(parse, "PWD");
	if (!ft_strncmp(result, pwd, ft_strlen(pwd)))
		return ;
	ft_export(parse, ft_strjoin("OLDPWD=", pwd));
	ft_export(parse, ft_strjoin("PWD=", result));
}

static bool	ft_error_cd(t_parse *parse, t_object *task, char *str)
{
	if (!str)
	{
		ft_excmd_result(parse, 1);
		return (true);
	}
	if (ft_arrlen((void **)task->cmd) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		ft_excmd_result(parse, 1);
		return (true);
	}
	return (false);
}

void	ft_cd(t_parse *parse, t_object *task, char *path)
{
	char	*pwd;
	int		res;
	char	*n_path;
	bool	modified;

	n_path = path;
	pwd = getcwd(NULL, 1024);
	modified = false;
	if (ft_error_cd(parse, task, pwd))
		return ;
	if (n_path[0] != '/')
		ft_getcd_path(&modified, &n_path, &pwd, &res);
	else
		res = chdir(path);
	if (res)
		return (ft_handle_cd_error(parse, path, &pwd, &n_path));
	free(pwd);
	ft_update_env(parse, n_path, path, modified);
	if (modified)
		free(n_path);
	return (ft_excmd_result(parse, 0));
}
