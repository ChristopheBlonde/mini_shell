/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:17:26 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 09:19:35 by cblonde          ###   ########.fr       */
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
	if (*n_path && ft_strncmp(*n_path, path, -1))
		free(*n_path);
}

void	ft_getcd_path(bool *modified, char **n_path, char **pwd, int *res)
{
	*modified = true;
	while (*n_path[0] == '/')
		*n_path += 1;
	if (!(*pwd))
		return ;
	*pwd = ft_strfjoin(*pwd, "/", 1);
	*n_path = ft_strfjoin(*pwd, *n_path, 0);
	*res = chdir(*n_path);
}

static void	ft_update_env(t_parse *parse, char *n_path,
		char *path, bool modified)
{
	char	*pwd;
	char	*result;
	char	*new_pwd;
	char	*old_pwd;

	if (modified)
		result = n_path;
	else
		result = path;
	pwd = ft_getenv(parse, "PWD");
	if (!ft_strncmp(result, pwd, -1))
		return ;
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	if (!old_pwd)
		return ;
	ft_export(parse, old_pwd);
	new_pwd = ft_strjoin("PWD=", result);
	if (!new_pwd)
	{
		free(old_pwd);
		return ;
	}
	ft_export(parse, new_pwd);
	free(old_pwd);
	free(new_pwd);
}

static bool	ft_error_cd(t_parse *parse, t_object *task)
{
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
	if (ft_error_cd(parse, task))
		return ;
	if (n_path[0] != '/' && ft_strncmp("./", n_path, 2)
		&& ft_strncmp("../", n_path, 3))
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
