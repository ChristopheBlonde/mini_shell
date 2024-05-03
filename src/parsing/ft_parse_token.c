/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/05/02 16:11:35 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_token(t_parse *parse, char *input)
{
	size_t	i;
	size_t	len;
	char	**arr;

	(void)parse;
	arr = ft_strtok(input, "|&\n");
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1,
			sizeof(t_object *));
	if (!parse->task)
		return ;
	i = -1;
	len = ft_arrlen((void **)arr);
	while ((size_t)++i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		if (!parse->task[i])
			return ;
		parse->task[i]->cmd = ft_split_with_quotes(arr[i], ' ');
		parse->task[i]->infile = -1;
		parse->task[i]->outfile = -1;
	}
	ft_redirection(parse);
	ft_wildcard(parse);
	ft_delete_quotes(parse);
	ft_free_array((void **)arr);
} //NORM
/*
	if (parse->redirect)
	{
		i = 0;
		while (parse->redirect[i])
		{
			ft_printf("enum:%d, quoted:%d, name:%s\n",
			parse->redirect[i]->type,
			parse->redirect[i]->in_quote, parse->redirect[i]->file);
			i++;
		}
	}
	i = 0;
	while (parse->task[i])
	{
		int j = 0;
		ft_printf("task[%d], input:%d, output:%d\n",
		i, parse->task[i]->infile, parse->task[i]->outfile);
		while (parse->task[i]->cmd[j])
		{
			ft_printf("task[%d], cmd[%d], value:%s\n", i,
			j, parse->task[i]->cmd[j]);
			j++;
		}
		i++;
	}
*/
