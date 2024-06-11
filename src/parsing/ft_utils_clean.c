/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:09:23 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/11 12:10:06 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_envvar(t_parse *parse, t_object *task, size_t index)
{
	char	*env;

	if (task->cmd[index] && task->cmd[index][0] == '$')
	{
		env = ft_getenv(parse, &task->cmd[index][1]);
		if ((index == 0 || task->cmd[index - 1] == NULL) && env == NULL)
		{
			free(task->cmd[index]);
			task->cmd[index] = NULL;
			return (true);
		}
	}
	return (false);
}
