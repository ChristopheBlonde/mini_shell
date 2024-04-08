/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/08 14:10:01 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>


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

char	*ft_strqcpy(char *s, char quote)
{
	size_t		len;
	char	*result;
	size_t		i;
	size_t		j;

	len = strlen(s);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != quote)
		{
			result[j++] = s[i];
		}
		i++;
	}
	free(s);
	return (result);
}

static inline char	*fill_word(const char *str, size_t word_start, size_t word_end)
{
	size_t word_length;
	char *word;

	word_length = word_end - word_start;
	word = (char *)malloc(word_length + 1);
	strncpy(word, str + word_start, word_length);
	word[word_length] = '\0';
	return (word);
}

/**
 * @brief Splits a string into tokens based on a delimiter, while handling quotes.
 *
 * This function takes a string and a delimiter character and splits the string into tokens.
 * It handles quotes (single and double) by ignoring delimiters inside quotes.
 *
 * @param str The string to be split into tokens.
 * @param delimiter The delimiter character used to split the string.
 * @return An array of strings representing the tokens. The last element of the array is NULL.
 */


char	**ft_split_with_quotes2(const char *str, char delimiter)
{
	size_t	i;
	size_t	word_start;
	size_t	word_count;
	int		in_quotes;
	char	**result;

	i = -1;
	word_count = 0;
	word_start = 0;
	in_quotes = -1;
	result = (char **)ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	if (!result)
		return NULL;
	while (str[++i])
	{
		in_quotes = is_in_quote(str, i, in_quotes);
		if ((str[i] == delimiter || str[i] == '\n') && in_quotes == -1)
		{
			copy_word(str, word_start, i, result, &word_count);
			word_start = i + 1;
		}
	}
	if (i > word_start)
		copy_word(str, word_start, i, result, &word_count);
	return result;
}

int is_in_quote(const char *str, size_t index, int in_quotes)
{
	if (str[index] == '"' && (index == 0 || str[index - 1] != '\\'))
	{
		if (in_quotes == -1)
			return index;
		else
			return -1;
	}
	return in_quotes;
}

void copy_word(const char *str, size_t start, size_t end, char **result, size_t *word_count)
{
	size_t word_length = end - start;
	result[*word_count] = (char *)malloc(word_length + 1);
	strncpy(result[*word_count], str + start, word_length);
	result[*word_count][word_length] = '\0';
	(*word_count)++;
}


static inline void print_cmds(char **cmd)
{
	for (size_t i = 0; cmd[i]; i++)
		printf("cmd[%zu] = %s\n", i, cmd[i]);
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
	size_t	j;
	size_t	len;
	char	**arr;
	
	(void)parse;
	arr = ft_strtok(input, "<>|&\n");
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1, sizeof(t_object *));
	i = -1;
	len = ft_arrlen((void **)arr);
	while ((size_t)++i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		parse->task[i]->cmd = ft_split_with_quotes2(arr[i], ' ');
		j = -1;
		while (parse->task[i]->cmd[++j])
			if (parse->task[i]->cmd[j][0] == '\'' || parse->task[i]->cmd[j][0] == '"')
				parse->task[i]->cmd[j] = ft_strqcpy(parse->task[i]->cmd[j], parse->task[i]->cmd[j][0]);
		
		print_cmds(parse->task[i]->cmd);
		// ft_fill_redirection(parse->task[i]->cmd, parse);
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
 