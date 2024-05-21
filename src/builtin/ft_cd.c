/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:17:26 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/21 13:25:13 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_handle_cd_error(t_parse *parse, char *path, char **pwd,
		char **n_path)
{
	free(*pwd);
	*pwd = NULL;
	if (*n_path)
		free(*n_path);
	ft_excmd_result(parse, 1);
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
}

void	ft_getcd_path(bool *modified, char **n_path, char **pwd, int *res)
{
	*modified = true;
	while (*n_path[0] == '.' || *n_path[0] == '/')
		*n_path += 1;
	*pwd = ft_strfjoin(*pwd, "/", 1);
	*n_path = ft_strfjoin(*pwd, *n_path, 0);
	*res = chdir(*n_path);
}

void	ft_cd(t_parse *parse, char *path)
{
	char	*pwd;
	int		res;
	char	*n_path;
	bool	modified;

	n_path = path;
	pwd = getcwd(NULL, 1024);
	modified = false;
	if (!pwd)
	{
		ft_excmd_result(parse, 1);
		return ;
	}
	if (n_path[0] != '/')
		ft_getcd_path(&modified, &n_path, &pwd, &res);
	else
		res = chdir(pwd);
	if (res)
		return (ft_handle_cd_error(parse, path, &pwd, &n_path));
	free(pwd);
	if (modified)
		free(n_path);
	return (ft_excmd_result(parse, 0));
}
