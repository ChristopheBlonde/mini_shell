/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/23 09:30:01 by cblonde          ###   ########.fr       */
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
	ft_builtin(parse);
	ft_redirection(parse);
	ft_env_handler(parse);
	ft_wildcard(parse);
	ft_delete_quotes(parse);
	ft_free_array((void **)arr);
	return (true);
} //NORM
/*
	if (parse->redirect)
	{
		i = 0;
		while (parse->redirect[i])
		{
			ft_printf("enum:%d, quoted:%d, name:%s\n",
			parse->redirect[i]->type,
			parse->redirect[i]->in_quote, parse->redirect[i]->file);
			i++;
		}
	}
	i = 0;
	while (parse->task[i])
	{
		int j = 0;
		ft_printf("task[%d], input:%d, output:%d\n",
		i, parse->task[i]->infile, parse->task[i]->outfile);
		while (parse->task[i]->cmd[j])
		{
			ft_printf("task[%d], cmd[%d], value:%s\n", i,
			j, parse->task[i]->cmd[j]);
			j++;
		}
		i++;
	}
*/
