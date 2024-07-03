/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:15:06 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/03 08:59:47 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(t_parse *parse)
{
	char	*pwd;

	pwd = getcwd(NULL, 1024);
	if (!pwd)
	{
		perror("pwd: error retrieving current directory:\
 getcwd: cannot access parent directories");
		ft_excmd_result(parse, 1);
		return ;
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	ft_excmd_result(parse, 0);
}
