/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/03/29 11:39:02 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO : classifier les tokens

/*
void	ft_parse_token(t_parse *parse, char *input)
{
	size_t	i;
	char	**arr;

	(void)parse;
	i = 0;
	arr = ft_strtok(input, "<>|&\n");
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(t_object *));
	parse->task->cmd = (char **)
	while (arr[i])
	{
		parse->task[i]->cmd[i] = (char *)ft_calloc(2, sizeof(char *));
		parse->task[i]->cmd[i] = arr[i];
		if (i == ft_arrlen((void **)arr) - 1)
			ft_putstr_fd(arr[i], 1);
		else
			ft_putendl_fd(arr[i], 1);
		i++;
	}
	ft_free_array((void **)arr);
}
*/
#include <stdio.h>

void	ft_parse_token(t_parse *parse, char *input)
{
	size_t	i;
	char	**arr;
	
	(void)parse;
	i = 0;
	arr = ft_strtok(input, "<>|&\n");
	while (arr[i])
	{
		if (i == ft_arrlen((void **)arr) - 1)
			ft_putstr_fd(arr[i], 1);
		else
			ft_putendl_fd(arr[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(t_object *));
	i = 0;
	size_t	len = ft_arrlen((void **)arr);
	while ((size_t)i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		parse->task[i]->cmd = ft_split(arr[i], ' ');
		i++;
	}
	i = 0;
	while (parse->task[i])
	{
		int j = 0;
		while (parse->task[i]->cmd[j])
		{
			printf("%s\n", parse->task[i]->cmd[j]);
			j++;
		}
		i++;
		ft_putendl_fd("new tab",1);
	}
	ft_free_array((void **)arr);
}
