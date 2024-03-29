/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objectify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:19:04 by tsadouk           #+#    #+#             */
/*   Updated: 2024/03/29 11:36:54 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_link	ft_get_link(char *cmd)
{
	if (ft_strcmp(cmd, "&&") == 0)
		return (AND);
	if (ft_strcmp(cmd, "||") == 0)
		return (OR);
	if (ft_strcmp(cmd, "|") == 0)
		return (PIPE);
	return (NO_LINK);
}

static t_priority	ft_get_priority(char *cmd)
{
	if (ft_strcmp(cmd, "&&") == 0 || ft_strcmp(cmd, "||") == 0)
		return (MEDIUM);
	if (!ft_strncmp(cmd, ">", 1) || !ft_strncmp(cmd, ">>", 2)\
		|| !ft_strncmp(cmd, "<", 1) || !ft_strncmp(cmd, "<<", 2))
		return (HIGH);
	return (LOW);
}

void	ft_objectify(t_parse *parse)
{
	size_t	i;
	size_t	j;
	size_t	k;
	t_object	*object;

	i = 0;
	j = 0;
	k = 0;
	object = malloc(sizeof(t_object) * ft_arrlen((void **)parse->cmd));
	while (parse->cmd[i])
	{
		object[j].cmd = ft_strtok(parse->cmd[i], " ");
		object[j].infile = -1;
		object[j].outfile = -1;
		object[j].link = PIPE;
		object[j].priority = LOW;
		j++;
		i++;
	}
	parse->cmd = object;
}
