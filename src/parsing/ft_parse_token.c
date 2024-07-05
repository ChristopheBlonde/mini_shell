/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/04 12:17:59 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_token(t_parse *parse, char *input)
{
	char	**arr;

	arr = ft_strtok(input, "|&\n");
	if (!arr)
		return (false);
	if (!ft_init_tasks(parse, arr))
	{
		ft_free_array((void **)arr);
		return (false);
	}
	// for (int i = 0; parse->task[i]; i++)
	// {
	// 	for (int j = 0; parse->task[i]->cmd[j]; j++)
	// 	{
	// 		printf("task[%d]->cmd[%d] = %s\n", i, j, parse->task[i]->cmd[j]);
	// 	}
	// }
	ft_get_priority(parse);
	ft_objectify(parse);
	ft_redirection(parse);
	ft_clean_dollar(parse);
	ft_builtin(parse);
	ft_free_array((void **)arr);
	return (true);
}
