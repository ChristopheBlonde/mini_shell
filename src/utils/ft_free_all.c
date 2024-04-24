/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:41:17 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/24 16:55:41 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirect(t_parse *parse)
{
	ft_free_arrstruct((void **)parse->redirect, ft_free_file_descriptor);
}

void	ft_free_task(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		ft_free_array((void **)parse->task[i]->cmd);
		free(parse->task[i]);
		i++;
	}
	free(parse->task);
}

void	ft_free_env(t_parse *parse)
{
	ft_free_array((void **)parse->env);
}

void	ft_free_all(t_parse *parse)
{
	if (parse->task)
	{
		ft_free_task(parse);
		parse->task = NULL;
	}
	if (parse->redirect)
	{
		ft_free_redirect(parse);
		parse->redirect = NULL;
	}
	if (parse->env)
	{
		ft_free_env(parse);
		parse->env = NULL;
	}
}
