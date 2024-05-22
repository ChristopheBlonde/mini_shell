/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:46:43 by tsadouk           #+#    #+#             */
/*   Updated: 2024/05/22 16:34:35 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// char	ft_echo(char *str)
// {
// 	int	option;

// 	option = 0;
// 	if (str == NULL)
// 		return (1);
// 	while (ft_isspace(*str))
// 		str++;
// 	if (*str == '\0')
// 	{
// 		putchar_fd('\n', 1);
// 		return (0);
// 	}
// 	if (*str == '-' && *(str + 1) == 'n')
// 	{
// 		str += 2;
// 		option = 1;
// 		while (ft_isspace(*str))
// 			str++;
// 	}
// 	put_str_fd(str, 1);
// 	if (!option)
// 		putchar_fd('\n', 1);
// 	return (0);
// }

static void	ft_echo(t_parse *parse)
{
	int		i;
	int		option;
	char	*str;

	i = 1;
	option = 0;
	while (parse->task[0]->cmd[i] && !ft_strncmp(parse->task[0]->cmd[i], "-n", 2))
	{
		option = 1;
		i++;
	}
	while (parse->task[0]->cmd[i])
	{
		str = parse->task[0]->cmd[i];
		ft_putstr_fd(str, 1);
		if (parse->task[0]->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
}

void	ft_exec_echo(t_parse *parse, t_object *task)
{
	if (task->builtin != ECHO)
		return;
	if (!task->cmd)
		return;

	ft_echo(parse);
	ft_excmd_result(parse, 0);
}

