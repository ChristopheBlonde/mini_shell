/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:55:51 by tsadouk           #+#    #+#             */
/*   Updated: 2024/04/03 16:01:17 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the parse structure by allocating memory for the task, env, history, and redirect arrays.
 *
 * This function initializes the parse structure by allocating memory for the task, env, history, and redirect arrays.
 * The task array is an array of t_object structures, the env array is an array of environment variables, the history array is an array of command history entries, and the redirect array is an array of file descriptors for redirection.
 *
 * @param parse A pointer to the parse structure to be initialized.
 */
void	ft_init_data(t_parse *parse)
{
	parse->task = (t_object **)ft_calloc(1, sizeof(t_object *));
	parse->env = (char **)ft_calloc(1, sizeof(char *));
	parse->history = (char **)ft_calloc(1, sizeof(char *));
	parse->redirect = (t_file_descriptor **)ft_calloc(1, sizeof(t_file_descriptor *));
}

void	free_objects(t_parse *parse)
{
	size_t	i;

	i = 0;
	while (parse->task[i])
	{
		free(parse->task[i]->cmd);
		free(parse->task[i]);
		i++;
	}
	free(parse->task);
}

void 	free_parse(t_parse *parse)
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

void free_history(t_parse *parse)
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