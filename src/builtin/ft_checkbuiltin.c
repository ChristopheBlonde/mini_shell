/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkbuiltin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:47:35 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/09 18:48:34 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	ft_check_builtin(t_object *task, char *cmd, size_t len)
{
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd, "echo", len))
		task->builtin = ECHO;
	else if (!ft_strncmp(cmd, "cd", len))
		task->builtin = CD;
	else if (!ft_strncmp(cmd, "pwd", len))
		task->builtin = PWD;
	else if (!ft_strncmp(cmd, "export", len))
		task->builtin = EXPORT;
	else if (!ft_strncmp(cmd, "unset", len))
		task->builtin = UNSET;
	else if (!ft_strncmp(cmd, "env", len))
		task->builtin = ENV;
	else if (!ft_strncmp(cmd, "exit", len))
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
