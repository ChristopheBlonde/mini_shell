/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsadouk <tsadouk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 08:17:08 by cblonde           #+#    #+#             */
/*   Updated: 2024/04/08 15:35:39 by tsadouk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

char	*ft_strqcpy(char *s, char quote)
{
	size_t		len;
	char		*result;
	size_t		i;
	size_t		j;

	len = strlen(s);
	result = (char *)ft_calloc(len - 1, sizeof(char));
	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] != quote)
			result[j++] = s[i];
	free(s);
	return (result);
}

static inline char	*fill_word(const char *str, size_t word_start,
	size_t word_end)
{
	size_t	word_length;
	char	*word;

	word_length = word_end - word_start;
	word = (char *)malloc(word_length + 1);
	ft_strlcpy(word, str + word_start, word_length + 1);
	word[word_length] = '\0';
	return (word);
}

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
		return (NULL);
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
	return (result);
}

int	is_in_quote(const char *str, size_t index, int in_quotes)
{
	if (str[index] == '"' && (index == 0 || str[index - 1] != '\\'))
	{
		if (in_quotes == -1)
			return (index);
		else
			return (-1);
	}
	return (in_quotes);
}

void	copy_word(const char *str, size_t start, size_t end, char **result,
	size_t *word_count)
{
	size_t	word_length;

	word_length = end - start;
	result[*word_count] = (char *)malloc(word_length + 1);
	if (!result[*word_count])
	{
		ft_free_array((void **)result);
		return ;
	}
	ft_strlcpy(result[*word_count], str + start, word_length + 1);
	result[*word_count][word_length] = '\0';
	(*word_count)++;
}

static inline void	print_cmds(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
		i++;
	}
}

void	ft_parse_token(t_parse *parse, char *input)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**arr;

	(void)parse;
	arr = ft_strtok(input, "<>|&\n");
	parse->task = (t_object **)ft_calloc(ft_arrlen((void **)arr) + 1,
			sizeof(t_object *));
	i = -1;
	len = ft_arrlen((void **)arr);
	while ((size_t)++i < len)
	{
		parse->task[i] = (t_object *)ft_calloc(1, sizeof(t_object));
		parse->task[i]->cmd = ft_split_with_quotes2(arr[i], ' ');
		j = -1;
		while (parse->task[i]->cmd[++j])
			if (parse->task[i]->cmd[j][0] == '\''
				|| parse->task[i]->cmd[j][0] == '"')
				parse->task[i]->cmd[j] = ft_strqcpy(parse->task[i]->cmd[j],
						parse->task[i]->cmd[j][0]);
		print_cmds(parse->task[i]->cmd);
	}
	ft_free_array((void **)arr);
}
