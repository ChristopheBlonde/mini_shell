/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:01:13 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/09 14:56:28 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static t_file_operation	ft_get_file_operation(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 1))
		return (WRITE);
	if (!ft_strncmp(cmd, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(cmd, "<", 1))
		return (READ);
	if (!ft_strncmp(cmd, "<<", 2))
		return (HEREDOC);
	return (NO_OP);
}

static bool	ft_is_redirect(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 1) || !ft_strncmp(cmd, ">>", 2)
		|| !ft_strncmp(cmd, "<", 1) || !ft_strncmp(cmd, "<<", 2))
		return (true);
	return (false);
}

static void	ft_fill_file_name(char **cmd, t_parse *parse, size_t *i)
{
	if (cmd[*i][0] == '>')
	{
		if (cmd [*i][1] != '\0')
			parse->redirect[*i]->file = ft_strdup(cmd[*i] + 1);
		else if (cmd[*i][1] == '>')
		{
			if (cmd[*i][2] != '\0')
				parse->redirect[*i]->file = ft_strdup(cmd[*i] + 2);
		}
		else
		{
			(*i)++;
			parse->redirect[*i]->file = ft_strdup(cmd[*i]);
		}
	}
	else if (cmd[*i][0] == '<')
	{
		if (cmd [*i][1] != '\0')
			parse->redirect[*i]->file = ft_strdup(cmd[*i] + 1);
		else if (cmd[*i][1] == '<')
		{
			if (cmd[*i][2] != '\0')
				parse->redirect[*i]->file = ft_strdup(cmd[*i] + 2);
		}
		else
		{
			(*i)++;
			parse->redirect[*i]->file = ft_strdup(cmd[*i]);
		}
	}
}*/
