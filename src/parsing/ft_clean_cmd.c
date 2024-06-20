/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:13:34 by cblonde           #+#    #+#             */
/*   Updated: 2024/06/20 15:40:59 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_check_redirect(char *str)
{
	t_file_operation	type;

	if (!str)
		return (0);
	type = ft_redirect_type(str);
	if (type == NO_OP)
		return (0);
	if (type == APPEND || type == HEREDOC)
	{
		if (str[2] == '\0')
			return (2);
		else
			return (1);
	}
	else
	{
		if (str[1] == '\0')
			return (2);
		else
			return (1);
	}
}

static void	ft_rewrite(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j] == '|' || str[j] == '&')
		j++;
	while (str[j])
	{
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

static size_t	ft_check_link(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '|' || str[0] == '&')
	{
		if (str[1] == '\0')
			return (1);
		if (str[1] == '|' || str[1] == '&')
		{
			if (str[2] == '\0')
				return (1);
		}
		return (2);
	}
	return (0);
}

static void	ft_cmdcpy(char **n_cmd, t_object *task)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (task->cmd[++i])
	{
		if (ft_check_link(task->cmd[i]) == 2)
			ft_rewrite(task->cmd[i]);
		if (ft_check_redirect(task->cmd[i]) == 0
			&& ft_check_link(task->cmd[i]) == 0)
			n_cmd[++j] = task->cmd[i];
		else if (ft_check_redirect(task->cmd[i]) == 1
			|| ft_check_link(task->cmd[i]) == 1)
			free(task->cmd[i]);
		else if (ft_check_redirect(task->cmd[i]) == 2)
		{
			free(task->cmd[i]);
			i++;
			free(task->cmd[i]);
		}
	}
	free(task->cmd);
	task->cmd = n_cmd;
}

char	**ft_reduce_cmd(t_object *task)
{
	size_t	cmd_len;
	char	**n_cmd;
	size_t	i;

	i = 0;
	cmd_len = ft_arrlen((void **)task->cmd);
	while (task->cmd[i])
	{
		cmd_len -= ft_check_redirect(task->cmd[i]);
		if (ft_check_link(task->cmd[i]) == 1)
			cmd_len--;
		i++;
	}
	n_cmd = (char **)ft_calloc(cmd_len + 1, sizeof(char *));
	if (!n_cmd)
		return (task->cmd);
	ft_cmdcpy(n_cmd, task);
	return (n_cmd);
}
