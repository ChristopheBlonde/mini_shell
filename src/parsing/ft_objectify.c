/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objectify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:04 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/30 12:17:23 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_link	ft_get_link(char *cmd)
{
	if (!ft_strncmp(cmd, "&&", 2))
		return (AND);
	if (!ft_strncmp(cmd, "||", 2))
		return (OR);
	if (!ft_strncmp(cmd, "|", 1))
		return (PIPE);
	return (NO_LINK);
}

static t_priority	ft_get_priority(char *cmd)
{
	if (!ft_strncmp(cmd, "&&", 2) || !ft_strncmp(cmd, "||", 2))
		return (MEDIUM);
	if (!ft_strncmp(cmd, ">", 1) || !ft_strncmp(cmd, ">>", 2)
		|| !ft_strncmp(cmd, "<", 1) || !ft_strncmp(cmd, "<<", 2))
		return (HIGH);
	return (LOW);
}

void	ft_objectify(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		parse->task[i]->link = ft_get_link(parse->task[i]->cmd[0]);
		parse->task[i]->priority = ft_get_priority(parse->task[i]->cmd[0]);
		i++;
	}
}
