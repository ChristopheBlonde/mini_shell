/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/22 10:25:51 by cblonde          ###   ########.fr       */
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
		ft_delete_quotes(parse, i);
	}
	ft_redirection(parse);
	if (parse->redirect)
	{
		ft_putendl_fd(parse->redirect[0]->file, 1);
		ft_putendl_fd(parse->redirect[1]->file, 1);
	}
	ft_free_array((void **)arr);
}
