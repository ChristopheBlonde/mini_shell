/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:18:30 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/15 09:49:14 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_export(t_parse *parse, t_object *task)
{
	size_t	i;
	bool	fail;

	i = 1;
	fail = false;
	if (task->builtin != EXPORT)
		return ;
	if (!task->cmd[i])
		ft_putexport(parse->env);
	while (task->cmd[i])
	{
		ft_export(parse, task->cmd[i]);
		if (!strncmp(ft_getenv(parse, "?"), "1", -1))
			fail = true;
		i++;
	}
	if (fail)
		task->status = 1;
}
