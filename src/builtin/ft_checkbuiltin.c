/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkbuiltin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:47:35 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/20 14:15:47 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_check_builtin(t_object *task, char *cmd, size_t len)
{
	if (!cmd || !cmd[0])
		return ;
	if (!ft_strncmp(cmd, "echo", len) && len == 4)
		task->builtin = ECHO;
	else if (!ft_strncmp(cmd, "cd", len) && len == 2)
		task->builtin = CD;
	else if (!ft_strncmp(cmd, "pwd", len) && len == 3)
		task->builtin = PWD;
	else if (!ft_strncmp(cmd, "export", len) && len == 6)
		task->builtin = EXPORT;
	else if (!ft_strncmp(cmd, "unset", len) && len == 5)
		task->builtin = UNSET;
	else if (!ft_strncmp(cmd, "env", len) && len == 3)
		task->builtin = ENV;
	else if (!ft_strncmp(cmd, "exit", len) && len == 4)
		task->builtin = EXIT;
	else
		task->builtin = NO_BUILTIN;
}

void	ft_builtin(t_parse *parse)
{
	size_t	i;
	size_t	len;
	char	*cmd;

	i = 0;
	while (parse->task[i])
	{
		if (parse->task[i]->cmd)
			cmd = parse->task[i]->cmd[0];
		if (cmd)
			len = ft_strlen(cmd);
		ft_check_builtin(parse->task[i], cmd, len);
		i++;
	}
}
