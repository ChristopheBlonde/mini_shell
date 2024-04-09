/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/09 14:22:57 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

static inline void	print_cmds(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
		i++;
	}
}

void	ft_parse_token(t_parse *parse, char *input)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**arr;

	(void)parse;
	arr = ft_strtok(input, "<>|&\n");
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1,
			sizeof(t_object *));
	i = -1;
	len = ft_arrlen((void **)arr);
	while ((size_t)++i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		parse->task[i]->cmd = ft_split_with_quotes(arr[i], ' ');
		j = -1;
		while (parse->task[i]->cmd[++j])
			if (parse->task[i]->cmd[j][0] == '\''
				|| parse->task[i]->cmd[j][0] == '"')
				parse->task[i]->cmd[j] = ft_strqcpy(parse->task[i]->cmd[j],
						parse->task[i]->cmd[j][0]);
		print_cmds(parse->task[i]->cmd);
	}
	ft_free_array((void **)arr);
}
