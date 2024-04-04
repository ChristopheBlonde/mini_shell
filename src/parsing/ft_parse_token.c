/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/04 20:08:26 by tsadouk          ###   ########.fr       */
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
 * @file ft_parse_token.c
 * @brief Split a string into tokens based on a delimiter, taking into account quotes.
 * 
 * This function splits a string into tokens based on a specified delimiter character.
 * It also takes into account quotes, allowing for tokens to be enclosed in double quotes.
 * The resulting tokens are stored in a dynamically allocated array of strings.
 * 
 * @param str The string to be split into tokens.
 * @param delimiter The delimiter character used to separate the tokens.
 * @return A dynamically allocated array of strings containing the tokens.
 *         The last element of the array is set to NULL.
 */

#include <string.h>

char **ft_split_with_quotes(const char *str, char delimiter)
{
	size_t i = 0;
	size_t word_start = 0;
	bool in_quotes = false;
	char **result = malloc(sizeof(char *) * 100); // Assuming a maximum of 100 words
	size_t word_count = 0; // Variable to keep track of the number of words found

	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
		}
		else if (!in_quotes && (str[i] == delimiter || str[i] == '\n'))
		{
			size_t word_length = i - word_start;
			result[word_count] = malloc(word_length + 1);
			strncpy(result[word_count], str + word_start, word_length);
			result[word_count][word_length] = '\0';
			word_start = i + 1;
			word_count++; // Increment word_count for each word found
		}
		else if (in_quotes && str[i] == delimiter)
		{
			// If inside quotes, treat the delimiter as a normal character
			i++;
			continue;
		}
		i++;
	}

	// Handle the last word if it doesn't end with a delimiter
	if (i > word_start)
	{
		size_t word_length = i - word_start;
		result[word_count] = malloc(word_length + 1);
		strncpy(result[word_count], str + word_start, word_length);
		result[word_count][word_length] = '\0';
		word_count++;
	}

	result[word_count] = NULL; // NULL-terminate the array
	return result;
}



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
	for (size_t j = 0; arr[j]; j++)
		printf("arr[%zu] = %s\n", j, arr[j]);

	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(t_object *));
	i = 0;
	size_t	len = ft_arrlen((void **)arr);
	while ((size_t)i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		parse->task[i]->cmd = ft_split_with_quotes(arr[i], ' ');
		for (size_t j = 0; parse->task[i]->cmd[j]; j++)
			printf("cmd[%zu][%zu] = %s\n", i, j, parse->task[i]->cmd[j]);
		// ft_fill_redirection(parse->task[i]->cmd, parse);
		i++;
	}
	ft_free_array((void **)arr);
}


/**
 * @brief Prints the tokens stored in the given parse structure.
 *
 * This function iterates over the task array in the parse structure and prints each token.
 * Each token is printed on a separate line, with a space between each token.
 *
 * @param parse The parse structure containing the tokens to be printed.
 */
// void print_tokens(t_parse *parse)
// {
// 	size_t i;
// 	size_t j;

// 	printf("je suis cette fonction\n");
// 	i = 0;
// 	while (parse->task[i])
// 	{
// 		j = 0;
// 		while (parse->task[i]->cmd[j])
// 		{
// 			printf("cmd[%zu] = %s\n", j, parse->task[i]->cmd[j]);
// 			printf("je ne asi aps ce que je fait\n");
// 			ft_putstr_fd(parse->task[i]->cmd[j], 1);
// 			ft_putstr_fd(" ", 1);
// 			j++;
// 		}
// 		ft_putstr_fd("\n", 1);
// 		i++;
// 	}
// }

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

	printf("je suis cette fonction\n");
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
