/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:17:26 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/24 14:46:59 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_handle_cd_error(t_parse *parse, char *path, char **n_path)
{
	ft_excmd_result(parse, 1);
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	if (*n_path && ft_strncmp(*n_path, path, -1))
		free(*n_path);
}

static void	ft_getcd_path(bool *modified, char **n_path, char pwd[4096], int *res)
{
	char	*tmp;

	tmp = NULL;
	*modified = true;
	while (*n_path[0] == '/')
		*n_path += 1;
	if (!pwd[0])
		return ;
	tmp = ft_strjoin(pwd, "/");
	if (!tmp)
		return ;
	*n_path = ft_strfjoin(tmp, *n_path, 1);
	*res = chdir(*n_path);
}

static void	ft_update_env(t_parse *parse, char *pwd)
{
	char	*new_pwd;
	char	*old_pwd;
	char	n_pwd[4096];

	n_pwd[0] = '\0';
	getcwd(n_pwd, 4096);
	if (!n_pwd[0])
		return ;
	if (!ft_strncmp(ft_getenv(parse, "PWD"), n_pwd, -1))
		return ;
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	if (!old_pwd)
		return ;
	ft_export(parse, old_pwd);
	free(old_pwd);
	new_pwd = ft_strjoin("PWD=", n_pwd);
	if (!new_pwd)
		return ;
	ft_export(parse, new_pwd);
	free(new_pwd);
}

static bool	ft_error_cd(t_parse *parse, t_object *task, char *pwd)
{
	size_t	arr_len;
	char	*home;

	arr_len = ft_arrlen((void **)task->cmd);
	if (arr_len > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		ft_excmd_result(parse, 1);
		return (true);
	}
	else if (arr_len < 2)
	{
		home = ft_getenv(parse, "HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			ft_excmd_result(parse, 1);
			return (true);
		}
		chdir(home);
		ft_update_env(parse, pwd);
		ft_excmd_result(parse, 0);
		return (true);
	}
	return (false);
}

void	ft_cd(t_parse *parse, t_object *task, char *path)
{
	char	pwd[4096];
	int		res;
	char	*n_path;
	bool	modified;

	n_path = path;
	pwd[0] = '\0';
	getcwd(pwd, 4096);
	if (!pwd[0])
		return ;
	modified = false;
	if (ft_error_cd(parse, task, pwd))
		return ;
	res = 1;
	if (n_path[0] != '/' && ft_strncmp("./", n_path, 2)
		&& ft_strncmp("../", n_path, 3))
		ft_getcd_path(&modified, &n_path, pwd, &res);
	else
		res = chdir(path);
	if (res)
		return (ft_handle_cd_error(parse, path, &n_path));
	ft_update_env(parse, pwd);
	if (modified)
		free(n_path);
	return (ft_excmd_result(parse, 0));
}
