/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/10 09:38:01 by cblonde          ###   ########.fr       */
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
/*	int i = 0, j;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			ft_putstr_fd("task: ", 1);
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" cmd: ", 1);
			ft_putnbr_fd(j, 1);
			ft_putstr_fd(" value: ", 1);
			ft_putendl_fd(parse->task[i]->cmd[j], 1);
			j++;
		}
		i++;
	}*/
	ft_redirection(parse);
	ft_env_handler(parse);
	ft_objectify(parse);
	ft_builtin(parse);
	ft_wildcard(parse);
	ft_delete_quotes(parse);
	ft_free_array((void **)arr);
	return (true);
}
