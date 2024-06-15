/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/14 18:52:01 by cblonde          ###   ########.fr       */
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
	ft_objectify(parse);
	ft_redirection(parse);
	ft_env_handler(parse);
	int i = -1;
	while (parse->task[++i])
	{
		int j = -1;
		while (parse->task[i]->cmd[++j])
			ft_putendl_fd(parse->task[i]->cmd[j], 1);
	}
	ft_builtin(parse);
	ft_wildcard(parse);
	ft_delete_quotes(parse);
	ft_del_dollar(parse);
	ft_free_array((void **)arr);
	return (true);
}
