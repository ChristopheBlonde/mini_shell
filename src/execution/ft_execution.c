/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:38:45 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/23 09:45:38 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_execution(t_parse *parse)
{
	if (!ft_strncmp(parse->input, "test", 4))
		ft_env_trim(parse->task[0]->cmd[1]);
	if (!ft_strncmp(parse->input, "clear", 5))
		write(STDOUT_FILENO, "\033[H\033[J", 7);
	if (!ft_strncmp(parse->input, "echo", 4))
		ft_exec_echo(parse, parse->task[0]);
	if (!ft_strncmp(parse->input, "export", 6))
		ft_exec_export(parse, parse->task[0]);
	if (!ft_strncmp(parse->input, "pwd", 3))
		ft_pwd(parse);
	if (!ft_strncmp(parse->input, "cd", 2))
		ft_cd(parse, parse->task[0]->cmd[1]);
	if (!ft_strncmp(parse->input, "exit", 4))
		return (false);
	return (true);
}

