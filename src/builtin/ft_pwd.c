/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:15:06 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/24 14:47:39 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(t_parse *parse)
{
	char	pwd[4096];

	pwd[0] = '\0';
	getcwd(pwd, 4096);
	if (!pwd[0])
	{
		perror("pwd: error retrieving current directory:\
 getcwd: cannot access parent directories");
		ft_excmd_result(parse, 1);
		return ;
	}
	ft_putendl_fd(pwd, 1);
	ft_excmd_result(parse, 0);
}
