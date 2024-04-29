/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reduce_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:13:34 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/29 09:34:49 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str[j] = '\0';
}

static void	ft_free_old_cmd(char **cmd, size_t index)
{
	size_t	arg_len;
	char	*tmp;

	tmp = ft_strdup(cmd[index]);
	if (!tmp)
		return ;
	arg_len = ft_strlen(cmd[index]);
	if (arg_len <= 2)
	{
		free(cmd[index]);
		if (tmp[0] == '<' || tmp[0] == '>')
			free(cmd[index + 1]);
	}
	else
	{
		if (tmp[0] == '<' || tmp[0] == '>')
			free(cmd[index]);
	}
	free(cmd);
	free(tmp);
}

static void	ft_cmdcpy_end(char **n_cmd, char **cmd, size_t *index[2], size_t i)
{
	if ((*index)[0] != i)
		n_cmd[(*index)[1]++] = cmd[(*index)[0]];
	else
	{
		if (!(cmd[i][0] == '<' || cmd[i][0] == '>'))
		{
			ft_rewrite(cmd[(*index)[0]]);
			n_cmd[((*index)[1])++] = cmd[(*index)[0]];
		}
	}
}

static void	ft_cmdcpy(char **n_cmd, char **cmd, size_t index)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (cmd[++i])
	{
		if (ft_strlen(cmd[index]) <= 2 && i != index)
		{
			if ((cmd[index][0] == '<' || cmd[index][0] == '>')
					&& i != index + 1)
				n_cmd[j++] = cmd[i];
			else if (!(cmd[index][0] == '<' || cmd[index][0] == '>'))
				n_cmd[j++] = cmd[i];
		}
		if (ft_strlen(cmd[index]) > 2)
			ft_cmdcpy_end(n_cmd, cmd, (size_t *[2]){&i, &j}, index);
	}
	ft_free_old_cmd(cmd, index);
}

char	**ft_reduce_cmd(char **cmd, size_t index)
{
	size_t	cmd_len;
	char	**new_cmd;

	cmd_len = ft_arrlen((void **)cmd);
	if (!cmd[index] || (cmd[index][0] != '<' && cmd[index][0] != '>'
			&& cmd[index][0] != '&' && cmd[index][0] != '|'))
		return (cmd);
	if (ft_strlen(cmd[index]) > 2)
	{
		if (cmd[index][0] == '<' || cmd[index][0] == '>')
			cmd_len--;
	}
	else
		if (cmd[index][0] == '<' || cmd[index][0] == '>')
			cmd_len -= 2;
	else
		cmd_len--;
	new_cmd = (char **)ft_calloc(cmd_len + 1, sizeof(char *));
	if (!new_cmd)
	{
		ft_free_array((void **)cmd);
		return (NULL);
	}
	ft_cmdcpy(new_cmd, cmd, index);
	return (new_cmd);
}
