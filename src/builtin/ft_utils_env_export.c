/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_env_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:18:30 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/23 17:22:28 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_export(t_parse *parse, t_object *task)
{
	size_t	i;

	i = 1;
	if (task->builtin != EXPORT)
		return ;
	if (!task->cmd[i])
		ft_putexport(parse->env);
	while (task->cmd[i])
	{
		ft_export(parse, task->cmd[i]);
		i++;
	}
}

void	ft_env_trim(char *str)
{
	int		i;
	int		j;
	size_t	count;
	int		start;

	i = -1;
	j = 0;
	count = 0;
	start = 0;
	while (str[++i] != '=')
	{
		start++;
		j++;
	}
	while (str[++i] == ' ')
		start++;
	while (str[++i])
		if (str[i] != ' ' || (i != 0 && str[i + 1] != ' '
				&& str[i + 1] != '\0' && str[i + 1] != '\n'))
			count++;
	while (str[++start])
		if (str[start] != ' ' || (i != 0 && str[start + 1] != '\0'
				&& str[start + 1] != ' ' && str[start + 1] != '\n'))
			str[++j] = str[start];
	str[++j] = '\0';
}
