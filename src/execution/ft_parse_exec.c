/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <cblonde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:05:49 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/23 06:33:48 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_parse_befor_exec(t_parse *parse, size_t i)
{
	t_builtin	tmp;

	if (!ft_exec_redirect(parse, i))
		return (false);
	if (!parse->task[i]->cmd
		|| (parse->task[i]->cmd && !parse->task[i]->cmd[0]))
		return (false);
	tmp = parse->task[i]->builtin;
	ft_handle_env(parse, i);
	ft_wildcard(parse, i);
	if (parse->task[i]->cmd[0] && parse->task[i]->cmd[0][0] == '\0')
	{
		ft_putendl_fd("minishell: Command '' not found", 2);
		ft_excmd_result(parse, 127);
		return (false);
	}
	if (parse->task[i]->cmd[0] && parse->task[i]->cmd[0][0])
		ft_check_builtin(parse->task[i],
			parse->task[i]->cmd[0], ft_strlen(parse->task[i]->cmd[0]));
	if (parse->task[i]->builtin != tmp)
		return (false);
	ft_get_path(parse);
	if (parse->task[i]->infile != -1)
		ft_handle_heredoc_var(parse, parse->redirect[parse->task[i]->infile]);
	return (true);
}

char	*ft_quote_args(char *args)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 1;
	if (!args)
		return (NULL);
	tmp = ft_calloc(ft_strlen(args) + 2, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '"';
	while (args[++i])
		tmp[j++] = args[i];
	tmp[j] = '"';
	return (tmp);
}
