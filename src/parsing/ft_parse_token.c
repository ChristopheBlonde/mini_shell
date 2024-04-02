/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/02 16:57:40 by tsadouk          ###   ########.fr       */
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

void	print_tokens(t_parse *parse);
#include <stdio.h>

/**
 * @brief Parses the input string and creates an array of commands.
 *
 * This function takes an input string and tokenizes it based on the delimiters "<>|&\n".
 * It then prints each token to the standard output, followed by three newlines.
 * It also creates an array of t_object structures, where each structure represents a command.
 * Each command is further split into an array of strings representing the command and its arguments.
 * Finally, it prints each command and its arguments to the standard output.
 *
 * @param parse A pointer to the t_parse structure.
 * @param input The input string to be parsed.
 */
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
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(t_object *));
	i = 0;
	size_t	len = ft_arrlen((void **)arr);
	while ((size_t)i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		parse->task[i]->cmd = ft_split(arr[i], ' ');
		//for (int k = 0; parse->task[i]->cmd[k]; k++)
			//("cmd[%d] = %s\n", k, parse->task[i]->cmd[k]);
		ft_fill_redirection(parse->task[i]->cmd, parse);
		
		i++;
	}
	i = 0;
	// print_tokens(parse);
	ft_free_array((void **)arr);
}

/*
void	ft_reparse_token(t_parse *parse)
{
	
}
*/

/**
 * @brief Prints the tokens stored in the given parse structure.
 *
 * This function iterates over the task array in the parse structure and prints each token.
 * Each token is printed on a separate line, with a space between each token.
 *
 * @param parse The parse structure containing the tokens to be printed.
 */
void print_tokens(t_parse *parse)
{
	size_t i;
	size_t j;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			ft_putstr_fd(parse->task[i]->cmd[j], 1);
			ft_putstr_fd(" ", 1);
			j++;
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
/*
void	print_links(t_parse *parse)
{
	size_t i = 0;
	while (parse->task[i])
	{
		if (parse->task[i]->link == AND)
			ft_putstr_fd("AND", 1);
		else if (parse->task[i]->link == OR)
			ft_putstr_fd("OR", 1);
		else if (parse->task[i]->link == PIPE)
			ft_putstr_fd("PIPE", 1);
		else
			ft_putstr_fd("NO_LINK", 1);
		i++;
	}
}
*/

void	print_objects(t_parse *parse)
{
	size_t i;
	size_t j;

	i = 0;
	while (parse->task[i])
	{
		j = 0;
		while (parse->task[i]->cmd[j])
		{
			ft_putstr_fd(parse->task[i]->cmd[j], 1);
			ft_putstr_fd(" ", 1);
			j++;
		}
		/*----LINK----*/
		if (parse->task[i]->link == AND)
			ft_putstr_fd("AND", 1);
		else if (parse->task[i]->link == OR)
			ft_putstr_fd("OR", 1);
		else if (parse->task[i]->link == PIPE)
			ft_putstr_fd("PIPE", 1);
		else
			ft_putstr_fd("NO_LINK", 1);
		/*--------------*/
		ft_putstr_fd("\n", 1);
		i++;
	}
}
