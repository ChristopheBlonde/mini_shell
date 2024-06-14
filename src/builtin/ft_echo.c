/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/06/14 16:00:44 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	get_skip_len(char *str, int start)
{
	int	len;

	len = 1;
	while (str[start + len]
		&& (ft_isalnum(str[start + len]) || str[start + len] == '_'))
		len++;
	return (len);
}

static void	handle_env_var(t_parse *parse, char **str, int *j)
{
	char	*env_var;
	int		skip;

	if (!ft_isalnum((*str)[*j + 1]) && (*str)[*j + 1] != '_')
	{
		(*j)++;
		return ;
	}
	ft_putstr_fd_until(*str, *j);
	env_var = ft_getenv(parse, &(*str)[*j + 1]);
	if (env_var)
	{
		ft_putstr_fd(env_var, 1);
		*j += ft_strlen(&(*str)[*j + 1]);
		*str = &(*str)[*j];
		*j = 0;
	}
	else
	{
		skip = get_skip_len(*str, *j);
		*str = &(*str)[*j + skip];
		*j = 0;
	}
}

static int	check_n_option(t_object *task, int *i)
{
	if (task->cmd[1] && task->cmd[1][0] != '\0'
		&& !ft_strncmp(task->cmd[1], "-n", ft_strlen(task->cmd[1])))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static int	ft_echo(t_parse *parse, t_object *task)
{
	int		i;
	int		option;
	char	*str;
	int		j;

	i = 1;
	option = check_n_option(task, &i);
	while (task->cmd[i])
	{
		str = task->cmd[i];
		j = 0;
		while (str[j])
		{
			if (str[j] == '$' && str[j + 1] != '\0')
				handle_env_var(parse, &str, &j);
			else
				j++;
		}
		ft_putstr_fd(str, 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	ft_excmd_result(parse, 0);
	return (0);
}

void	ft_exec_echo(t_parse *parse, t_object *task)
{
	if (task->builtin != ECHO)
		return ;
	if (!task->cmd)
		return ;
	ft_echo(parse, task);
}
