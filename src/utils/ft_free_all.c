/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:41:17 by cblonde           #+#    #+#             */
/*   Updated: 2024/07/06 09:17:44 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirect(t_parse *parse)
{
	ft_free_arrstruct((void **)parse->redirect, ft_free_file_descriptor);
}

void	ft_free_task(t_parse *parse)
{
	int	i;

	i = -1;
	while (parse->task[++i])
	{
		if (parse->task[i] && parse->task[i]->cmd)
		{
			ft_free_array((void **)parse->task[i]->cmd);
			parse->task[i]->cmd = NULL;
		}
		if (parse->task[i]->unquoted)
		{
			free(parse->task[i]->unquoted);
			parse->task[i]->unquoted = NULL;
		}
		if (parse->task[i])
		{
			free(parse->task[i]);
			parse->task[i] = NULL;
		}
	}
	free(parse->task);
}

void	ft_free_env(t_parse *parse)
{
	ft_free_array((void **)parse->env);
}

void	ft_free_parsing(t_parse *parse)
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
	if (parse->input)
	{
		free(parse->input);
		parse->input = NULL;
	}
}

void	ft_free_all(t_parse *parse)
{
	if (parse && parse->task)
	{
		ft_free_task(parse);
		parse->task = NULL;
	}
	if (parse && parse->redirect)
	{
		ft_free_redirect(parse);
		parse->redirect = NULL;
	}
	if (parse && parse->env)
	{
		ft_free_env(parse);
		parse->env = NULL;
	}
	if (parse && parse->input)
	{
		free(parse->input);
		parse->input = NULL;
	}
}
