/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblonde <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:41:17 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/09 15:48:46 by cblonde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_objects(t_parse *parse)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			free(parse->task[i]->cmd[j]);
			j++;
		}
		free(parse->task[i]->cmd);
		free(parse->task[i]);
		i++;
	}
	free(parse->task);
}

void	free_parse(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->env[i])
	{
		free(parse->env[i]);
		i++;
	}
	free(parse->env);
	i = 0;
	while (parse->history[i])
	{
		free(parse->history[i]);
		i++;
	}
	free(parse->history);
	i = 0;
	while (parse->redirect[i])
	{
		free(parse->redirect[i]);
		i++;
	}
	free(parse->redirect);
	free_objects(parse);
}

void	free_redirect(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->redirect[i])
	{
		free(parse->redirect[i]);
		i++;
	}
	free(parse->redirect);
}

void	free_history(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->history[i])
	{
		free(parse->history[i]);
		i++;
	}
	free(parse->history);
}

void	free_all(t_parse *parse)
{
	free_parse(parse);
	free_history(parse);
	free_redirect(parse);
}
